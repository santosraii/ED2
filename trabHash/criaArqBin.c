#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct Cliente {
    int codCliente;
    char nome[MAX_NOME];
} Cliente;

void criarArquivoBinario(const char *nomeArquivo) {
    // Entrada 1
    /*
    Cliente clientes[] = {
        {10, "Cliente 10"},
        {3, "Cliente 3"},
        {5, "Cliente 5"},
        {7, "Cliente 7"},
        {12, "Cliente 12"},
        {6, "Cliente 6"},
        {14, "Cliente 14"},
        {4, "Cliente 4"},
        {8, "Cliente 8"},
        {20, "Cliente 20"},
        {22, "Cliente 22"}


    };
    */

   // /*
    // Entrada 2
    Cliente clientes[] = {
        {15, "Cliente 15"},
        {9, "Cliente 9"},
        {1, "Cliente 1"},
        {3, "Cliente 3"},
        {20, "Cliente 20"},
        {25, "Cliente 25"},
        {11, "Cliente 11"},
        {30, "Cliente 30"},
        {2, "Cliente 2"},
        {16, "Cliente 16"}

    };
   // */

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
