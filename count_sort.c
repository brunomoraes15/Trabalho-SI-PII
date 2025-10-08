#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>  // para medir o tempo de execução

#define MAX_PALAVRAS 100
#define TAM_MAX 100
#define ALCANCE_ASCII 256  // tamanho do vetor de contagem (0-255)

long long passos = 0;  // contador global de passos

// Função que remove apenas espaços no início e no fim (mantém espaços internos)

void removerEspacos(char *str) {
    char *inicio = str;
    while (isspace((unsigned char)*inicio))
        inicio++;

    char *fim = inicio + strlen(inicio);
    while (fim > inicio && isspace((unsigned char)*(fim - 1)))
        fim--;

    *fim = '\0';
    if (inicio != str)
        memmove(str, inicio, fim - inicio + 1);
    passos += strlen(str); // contar operações de limpeza
}

// Ordenação Counting Sort considerando apenas a primeira letra
void countingSortPrimeiraLetra(char arr[MAX_PALAVRAS][TAM_MAX], int n) {
    char saida[MAX_PALAVRAS][TAM_MAX];
    int contagem[ALCANCE_ASCII] = {0};

    // Etapa 1: contar frequência da primeira letra
    for (int i = 0; i < n; i++) {
        unsigned char c = (unsigned char)tolower(arr[i][0]);
        contagem[c]++;
        passos += 3; // acesso + conversão + incremento
    }

    // Etapa 2: somar contagem cumulativa
    for (int i = 1; i < ALCANCE_ASCII; i++) {
        contagem[i] += contagem[i - 1];
        passos += 2; // soma + atribuição
    }

    // Etapa 3: colocar nomes em suas posições (estável)
    for (int i = n - 1; i >= 0; i--) {
        unsigned char c = (unsigned char)tolower(arr[i][0]);
        strcpy(saida[--contagem[c]], arr[i]);
        passos += strlen(arr[i]); // cópia de caracteres
    }

    // Etapa 4: copiar de volta para o array original
    for (int i = 0; i < n; i++) {
        strcpy(arr[i], saida[i]);
        passos += strlen(arr[i]);
    }
}

int main() {
    FILE *arquivo = fopen("data_fixed.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    char linha[10000];
    char palavras[MAX_PALAVRAS][TAM_MAX];
    int qtd = 0;

    // Leitura do arquivo (1 ou mais linhas com vírgulas)
    while (fgets(linha, sizeof(linha), arquivo) && qtd < MAX_PALAVRAS) {
        char *token = strtok(linha, ",");  // separa apenas por vírgulas
        while (token && qtd < MAX_PALAVRAS) {
            removerEspacos(token);
            if (strlen(token) > 0)
                strncpy(palavras[qtd++], token, TAM_MAX - 1);
            token = strtok(NULL, ",");
            passos += 3; // tokenização + verificação + incremento
        }
    }
    fclose(arquivo);

    if (qtd == 0) {
        printf("Nenhuma palavra encontrada no arquivo.\n");
        return 0;
    }


    // Inicia o cronômetro
    clock_t inicio = clock();

    // Ordena usando Counting Sort (primeira letra)
    countingSortPrimeiraLetra(palavras, qtd);

    // Para o cronômetro
    clock_t fim = clock();
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Exibe resultados
    printf("Palavras ordenadas parcialmente (primeira letra):\n");
    for (int i = 0; i < qtd; i++)
        printf("%s\n", palavras[i]);

    // Salva em arquivo
    FILE *saida = fopen("ordenado_cs.csv", "w");
    if (!saida) {
        perror("Erro ao criar o arquivo de saída");
        return 1;
    }
    for (int i = 0; i < qtd; i++)
        fprintf(saida, "%s\n", palavras[i]);
    fclose(saida);

    printf("Quantidade de palavras: %d\n", qtd);
    printf("Passos de execução: %lld\n", passos);
    printf("Tempo de execução: %.6f segundos\n", tempoExecucao);

    return 0;
}
