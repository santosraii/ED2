#include <stdio.h>
#include <stdlib.h>

void verificarArquivo(char* nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    int valor;
    printf("Conteúdo do arquivo %s:\n", nomeArquivo);
    while (fread(&valor, sizeof(int), 1, arquivo) == 1) {
        printf("%d ", valor);
    }
    printf("\n");
    fclose(arquivo);
}

int main() {
    // Nome dos arquivos de saída para verificar
    char* arquivos[] = {"saida1.bin", "saida2.bin", "saida3.bin"};
    int numArquivos = sizeof(arquivos) / sizeof(arquivos[0]);

    for (int i = 0; i < numArquivos; i++) {
        verificarArquivo(arquivos[i]);
    }

    return 0;
}
