#include "banco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarAgencia (FILE *arquivo){
    Agencia ag;
    printf("*******************************************************************\n");
    printf("Digite o código da agência: ");
    scanf("%d", &ag.cod);

    printf("Digite o nome da agência: ");
    scanf(" %[^\n]", ag.nome);

    printf("Digite o nome do gerente: ");
    scanf(" %[^\n]", ag.gerente);

    fwrite(&ag, sizeof(Agencia), 1, arquivo);
    printf("Agência cadastrada com sucesso!\n");

    printf("*******************************************************************\n");
}

void cadastrarConta(FILE *arquivo){
    ContaCorrente cc;
    printf("*******************************************************************\n");
    printf("Digite o código da conta: ");
    scanf("%d", &cc.cod);

    printf("Digite o código da agência: ");
    scanf("%d", &cc.codAgencia);

    printf("Digite o saldo inicial da conta: ");
    scanf("%lf", &cc.saldo);

    fwrite(&cc, sizeof(ContaCorrente), 1, arquivo);
    printf("Conta corrente cadastrada com sucesso!\n");

    printf("*******************************************************************\n");

}

void lerAgencias(FILE *arquivo){
    Agencia ag;

    rewind(arquivo);
    printf("\n--- Agências Cadastradas ---\n");

    while(fread(&ag, sizeof(Agencia), 1, arquivo)){
        printf("Cod: %d\nNome: %s\nGerente: %s\n\n", ag.cod, ag.nome, ag.gerente);
    }
}

void lerContas(FILE *arquivo){
    ContaCorrente cc;

    rewind(arquivo);
    printf("\n--- Contas Cadastradas ---\n");

    while(fread(&cc, sizeof(ContaCorrente), 1, arquivo)){
        printf("Cod: %d\nAgencia: %d\nSaldo: %.2lf\n\n", cc.cod, cc.codAgencia, cc.saldo);
    }
}