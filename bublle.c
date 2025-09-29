#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char nome[100];
}Nomes;
int main(){
    FILE*arquivo;
    char linha[100], *token;
    char temp[100];
    int i=0;
    Nomes nm[100];
    arquivo=fopen("data_fixed.csv", "r");
    if(arquivo==NULL){
        printf("ERRO!!!!");
        return 1;
    }
    while(fgets(linha, sizeof(linha), arquivo)){
        token= strtok(linha, "\n");
        strcpy(nm[i].nome, token);
        i++;
    }
    printf("Total de registros lidos: %d\n", i);
    fclose(arquivo);
    for(int x=0;x<100;x++){
        printf("%s\n", nm[x].nome);
    }
    //bublle sort
    pintf("\n");
    for(int x=0;x<100;x++){
        printf("%s\n", nm[x].nome);
    }
    return 0;
}
