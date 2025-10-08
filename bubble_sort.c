#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[100];
} Nomes;

long long passos = 0;

int main() {
    FILE* arquivo;
    char linha[100];
    char temp[100];
    int i = 0;
    Nomes nm[100];

    arquivo = fopen("data_fixed.csv", "r");
    if (arquivo == NULL) {
        printf("ERRO!!!!");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        strtok(linha, "\n");
        strcpy(nm[i].nome, linha);
        i++;
        passos += strlen(linha);
    }
    fclose(arquivo);

    printf("Total de registros lidos: %d\n", i);

    for (int x = 0; x < i; x++) {
        printf("%s\n", nm[x].nome);
        passos++;
    }

    clock_t inicio = clock();

    for (i = 0; i < 100 - 1; i++) {
        for (int j = 0; j < 100 - i - 1; j++) {
            passos++;
            if (strcmp(nm[j].nome, nm[j + 1].nome) > 0) {
                strcpy(temp, nm[j].nome); passos += strlen(nm[j].nome);
                strcpy(nm[j].nome, nm[j + 1].nome); passos += strlen(nm[j+1].nome);
                strcpy(nm[j + 1].nome, temp); passos += strlen(temp);
            }
        }
    }

    clock_t fim = clock();
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nPalavras ordenadas:\n");
    for (int x = 0; x < 100; x++) {
        printf("%s\n", nm[x].nome);
        passos++;
    }

    arquivo = fopen("ordenado_bs.csv", "w");
    if (arquivo == NULL) {
        printf("ERRO!!!!");
        return 1;
    }
    for (i = 0; i < 100; i++) {
        fprintf(arquivo, "%s\n", nm[i].nome);
        passos++;
    }
    fclose(arquivo);

    printf("\nQuantidade de palavras: %d\n", i);
    printf("Passos de execução: %lld\n", passos);
    printf("Tempo de execução: %.6f segundos\n", tempoExecucao);

    return 0;
}
