#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMES 100
#define TAM_MAX 100
#define ALCANCE_ASCII 256

void ordenacaoPorContagem(char nomes[MAX_NOMES][TAM_MAX], int n, int pos) {
    char saida[MAX_NOMES][TAM_MAX];
    int contagem[ALCANCE_ASCII] = {0};

    for (int i = 0; i < n; i++) {
        unsigned char c = (pos < (int)strlen(nomes[i])) ? (unsigned char)tolower(nomes[i][pos]) : 0;
        contagem[c]++;
    }

    for (int i = 1; i < ALCANCE_ASCII; i++)
        contagem[i] += contagem[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        unsigned char c = (pos < (int)strlen(nomes[i])) ? (unsigned char)tolower(nomes[i][pos]) : 0;
        strcpy(saida[--contagem[c]], nomes[i]);
    }

    for (int i = 0; i < n; i++)
        strcpy(nomes[i], saida[i]);
}

void ordenarAlfabeticamente(char nomes[MAX_NOMES][TAM_MAX], int n) {
    int tamMax = 0;
    for (int i = 0; i < n; i++) {
        int tam = (int)strlen(nomes[i]);
        if (tam > tamMax)
            tamMax = tam;
    }

    for (int pos = tamMax - 1; pos >= 0; pos--)
        ordenacaoPorContagem(nomes, n, pos);
}

int main(void) {
    FILE *arquivo = fopen("data_fixed.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char nomes[MAX_NOMES][TAM_MAX];
    int qtd = 0;

    while (qtd < MAX_NOMES && fgets(nomes[qtd], sizeof(nomes[qtd]), arquivo)) {

        nomes[qtd][strcspn(nomes[qtd], "\r\n")] = 0;

        if (strlen(nomes[qtd]) == 0)
            continue;

        qtd++;
    }
    fclose(arquivo);

    if (qtd == 0) {
        printf("Nenhum nome encontrado no arquivo.\n");
        return 0;
    }

    ordenarAlfabeticamente(nomes, qtd);

    printf("Nomes ordenados:\n");
    for (int i = 0; i < qtd; i++)
        printf("%s\n", nomes[i]);


    FILE *saida = fopen("ordenado.csv", "w");
    if (!saida) {
        perror("Erro ao escrever em ordenado.csv");
        return 1;
    }
    for (int i = 0; i < qtd; i++)
        fprintf(saida, "%s\n", nomes[i]);
    fclose(saida);

    printf("\nNomes ordenados\n");
    return 0;
}
