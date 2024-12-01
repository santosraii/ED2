#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct{
    int cod;
    char nome[MAX_NOME];
    int idade;
} Cliente;

typedef struct{
    int idade;
    long offset;
} Indice;

void criarIndice(const char *arquivoEntrada, const char *arquivoIndice) {
    FILE *entrada = fopen(arquivoEntrada, "rb");
    FILE *saida = fopen(arquivoIndice, "wb");

    if (entrada == NULL || saida == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Cliente cliente;
    Indice indice;
    long offset;

    while (fread(&cliente, sizeof(Cliente), 1, entrada) == 1) {
        offset = ftell(entrada) - sizeof(Cliente);
        indice.idade = cliente.idade;
        indice.offset = offset;
        fwrite(&indice, sizeof(Indice), 1, saida);
    }

    fclose(entrada);
    fclose(saida);
}

int compararIndices(const void *a, const void *b) {
    Indice *indiceA = (Indice *)a;
    Indice *indiceB = (Indice *)b;
    return (indiceA->idade - indiceB->idade);
}

void ordenarIndice(const char *arquivoIndice) {
    FILE *arquivo = fopen(arquivoIndice, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    int numIndices = tamanhoArquivo / sizeof(Indice);
    rewind(arquivo);

    Indice *indices = (Indice *)malloc(tamanhoArquivo);
    fread(indices, sizeof(Indice), numIndices, arquivo);

    qsort(indices, numIndices, sizeof(Indice), compararIndices);

    rewind(arquivo);
    fwrite(indices, sizeof(Indice), numIndices, arquivo);

    fclose(arquivo);
    free(indices);
}

void imprimirIndice(const char *arquivoIndice) {
    FILE *arquivo = fopen(arquivoIndice, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    
    Indice indice;
    printf("Índice:\n");
    while (fread(&indice, sizeof(Indice), 1, arquivo) == 1) {
        printf("Idade: %d, Offset: %ld\n", indice.idade, indice.offset);
    }

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_indice>\n", argv[0]);
        return 1;
    }

    const char *arquivoEntrada = argv[1];
    const char *arquivoIndice = argv[2];

    criarIndice(arquivoEntrada, arquivoIndice);
    ordenarIndice(arquivoIndice);

    printf("Índice criado e ordenado com sucesso.\n");

    imprimirIndice(arquivoIndice);
    
    return 0;
}
