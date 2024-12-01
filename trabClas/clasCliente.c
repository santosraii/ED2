#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define M 7
#define MAX_NOME 50
#define MAX_DATA 20

typedef struct {
    int CodCliente;
    char Nome[MAX_NOME];
    char DataNascimento[MAX_DATA];
    bool congelado;
} Cliente;

void lerClientesIniciais(Cliente clientes[], FILE *entrada) {
    for (int i = 0; i < M; i++) {
        if (fread(&clientes[i], sizeof(Cliente), 1, entrada) == 1) {
            clientes[i].congelado = false;
        } else {
            clientes[i].CodCliente = INT_MAX;
            clientes[i].congelado = true;
        }
    }
}

int encontrarMenorCodCliente(Cliente clientes[]) {
    int menorCod = INT_MAX;
    int indiceMenor = -1;
    for (int i = 0; i < M; i++) {
        if (!clientes[i].congelado && clientes[i].CodCliente < menorCod) {
            menorCod = clientes[i].CodCliente;
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

void gravarCliente(FILE *saida, Cliente cliente) {
    fwrite(&cliente, sizeof(Cliente), 1, saida);
}

void substituirCliente(Cliente clientes[], int indice, FILE *entrada) {
    if (fread(&clientes[indice], sizeof(Cliente), 1, entrada) != 1) {
        clientes[indice].CodCliente = INT_MAX;
    }
}

bool todosClientesCongelados(Cliente clientes[]) {
    for (int i = 0; i < M; i++) {
        if (!clientes[i].congelado && clientes[i].CodCliente != INT_MAX) {
            return false;
        }
    }
    return true;
}

void imprimirConteudoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Cliente cliente;
    printf("Conteúdo do arquivo %s:\n", nomeArquivo);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        printf("CodCliente: %d, Nome: %s, DataNascimento: %s\n", 
                cliente.CodCliente, cliente.Nome, cliente.DataNascimento);
    }

    fclose(arquivo);
}

int main(int argc, char* argv[]) {
    
    if(argc != 2){
        fprintf(stderr, "Uso: %s nomeArquivo\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "rb");
    FILE *saida = NULL;
    Cliente clientes[M];
    int particao = 1;
    int indiceMenor;
    
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    lerClientesIniciais(clientes, entrada);

    while (1) {
        char nomeArquivoSaida[20];
        sprintf(nomeArquivoSaida, "saida%d.bin", particao);
        saida = fopen(nomeArquivoSaida, "wb");
        if (saida == NULL) {
            perror("Erro ao abrir o arquivo de saída");
            fclose(entrada);
            return 1;
        }

        while (!todosClientesCongelados(clientes)) {
            indiceMenor = encontrarMenorCodCliente(clientes);
            if (indiceMenor == -1) {
                break;
            }
            gravarCliente(saida, clientes[indiceMenor]);

            int codAnterior = clientes[indiceMenor].CodCliente;
            substituirCliente(clientes, indiceMenor, entrada);
            
            if (clientes[indiceMenor].CodCliente == INT_MAX || clientes[indiceMenor].CodCliente < codAnterior) {
                clientes[indiceMenor].congelado = true;
            }
        }

        fclose(saida);
        particao++;

        bool maisClientes = false;
        for (int i = 0; i < M; i++) {
            if (clientes[i].CodCliente != INT_MAX) {
                maisClientes = true;
                break;
            }
        }

        if (!maisClientes) {
            break;
        }

        for (int i = 0; i < M; i++) {
            clientes[i].congelado = false;
        }
    }

    fclose(entrada);

    for(int i = 1; i < particao; i++){
        char nomeArquivoSaida[20];
        sprintf(nomeArquivoSaida, "saida%d.bin", i);
        imprimirConteudoArquivo(nomeArquivoSaida);
        printf("\n");
    }

    return 0;
}
