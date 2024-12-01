#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct Cliente {
    int codCliente;
    char nome[MAX_NOME];
} Cliente;

typedef struct NoHash {
    int codCliente;
    long offset;
    struct NoHash *prox;
} NoHash;

typedef struct TabelaHash {
    int m;
    int l;
    int p;
    int tamanho;
    float fatorCarga;
    NoHash **tabela;
} TabelaHash;

int funcaoHash(TabelaHash *tabela, int codCliente) {
    int mPotencia = tabela->m * (1 << tabela->l);
    return codCliente % mPotencia;
}

TabelaHash* criarTabelaHash(int tamanhoInicial, float fatorCarga) {
    TabelaHash *tabela = (TabelaHash *)malloc(sizeof(TabelaHash));
    tabela->m = tamanhoInicial;
    tabela->l = 0;
    tabela->p = 0;
    tabela->tamanho = 0;
    tabela->fatorCarga = fatorCarga;
    tabela->tabela = (NoHash **)malloc(tamanhoInicial * sizeof(NoHash *));
    for (int i = 0; i < tamanhoInicial; i++) {
        tabela->tabela[i] = NULL;
    }
    return tabela;
}

void redistribuirCompartimento(TabelaHash *tabela, int pAntigo) {
    NoHash *atual = tabela->tabela[pAntigo];
    tabela->tabela[pAntigo] = NULL;
    
    while (atual != NULL) {
        NoHash *temp = atual->prox;
        int novoIndice = funcaoHash(tabela, atual->codCliente);
        atual->prox = tabela->tabela[novoIndice];
        tabela->tabela[novoIndice] = atual;
        atual = temp;
    }
}

void expandirTabelaHash(TabelaHash *tabela) {
    int novaCapacidade = tabela->m * (1 << (tabela->l + 1));
    tabela->tabela = (NoHash **)realloc(tabela->tabela, novaCapacidade * sizeof(NoHash *));
    for (int i = tabela->m * (1 << tabela->l); i < novaCapacidade; i++) {
        tabela->tabela[i] = NULL;
    }
    
    tabela->l++;
    tabela->p = 0;
}

void inserirCliente(TabelaHash *tabela, int codCliente, long offset) {
    NoHash *novoNo = (NoHash *)malloc(sizeof(NoHash));
    novoNo->codCliente = codCliente;
    novoNo->offset = offset;
    novoNo->prox = NULL;

    int indice = funcaoHash(tabela, codCliente);

    NoHash *atual = tabela->tabela[indice];
    if (atual == NULL) {
        tabela->tabela[indice] = novoNo;
    } else {
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }

    tabela->tamanho++;

    if ((float)tabela->tamanho / (tabela->m * (1 << tabela->l)) > tabela->fatorCarga) {
        expandirTabelaHash(tabela);
    }

    if (tabela->p < tabela->m * (1 << (tabela->l - 1))) {
        redistribuirCompartimento(tabela, tabela->p);
        tabela->p++;
    }
}

void lerClientesArquivo(TabelaHash *tabela, const char *nomeArquivoEntrada, FILE *arquivoClientesSaida) {
    FILE *arquivoEntrada = fopen(nomeArquivoEntrada, "rb");
    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return;
    }

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoEntrada) == 1) {
        long offset = ftell(arquivoClientesSaida);
        fwrite(&cliente, sizeof(Cliente), 1, arquivoClientesSaida);
        inserirCliente(tabela, cliente.codCliente, offset);
    }

    fclose(arquivoEntrada);
}

void escreverTabelaArquivo(TabelaHash *tabela, const char *nomeArquivoSaida) {
    FILE *arquivoSaida = fopen(nomeArquivoSaida, "wb");
    if (arquivoSaida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    int capacidade = tabela->m * (1 << tabela->l);
    for (int i = 0; i < capacidade; i++) {
        NoHash *atual = tabela->tabela[i];
        while (atual != NULL) {
            fwrite(atual, sizeof(NoHash), 1, arquivoSaida);
            atual = atual->prox;
        }
    }

    fclose(arquivoSaida);
}

void imprimirTabela(TabelaHash *tabela) {
    int capacidade = tabela->m * (1 << tabela->l);
    for (int i = 0; i < capacidade; i++) {
        NoHash *atual = tabela->tabela[i];
        if (atual != NULL) {
            printf("Indice %d:\n", i);
            while (atual != NULL) {
                printf(" CodCliente: %d, Offset: %ld\n", atual->codCliente, atual->offset);
                atual = atual->prox;
                }
            }
        }
    }

    int main(int argc, char *argv[]) {
        if (argc != 3) {
            fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida_prefix>\n", argv[0]);
            return 1;
        }

        const char *nomeArquivoEntrada = argv[1];
        char nomeArquivoTabela[100];
        char nomeArquivoClientes[100];
        snprintf(nomeArquivoTabela, 100, "%s_tabela.bin", argv[2]);
        snprintf(nomeArquivoClientes, 100, "%s_clientes.bin", argv[2]);
       
        TabelaHash *tabela = criarTabelaHash(7, 0.75);
        
        FILE *arquivoClientesSaida = fopen(nomeArquivoClientes, "wb");
        if (arquivoClientesSaida == NULL) {
            perror("Erro ao abrir o arquivo de saída de clientes");
            return 1;
        }

        lerClientesArquivo(tabela, nomeArquivoEntrada, arquivoClientesSaida);
        fclose(arquivoClientesSaida);

        escreverTabelaArquivo(tabela, nomeArquivoTabela); 

        printf("Conteúdo da tabela hash:\n"); 
        imprimirTabela(tabela);

        return 0;
    }