#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_DATA 20

typedef struct {
    int CodCliente;
    char Nome[MAX_NOME];
    char DataNascimento[MAX_DATA];
} Cliente;

void imprimirConteudoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Cliente cliente;
    printf("Conteúdo do arquivo %s:\n", nomeArquivo);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        printf("CodCliente: %d, Nome: %s, DataNascimento: %s\n", 
               cliente.CodCliente, cliente.Nome, cliente.DataNascimento);
    }

    fclose(arquivo);
}

int main() {
    char *arquivoSaida = "resultado_final.bin";

    // Chama a função para imprimir o conteúdo do arquivo binário
    imprimirConteudoArquivo(arquivoSaida);

    return 0;
}
