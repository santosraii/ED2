#ifndef BANCO_H
#define BANCO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Agencia {
    int cod;
    char nome[50];
    char gerente[50];
} Agencia;

typedef struct ContaCorrente {
    int cod;
    int codAgencia;
    double saldo;
} ContaCorrente;

void cadastrarAgencia(FILE *arquivo);
void cadastrarConta(FILE *arquivo);
void lerAgencias(FILE *arquivo);
void lerContas(FILE *arquivo);

#endif