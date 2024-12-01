#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_DATA 20

typedef struct {
    int codCliente;
    char nome[MAX_NOME];
    char dataNascimento[MAX_DATA];
} Cliente;

void criarArquivoClientes(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Cliente clientes[] = {
       /* {168, "Raiane", "19/06/2003"}, 
{2, "Sandra", "16/11/1964"},
{433, "Raissa", "02/03/2000"},
{4, "Rafael", "03/07/1993"},
{569, "Carlos", "25/09/1985"},
{6, "Maria", "12/12/1995"},
{764, "Joaquim", "01/01/2001"},
{16, "Luisa", "26/03/2024"},
{8, "Bruno", "15/08/1998"},
{96, "Lucas", "10/05/1990"},
{120, "Bruna", "11/11/1999"},
{345, "Fernanda", "22/02/1987"},
{89, "Aline", "05/06/1992"},
{547, "Pedro", "17/10/1980"},
{31, "Larissa", "08/04/2002"},
{215, "Vitor", "12/01/1998"},
{578, "Camila", "30/03/1995"},
{64, "Gabriel", "29/07/2003"},
{174, "Arthur", "20/09/2000"},
{132, "Mariana", "24/09/1990"},
{663, "Roberto", "15/05/1982"},
{49, "Thiago", "18/07/1997"},
{903, "Juliana", "11/08/1985"},
{27, "André", "25/10/1975"},
{376, "Patrícia", "13/06/1989"},
{108, "Felipe", "22/11/1991"},
{512, "Ana", "06/12/1996"},
{702, "Eduardo", "03/03/1994"},
{15, "Gustavo", "07/02/2000"},
{640, "Isabela", "20/09/1988"},
{224, "Letícia", "14/04/2001"},
{59, "Leonardo", "19/08/1990"},
{298, "Cecília", "30/05/1999"},
{877, "Vinícius", "09/10/1986"}
        
*/
{30, "Raiane", "19/06/2003"}, 
{14, "Sandra", "16/11/1964"},
{15, "Raissa", "02/03/2000"},
{75, "Rafael", "03/07/1993"},
{32, "Carlos", "25/09/1985"},
{6, "Maria", "12/12/1995"},
{5, "Joaquim", "01/01/2001"},
{81, "Luisa", "26/03/2024"},
{48, "Bruno", "15/08/1998"},
{41, "Lucas", "10/05/1990"},
{87, "Bruna", "11/11/1999"},
{18, "Fernanda", "22/02/1987"},
{56, "Aline", "05/06/1992"},
{20, "Pedro", "17/10/1980"},
{26, "Larissa", "08/04/2002"},
{4, "Vitor", "12/01/1998"},
{21, "Camila", "30/03/1995"},
{65, "Gabriel", "29/07/2003"},
{22, "Arthur", "20/09/2000"},
{49, "Mariana", "24/09/1990"},
{11, "Roberto", "15/05/1982"},
{16, "Thiago", "18/07/1997"},
{8, "Juliana", "11/08/1985"},
{12, "André", "25/10/1975"}
    };

    int numClientes = sizeof(clientes) / sizeof(Cliente);
    
    for (int i = 0; i < numClientes; i++) {
        fwrite(&clientes[i], sizeof(Cliente), 1, arquivo);
    }

    fclose(arquivo);
    printf("Arquivo de clientes criado com sucesso!\n");
}

int main() {
    criarArquivoClientes("clientes.bin");
    return 0;
}
