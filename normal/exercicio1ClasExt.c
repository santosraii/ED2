#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define M 7 // número de registros que cabem na memória

typedef struct {
    int chave;
    bool congelado;
} Registro;

void lerRegistrosIniciais(Registro registros[], FILE *entrada) {
    for (int i = 0; i < M; i++) {
        if (fscanf(entrada, "%d", &registros[i].chave) == 1) {
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
    fprintf(saida, "%d\n", registro.chave);
}

void substituirRegistro(Registro registros[], int indice, FILE *entrada) {
    if (fscanf(entrada, "%d", &registros[indice].chave) != 1) {
        registros[indice].chave = INT_MAX; // Define como INT_MAX se não houver mais registros
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
    FILE *entrada = fopen("entrada.txt", "r");
    FILE *saida = NULL;
    Registro registros[M];
    int particao = 1;
    
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    lerRegistrosIniciais(registros, entrada);

    while (true) {
        char nomeArquivoSaida[20];
        sprintf(nomeArquivoSaida, "saida%d.txt", particao);
        saida = fopen(nomeArquivoSaida, "w");
        if (saida == NULL) {
            perror("Erro ao abrir o arquivo de saída");
            fclose(entrada);
            return 1;
        }

        while (!todosRegistrosCongelados(registros)) {
            int indiceMenor = encontrarMenorChave(registros);
            if (indiceMenor == -1) {
                break; // Não há mais registros não congelados
            }
            gravarRegistro(saida, registros[indiceMenor]);

            int chaveAnterior = registros[indiceMenor].chave;
            substituirRegistro(registros, indiceMenor, entrada);
            
            if (registros[indiceMenor].chave < chaveAnterior) {
                registros[indiceMenor].congelado = true; // Congela se a nova chave for menor
            }
        }

        fclose(saida);
        particao++;

        // Checar se existem mais registros disponíveis
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

        // Resetar o estado de congelamento para a próxima partição
        for (int i = 0; i < M; i++) {
            if (registros[i].chave != INT_MAX) {
                registros[i].congelado = false; // Descongela todos os registros não vazios
            }
        }
    }

    fclose(entrada);
    return 0;
}


    //30 14 15 75 32 6 5 81 48 41 87 18 56 20 26 4 21 65 22 49 11 16 8 12
    //29 14 76 75 59 6 7 74 48 46 10 18 56 20 26 4 21 65 22 49 11 16 8 15 5 19