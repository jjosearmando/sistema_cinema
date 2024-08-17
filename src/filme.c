#include "filme.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarFilme(Filme **filmes, int *numFilmes){
    Filme novoFilme;
    int numHorarios;

    printf("Nome do Filme: ");
    fgets(novoFilme.nome, MAX_NOME, stdin);
    novoFilme.nome[strcspn(novoFilme.nome, "\n")] = 0;

    printf("Duração (em minutos): ");
    scanf("%d", &novoFilme.duracao);
    getchar();

    printf("Avaliação (0.0 a 10.0): ");
    scanf("%f", &novoFilme.avaliacao);
    getchar();

    printf("Preço do Ingresso: ");
    scanf("%f", &novoFilme.precoIngresso);
    getchar();

    for(int i = 0; i < 7; i++){
        printf("Quantos horários o filme será exibido no %s? (0 para nenhum): ", diasDaSemana[i]);
        scanf("%d", &numHorarios);
        getchar();

        if(numHorarios > 0){
            printf("Quantidade de ingressos disponíveis para %s: ", diasDaSemana[i]);
            scanf("%d", &novoFilme.quantidadeIngressosDisponiveis[i]);
            getchar();
        } 
        else{
            novoFilme.quantidadeIngressosDisponiveis[i] = 0;
        }

        for(int j = 0; j < numHorarios; j++){
            printf("Digite o horário %d (em formato 24h, ex: 1900 para 19:00): ", j + 1);
            scanf("%d", &novoFilme.diasSemana[i][j]);
            getchar();
        }

        for(int j = numHorarios; j < MAX_HORARIOS; j++){
            novoFilme.diasSemana[i][j] = -1;
        }
    }

    *filmes = realloc(*filmes, (*numFilmes + 1) * sizeof(Filme));
    if(*filmes == NULL){
        printf("Erro ao alocar memória para o array de filmes!\n");
        return;
    }

    (*filmes)[*numFilmes] = novoFilme;
    (*numFilmes)++;
}

void excluirFilme(Filme **filmes, int *numFilmes){
    if(*numFilmes == 0){
        printf("Nenhum filme disponível para excluir.\n");
        return;
    }

    verFilmes(*filmes, *numFilmes);

    int index;
    printf("Digite o número do filme a ser excluído (1 a %d): ", *numFilmes);
    scanf("%d", &index);
    getchar();

    if(index < 1 || index > *numFilmes){
        printf("Número inválido!\n");
        return;
    }

    index--;

    for(int i = index; i < (*numFilmes) - 1; i++){
        (*filmes)[i] = (*filmes)[i + 1];
    }

    *filmes = realloc(*filmes, (*numFilmes - 1) * sizeof(Filme));
    if(*filmes == NULL && *numFilmes > 1){
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    (*numFilmes)--;
    printf("Filme excluído com sucesso!\n");
}

void editarFilme(Filme *filmes, int numFilmes){
    if(numFilmes == 0){
        printf("Nenhum filme disponível para editar.\n");
        return;
    }

    verFilmes(filmes, numFilmes);

    int index;
    printf("Digite o número do filme a ser editado (1 a %d): ", numFilmes);
    scanf("%d", &index);
    getchar();

    if(index < 1 || index > numFilmes){
        printf("Número inválido!\n");
        return;
    }

    index--;

    printf("Nome do Filme [%s]: ", filmes[index].nome);
    fgets(filmes[index].nome, MAX_NOME, stdin);
    filmes[index].nome[strcspn(filmes[index].nome, "\n")] = 0;

    printf("Duração (em minutos) [%d]: ", filmes[index].duracao);
    scanf("%d", &filmes[index].duracao);
    getchar();

    printf("Avaliação (0.0 a 10.0) [%.1f]: ", filmes[index].avaliacao);
    scanf("%f", &filmes[index].avaliacao);
    getchar();

    printf("Preço do Ingresso [R$%.2f]: ", filmes[index].precoIngresso);
    scanf("%f", &filmes[index].precoIngresso);
    getchar();

    for(int i = 0; i < 7; i++){
        printf("Quantidade de Ingressos Disponíveis para %s [%d]: ", diasDaSemana[i], filmes[index].quantidadeIngressosDisponiveis[i]);
        scanf("%d", &filmes[index].quantidadeIngressosDisponiveis[i]);
        getchar();
    }

    printf("Filme editado com sucesso!\n");
}

void verFilmes(Filme *filmes, int numFilmes){
    if(numFilmes == 0){
        printf("Nenhum filme disponível no catálogo.\n");
        return;
    }

    printf("\n=====================================\n");
    printf("           FILMES DISPONÍVEIS        \n");
    printf("=====================================\n");
    for(int i = 0; i < numFilmes; i++){
        printf("\nFilme %d: %s\n", i + 1, filmes[i].nome); 
        printf("Duração: %d minutos\n", filmes[i].duracao);
        printf("Avaliação: %.1f\n", filmes[i].avaliacao);
        printf("Preço do Ingresso: R$%.2f\n", filmes[i].precoIngresso);

        printf("Dias de exibição e horários:\n");
        for(int j = 0; j < 7; j++){
            if(filmes[i].quantidadeIngressosDisponiveis[j] > 0){
                printf("%s: ", diasDaSemana[j]);
                for(int k = 0; k < MAX_HORARIOS; k++){
                    if(filmes[i].diasSemana[j][k] != -1){
                        printf("%d ", filmes[i].diasSemana[j][k]);  // Exibe o horário válido
                    }
                }
                printf("\n");
            }
        }
    }
    printf("=====================================\n");
}

void salvarFilmes(Filme *filmes, int numFilmes){
    FILE *file = fopen("data/filmes.dat", "wb");
    if(file == NULL){
        printf("Erro ao abrir arquivo para salvar filmes!\n");
        return;
    }

    fwrite(&numFilmes, sizeof(int), 1, file);

    for(int i = 0; i < numFilmes; i++){
        fwrite(&filmes[i], sizeof(Filme), 1, file);
    }

    fclose(file);
}

void carregarFilmes(Filme **filmes, int *numFilmes){
    FILE *file = fopen("data/filmes.dat", "rb");
    if(file == NULL){
        printf("Nenhum filme encontrado. Iniciando novo arquivo.\n");
        return;
    }

    fread(numFilmes, sizeof(int), 1, file);
    *filmes = malloc(*numFilmes * sizeof(Filme));
    if(*filmes == NULL){
        printf("Erro ao alocar memória para carregar filmes!\n");
        exit(1);
    }

    fread(*filmes, sizeof(Filme), *numFilmes, file);

    fclose(file);
}

void comprarIngresso(Filme *filmes, int numFilmes){
    if(numFilmes == 0){
        printf("Nenhum filme disponível para compra.\n");
        return;
    }

    verFilmes(filmes, numFilmes);

    int filmeIndex;
    printf("Digite o número do filme para o qual deseja comprar ingresso (1 a %d): ", numFilmes);
    filmeIndex = lerOpcao(1, numFilmes) - 1;

    Filme *filmeEscolhido = &filmes[filmeIndex];

    printf("Escolha o dia da semana para a sessão (1-Domingo a 7-Sábado): ");
    int diaIndex = lerOpcao(1, 7) - 1;

    if(filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex] == 0){
        printf("Nenhuma sessão disponível neste dia.\n");
        return;
    }

    printf("Horários disponíveis para %s:\n", diasDaSemana[diaIndex]);
    int horarioValido = 0;
    for(int i = 0; i < MAX_HORARIOS; i++){
        if(filmeEscolhido->diasSemana[diaIndex][i] != -1){
            horarioValido++;
            printf("%d. %d\n", horarioValido, filmeEscolhido->diasSemana[diaIndex][i]);
        }
    }

    if(horarioValido == 0){
        printf("Nenhum horário disponível para esse dia.\n");
        return;
    }

    int horarioIndex;
    printf("Escolha o horário da sessão: ");
    horarioIndex = lerOpcao(1, horarioValido) - 1;

    int quantidadeIngressos;
    printf("Quantidade de ingressos para comprar: ");
    scanf("%d", &quantidadeIngressos);
    getchar();

    if(quantidadeIngressos > filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex]){
        printf("Não há ingressos suficientes disponíveis. Tente novamente.\n");
        return;
    }

    filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex] -= quantidadeIngressos;
    printf("Compra realizada com sucesso! Você comprou %d ingresso(s) para o filme '%s' no dia %s às %d.\n", 
            quantidadeIngressos, filmeEscolhido->nome, diasDaSemana[diaIndex], filmeEscolhido->diasSemana[diaIndex][horarioIndex]);
}
