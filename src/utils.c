#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *diasDaSemana[] = {
    "Domingo",
    "Segunda-feira",
    "Terça-feira",
    "Quarta-feira",
    "Quinta-feira",
    "Sexta-feira",
    "Sábado"
};

int validarEmail(const char *email){
    int len = strlen(email);

    if(len >= 81){
        return 0;
    }

    char *atSymbol = strchr(email, '@');
    if(atSymbol == NULL || atSymbol == email){
        return 0;
    }

    char *dot = strrchr(atSymbol, '.');
    if(dot == NULL || dot == atSymbol + 1 || dot == email + len - 1){
        return 0;
    }

    if(strlen(dot + 1) < 2){
        return 0;
    }

    for(const char *ptr = email; *ptr; ptr++){
        if(!isalnum(*ptr) && *ptr != '@' && *ptr != '.' && *ptr != '-' && *ptr != '_'){
            return 0;
        }
    }

    return 1;
}

int validarEntrada(int opcao, int min, int max){
    if(opcao < min || opcao > max){
        printf("Opção inválida! Escolha um valor entre %d e %d.\n", min, max);
        return 0;
    }
    return 1;
}

int lerOpcao(int min, int max){
    char entrada[100];
    int opcao;
    char *endptr;

    while(1){
        printf("Escolha uma opção: ");
        if(fgets(entrada, sizeof(entrada), stdin) == NULL){
            printf("Erro ao ler entrada.\n");
            continue;
        }

        entrada[strcspn(entrada, "\n")] = 0;

        opcao = strtol(entrada, &endptr, 10);

        if(*endptr == '\0' && opcao >= min && opcao <= max){
            return opcao;
        } 
        else{
            printf("Entrada inválida. Por favor, insira um número entre %d e %d.\n", min, max);
        }
    }
}
