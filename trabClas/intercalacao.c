#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NOME 50
#define MAX_DATA 20

typedef struct {
    int CodCliente;
    char Nome[MAX_NOME];
    char DataNascimento[MAX_DATA];
} Cliente;

typedef struct {
    Cliente cliente;
    int indice;
    bool congelado;
} No;

void atualizarVencedor(No *nos, int n) {
    for (int i = n - 1; i > 0; i--) {
        if (nos[2 * i].cliente.CodCliente <= nos[2 * i + 1].cliente.CodCliente) {
            nos[i] = nos[2 * i];
        } else {
            nos[i] = nos[2 * i + 1];
        }
    }
}

void intercalarParticoes(char **arquivosEntrada, int numParticoes, char *arquivoSaida) {
    FILE *entrada[numParticoes];
    for (int i = 0; i < numParticoes; i++) {
        entrada[i] = fopen(arquivosEntrada[i], "rb");
        if (entrada[i] == NULL) {
            perror("Erro ao abrir arquivo de entrada");
            exit(1);
        }
    }

    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }

    No nos[2 * numParticoes];
    
    for (int i = 0; i < numParticoes; i++) {
        if (fread(&nos[i + numParticoes].cliente, sizeof(Cliente), 1, entrada[i]) == 1) {
            nos[i + numParticoes].indice = i;
            nos[i + numParticoes].congelado = false;
        } else {
            nos[i + numParticoes].cliente.CodCliente = INT_MAX;
        }
    }

    atualizarVencedor(nos, numParticoes);

    while (nos[1].cliente.CodCliente != INT_MAX) {
        fwrite(&nos[1].cliente, sizeof(Cliente), 1, saida);
        int origem = nos[1].indice;

        if (fread(&nos[origem + numParticoes].cliente, sizeof(Cliente), 1, entrada[origem]) != 1) {
            nos[origem + numParticoes].cliente.CodCliente = INT_MAX;
        }

        atualizarVencedor(nos, numParticoes);
    }

    for (int i = 0; i < numParticoes; i++) {
        fclose(entrada[i]);
    }
    fclose(saida);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo de saída> <arquivos de entrada...>\n", argv[0]);
        return 1;
    }

    char *arquivoSaida = argv[1];
    int numParticoes = argc - 2;
    char **arquivosEntrada = &argv[2];

    intercalarParticoes(arquivosEntrada, numParticoes, arquivoSaida);

    FILE *arquivo = fopen(arquivoSaida, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo resultante");
        return 1;
    }

    Cliente cliente;
    printf("Conteúdo do arquivo %s:\n", arquivoSaida);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        printf("CodCliente: %d, Nome: %s, DataNascimento: %s\n", 
               cliente.CodCliente, cliente.Nome, cliente.DataNascimento);
    }
    fclose(arquivo);

    return 0;
}
