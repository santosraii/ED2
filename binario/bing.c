#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define M 7 // número de registros que cabem na memória

typedef struct {
    int chave;
    bool congelado;
} Registro;

void lerRegistrosIniciais(Registro registros[], FILE *entrada) {
    for (int i = 0; i < M; i++) {
        if (fread(&registros[i].chave, sizeof(int), 1, entrada) == 1) {
            registros[i].congelado = false;
        } else {
            registros[i].chave = INT_MAX;
            registros[i].congelado = true;
        }
    }
}

int encontrarMenorChave(Registro registros[]) {
    int menorChave = INT_MAX;
    int indiceMenor = -1;
    for (int i = 0; i < M; i++) {
        if (!registros[i].congelado && registros[i].chave < menorChave) {
            menorChave = registros[i].chave;
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

void gravarRegistro(FILE *saida, Registro registro) {
    fwrite(&registro.chave, sizeof(int), 1, saida);
}

void substituirRegistro(Registro registros[], int indice, FILE *entrada) {
    if (fread(&registros[indice].chave, sizeof(int), 1, entrada) != 1) {
        registros[indice].chave = INT_MAX;
    }
}

bool todosRegistrosCongelados(Registro registros[]) {
    for (int i = 0; i < M; i++) {
        if (!registros[i].congelado && registros[i].chave != INT_MAX) {
            return false;
        }
    }
    return true;
}

int main() {
    FILE *entrada = fopen("entrada.bin", "rb");
    FILE *saida = NULL;
    Registro registros[M];
    int particao = 1;
    int indiceMenor, registrosCongelados;
    
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    lerRegistrosIniciais(registros, entrada);

    while (1) {
        char nomeArquivoSaida[20];
        sprintf(nomeArquivoSaida, "saida%d.bin", particao);
        saida = fopen(nomeArquivoSaida, "wb");
        if (saida == NULL) {
            perror("Erro ao abrir o arquivo de saída");
            fclose(entrada);
            return 1;
        }

        registrosCongelados = 0;

        while (!todosRegistrosCongelados(registros)) {
            indiceMenor = encontrarMenorChave(registros);
            if (indiceMenor == -1) {
                break;
            }
            gravarRegistro(saida, registros[indiceMenor]);

            int chaveAnterior = registros[indiceMenor].chave;
            substituirRegistro(registros, indiceMenor, entrada);
            
            if (registros[indiceMenor].chave < chaveAnterior) {
                registros[indiceMenor].congelado = true;
                registrosCongelados++;
            }
        }

        fclose(saida);
        particao++;

        bool maisRegistros = false;
        for (int i = 0; i < M; i++) {
            if (registros[i].chave != INT_MAX) {
                maisRegistros = true;
                break;
            }
        }

        if (!maisRegistros) {
            break;
        }

        for (int i = 0; i < M; i++) {
            registros[i].congelado = false;
        }
    }

    fclose(entrada);
    return 0;
}
