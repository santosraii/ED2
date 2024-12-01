#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include "banco.h"

void main() {
    int opcao;
    FILE *arquivoAgencia, *arquivoConta;

    arquivoAgencia = fopen("agencias.dat", "a+b");
    arquivoConta = fopen("contas.dat", "a+b");

    if(!arquivoAgencia || !arquivoConta){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    do{
        printf("\n--- Sistema de Banco ---\n");
        printf("1. Cadastrar Agência\n");
        printf("2. Cadastrar Conta-Corrente\n");
        printf("3. Listar Agencias\n");
        printf("4. Listar Contas\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1: cadastrarAgencia(arquivoAgencia); break;
            case 2: cadastrarConta(arquivoConta); break;
            case 3: lerAgencias(arquivoAgencia); break;
            case 4: lerContas(arquivoConta); break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opção invalida\n");
        }
} while (opcao != 5);

    fclose(arquivoAgencia);
    fclose(arquivoConta);

    return;
}


