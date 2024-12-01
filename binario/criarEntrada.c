#include <stdio.h>

int main() {
    FILE *arquivo = fopen("entrada.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Array de inteiros que queremos escrever no arquivo binário
    //int registros[] = {30, 14, 15, 75, 32, 6, 5, 81, 48, 41, 87, 18, 56, 20, 26, 4, 21, 65, 22, 49, 11, 16, 8, 12};
    int registros[] = {29, 14, 76, 75, 59, 6, 7, 74, 48, 46, 10, 18, 56, 20, 26, 4, 21, 65, 22, 49, 11, 16, 8, 15, 5, 19};
    int tamanho = sizeof(registros) / sizeof(registros[0]);

    // Escrevendo os registros no arquivo binário
    for (int i = 0; i < tamanho; i++) {
        fwrite(&registros[i], sizeof(int), 1, arquivo);
    }

    fclose(arquivo);
    printf("Arquivo binário de entrada criado com sucesso!\n");
    return 0;
}
