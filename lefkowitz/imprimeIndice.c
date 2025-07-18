#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idade;
    long offset;
} Indice;

void imprimirIndice(const char *arquivoIndice) {
    FILE *arquivo = fopen(arquivoIndice, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Indice indice;
    int posicao = 0;
    while (fread(&indice, sizeof(Indice), 1, arquivo) == 1) {
        printf("Posição %d -> Idade: %d, Offset: %ld, Endereço: %p\n", 
                posicao, indice.idade, indice.offset, (void*)&indice);
        posicao++;
    }

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_indice>\n", argv[0]);
        return 1;
    }

    const char *arquivoIndice = argv[1];
    imprimirIndice(arquivoIndice);
    return 0;
}
