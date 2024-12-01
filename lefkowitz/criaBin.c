#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct {
    int cod;
    char nome[MAX_NOME];
    int idade;
} Cliente;

void criarArquivoBinario(const char *nomeArquivo) {
    // Conjunto de dados original
    Cliente clientes[] = {
        {10, "Cliente 10", 25},
        {3, "Cliente 3", 30},
        {5, "Cliente 5", 20},
        {7, "Cliente 7", 22},
        {12, "Cliente 12", 30},
        {6, "Cliente 6", 25},
        {14, "Cliente 14", 35},
        {4, "Cliente 4", 40},
        {8, "Cliente 8", 18}
    };

    /*
    // Outra opção de conjunto de dados
    Cliente clientes[] = {
        {15, "Cliente 15", 28},
        {9, "Cliente 9", 24},
        {1, "Cliente 1", 29},
        {3, "Cliente 3", 32},
        {20, "Cliente 20", 26},
        {25, "Cliente 25", 27},
        {11, "Cliente 11", 33},
        {30, "Cliente 30", 31},
        {2, "Cliente 2", 21}
    };
    */

    int n = sizeof(clientes) / sizeof(clientes[0]);

    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fwrite(&clientes[i], sizeof(Cliente), 1, arquivo);
    }

    fclose(arquivo);
    printf("Arquivo binário criado com sucesso: %s\n", nomeArquivo);
}

int main() {
    const char *nomeArquivo = "clientes.bin";
    criarArquivoBinario(nomeArquivo);
    return 0;
}
