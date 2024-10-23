#include "../include/filme.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarFilme(Filme **filmes) {
    Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
    if (novoFilme == NULL) {
        printf("Erro ao alocar memória para o filme!\n");
        return;
    }

    int numHorarios;
    
    // Leitura dos dados do filme
    printf("Nome do Filme: ");
    fgets(novoFilme->nome, MAX_NOME, stdin);
    novoFilme->nome[strcspn(novoFilme->nome, "\n")] = 0;

    printf("Duração (em minutos): ");
    scanf("%d", &novoFilme->duracao);
    getchar();

    printf("Avaliação (0.0 a 10.0): ");
    scanf("%f", &novoFilme->avaliacao);
    getchar();

    printf("Preço do Ingresso: ");
    scanf("%f", &novoFilme->precoIngresso);
    getchar();

    for (int i = 0; i < 7; i++) {
        printf("Quantos horários o filme será exibido no %s? (0 para nenhum): ", diasDaSemana[i]);
        scanf("%d", &numHorarios);
        getchar();

        if (numHorarios > 0) {
            printf("Quantidade de ingressos disponíveis para %s: ", diasDaSemana[i]);
            scanf("%d", &novoFilme->quantidadeIngressosDisponiveis[i]);
            getchar();
        } else {
            novoFilme->quantidadeIngressosDisponiveis[i] = 0;
        }

        for (int j = 0; j < numHorarios; j++) {
            printf("Digite o horário %d (em formato 24h, ex: 1900 para 19:00): ", j + 1);
            scanf("%d", &novoFilme->diasSemana[i][j]);
            getchar();
        }

        for (int j = numHorarios; j < MAX_HORARIOS; j++) {
            novoFilme->diasSemana[i][j] = -1;
        }
    }

    // Inserir no início da lista
    novoFilme->prox = *filmes;
    *filmes = novoFilme;
}//MODIFICADO

void excluirFilme(Filme **filmes) {
    if (*filmes == NULL) {
        printf("Nenhum filme disponível para excluir.\n");
        return;
    }

    verFilmes(*filmes);

    int index;
    printf("Digite o número do filme a ser excluído: ");
    scanf("%d", &index);
    getchar();

    Filme *atual = *filmes;
    Filme *anterior = NULL;

    for (int i = 1; i < index && atual != NULL; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Número inválido!\n");
        return;
    }

    if (anterior == NULL) {
        *filmes = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Filme excluído com sucesso!\n");
}//MODIFICADO

void editarFilme(Filme *filmes) {
    if (filmes == NULL) {
        printf("Nenhum filme disponível para editar.\n");
        return;
    }

    verFilmes(filmes);

    int index;
    printf("Digite o número do filme a ser editado: ");
    scanf("%d", &index);
    getchar();

    Filme *atual = filmes;
    for (int i = 1; i < index && atual != NULL; i++) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Número inválido!\n");
        return;
    }

    // Realizando a edição
    printf("Nome do Filme [%s]: ", atual->nome);
    fgets(atual->nome, MAX_NOME, stdin);
    atual->nome[strcspn(atual->nome, "\n")] = 0;

    printf("Duração (em minutos) [%d]: ", atual->duracao);
    scanf("%d", &atual->duracao);
    getchar();

    printf("Avaliação (0.0 a 10.0) [%.1f]: ", atual->avaliacao);
    scanf("%f", &atual->avaliacao);
    getchar();

    printf("Preço do Ingresso [R$%.2f]: ", atual->precoIngresso);
    scanf("%f", &atual->precoIngresso);
    getchar();

    for (int i = 0; i < 7; i++) {
        printf("Quantidade de Ingressos Disponíveis para %s [%d]: ", diasDaSemana[i], atual->quantidadeIngressosDisponiveis[i]);
        scanf("%d", &atual->quantidadeIngressosDisponiveis[i]);
        getchar();
    }

    printf("Filme editado com sucesso!\n");
}//MODIFICADO

void verFilmes(Filme *filmes) {
    if (filmes == NULL) {
        printf("Nenhum filme disponível no catálogo.\n");
        return;
    }

    int count = 1;
    printf("\n=====================================\n");
    printf("           FILMES DISPONÍVEIS        \n");
    printf("=====================================\n");
    while (filmes != NULL) {
        printf("\nFilme %d: %s\n", count++, filmes->nome);
        printf("Duração: %d minutos\n", filmes->duracao);
        printf("Avaliação: %.1f\n", filmes->avaliacao);
        printf("Preço do Ingresso: R$%.2f\n", filmes->precoIngresso);

        printf("Dias de exibição e horários:\n");
        for (int j = 0; j < 7; j++) {
            if (filmes->quantidadeIngressosDisponiveis[j] > 0) {
                printf("%s: ", diasDaSemana[j]);
                for (int k = 0; k < MAX_HORARIOS; k++) {
                    if (filmes->diasSemana[j][k] != -1) {
                        printf("%d ", filmes->diasSemana[j][k]);
                    }
                }
                printf("\n");
            }
        }

        filmes = filmes->prox;
    }
    printf("=====================================\n");
}//MODIFICADO

void salvarFilmes(Filme *filmes) {
    FILE *file = fopen("data/filmes.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para salvar filmes!\n");
        return;
    }

    int numFilmes = 0;
    Filme *temp = filmes;

    // Contando o número de filmes na lista
    while (temp != NULL) {
        numFilmes++;
        temp = temp->prox;
    }

    fwrite(&numFilmes, sizeof(int), 1, file);

    // Salvando cada filme
    while (filmes != NULL) {
        fwrite(filmes, sizeof(Filme) - sizeof(Filme*), 1, file);  // Ignoramos o ponteiro 'prox'
        filmes = filmes->prox;
    }

    fclose(file);
    printf("Filmes salvos com sucesso!\n");
}//MODIFICADO

void carregarFilmes(Filme **filmes) {
    FILE *file = fopen("data/filmes.dat", "rb");
    if (file == NULL) {
        printf("Nenhum filme encontrado. Iniciando novo arquivo.\n");
        return;
    }

    int numFilmes;
    fread(&numFilmes, sizeof(int), 1, file);

    Filme *ultimo = NULL;
    for (int i = 0; i < numFilmes; i++) {
        Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
        if (novoFilme == NULL) {
            printf("Erro ao alocar memória para carregar filmes!\n");
            exit(1);
        }

        fread(novoFilme, sizeof(Filme) - sizeof(Filme*), 1, file);
        novoFilme->prox = NULL;

        if (*filmes == NULL) {
            *filmes = novoFilme;
        } else {
            ultimo->prox = novoFilme;
        }
        ultimo = novoFilme;
    }

    fclose(file);
    printf("Filmes carregados com sucesso!\n");
}//MODIFICADO

void comprarIngresso(Filme *filmes) {
    if (filmes == NULL) {
        printf("Nenhum filme disponível para compra.\n");
        return;
    }

    verFilmes(filmes);

    int filmeIndex;
    printf("Digite o número do filme para o qual deseja comprar ingresso: ");
    scanf("%d", &filmeIndex);
    getchar();

    Filme *filmeEscolhido = filmes;
    for (int i = 1; i < filmeIndex && filmeEscolhido != NULL; i++) {
        filmeEscolhido = filmeEscolhido->prox;
    }

    if (filmeEscolhido == NULL) {
        printf("Número de filme inválido!\n");
        return;
    }

    printf("Escolha o dia da semana para a sessão (1-Domingo a 7-Sábado): ");
    int diaIndex = lerOpcao(1, 7) - 1;

    if (filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex] == 0) {
        printf("Nenhuma sessão disponível neste dia.\n");
        return;
    }

    printf("Horários disponíveis para %s:\n", diasDaSemana[diaIndex]);
    int horarioValido = 0;
    for (int i = 0; i < MAX_HORARIOS; i++) {
        if (filmeEscolhido->diasSemana[diaIndex][i] != -1) {
            horarioValido++;
            printf("%d. %d\n", horarioValido, filmeEscolhido->diasSemana[diaIndex][i]);
        }
    }

    if (horarioValido == 0) {
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

    if (quantidadeIngressos > filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex]) {
        printf("Não há ingressos suficientes disponíveis. Tente novamente.\n");
        return;
    }

    filmeEscolhido->quantidadeIngressosDisponiveis[diaIndex] -= quantidadeIngressos;
    printf("Compra realizada com sucesso! Você comprou %d ingresso(s) para o filme '%s' no dia %s às %d.\n", 
            quantidadeIngressos, filmeEscolhido->nome, diasDaSemana[diaIndex], filmeEscolhido->diasSemana[diaIndex][horarioIndex]);
}//MODIFICADO

void salvarFilmesTxt(Filme *filmes) {
    FILE *file = fopen("data/filmes.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para salvar filmes em formato texto!\n");
        return;
    }

    int numFilmes = 0;
    Filme *temp = filmes;

    // Contando o número de filmes na lista
    while (temp != NULL) {
        numFilmes++;
        temp = temp->prox;
    }

    fprintf(file, "%d\n", numFilmes);

    // Salvando cada filme
    while (filmes != NULL) {
        fprintf(file, "%s\n", filmes->nome);
        fprintf(file, "%d\n", filmes->duracao);
        fprintf(file, "%.1f\n", filmes->avaliacao);
        fprintf(file, "%.2f\n", filmes->precoIngresso);

        for (int i = 0; i < 7; i++) {
            if (filmes->quantidadeIngressosDisponiveis[i] > 0) {
                fprintf(file, "%s\n", diasDaSemana[i]);
                fprintf(file, "%d\n", filmes->quantidadeIngressosDisponiveis[i]);
                for (int j = 0; j < MAX_HORARIOS; j++) {
                    if (filmes->diasSemana[i][j] != -1) {
                        fprintf(file, "%d ", filmes->diasSemana[i][j]);
                    }
                }
                fprintf(file, "\n");
            }
        }

        filmes = filmes->prox;
        if (filmes != NULL) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("Filmes salvos com sucesso em formato texto!\n");
}//MODIFICADO

void carregarFilmesTxt(Filme **filmes) {
    FILE *file = fopen("data/filmes.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de filmes encontrado em formato texto. Iniciando novo arquivo.\n");
        return;
    }

    int numFilmes;
    fscanf(file, "%d\n", &numFilmes);

    Filme *ultimo = NULL;
    for (int i = 0; i < numFilmes; i++) {
        Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
        if (novoFilme == NULL) {
            printf("Erro ao alocar memória para carregar filmes!\n");
            exit(1);
        }

        fgets(novoFilme->nome, MAX_NOME, file);
        novoFilme->nome[strcspn(novoFilme->nome, "\n")] = 0;

        fscanf(file, "%d\n", &novoFilme->duracao);
        fscanf(file, "%f\n", &novoFilme->avaliacao);
        fscanf(file, "%f\n", &novoFilme->precoIngresso);

        for (int j = 0; j < 7; j++) {
            novoFilme->quantidadeIngressosDisponiveis[j] = 0;
            for (int k = 0; k < MAX_HORARIOS; k++) {
                novoFilme->diasSemana[j][k] = -1;
            }
        }

        char diaSemana[20];
        while (fgets(diaSemana, sizeof(diaSemana), file) && strcmp(diaSemana, "\n") != 0) {
            diaSemana[strcspn(diaSemana, "\n")] = 0;

            int diaIndex = -1;
            for (int j = 0; j < 7; j++) {
                if (strcmp(diaSemana, diasDaSemana[j]) == 0) {
                    diaIndex = j;
                    break;
                }
            }

            if (diaIndex != -1) {
                fscanf(file, "%d\n", &novoFilme->quantidadeIngressosDisponiveis[diaIndex]);

                char horariosLinha[100];
                fgets(horariosLinha, sizeof(horariosLinha), file);

                char *token = strtok(horariosLinha, " ");
                int k = 0;
                while (token != NULL) {
                    int horario = atoi(token);
                    if (horario != -1) {
                        novoFilme->diasSemana[diaIndex][k++] = horario;
                    }
                    token = strtok(NULL, " ");
                }
            }
        }

        novoFilme->prox = NULL;

        if (*filmes == NULL) {
            *filmes = novoFilme;
        } else {
            ultimo->prox = novoFilme;
        }
        ultimo = novoFilme;
    }

    fclose(file);
    printf("Filmes carregados com sucesso de formato texto!\n");
}//MODIFICADO

int compararFilmes(const void *a, const void *b) {
    Filme *filmeA = *(Filme **)a;
    Filme *filmeB = *(Filme **)b;
    return strcmp(filmeA->nome, filmeB->nome);
}//MODIFICADO

void ordenarFilmes(Filme **filmes) {
    // Contar o número de filmes
    int numFilmes = 0;
    Filme *temp = *filmes;
    while (temp != NULL) {
        numFilmes++;
        temp = temp->prox;
    }

    if (numFilmes < 2) {
        printf("A lista já está ordenada ou contém apenas um filme.\n");
        return;
    }

    // Criar um array de ponteiros para os filmes
    Filme **filmeArray = (Filme **)malloc(numFilmes * sizeof(Filme *));
    if (filmeArray == NULL) {
        printf("Erro ao alocar memória para ordenação de filmes!\n");
        return;
    }

    temp = *filmes;
    for (int i = 0; i < numFilmes; i++) {
        filmeArray[i] = temp;
        temp = temp->prox;
    }

    // Ordenar o array de filmes
    qsort(filmeArray, numFilmes, sizeof(Filme *), compararFilmes);

    // Remontar a lista encadeada
    *filmes = filmeArray[0];
    for (int i = 0; i < numFilmes - 1; i++) {
        filmeArray[i]->prox = filmeArray[i + 1];
    }
    filmeArray[numFilmes - 1]->prox = NULL;

    free(filmeArray);
    printf("Filmes ordenados com sucesso!\n");
}//MODIFICADO

void buscarFilme(Filme *filmes) {
    char nome[MAX_NOME];
    printf("Digite o nome do filme que deseja buscar: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    Filme *atual = filmes;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Filme encontrado:\n");
            printf("Nome: %s\n", atual->nome);
            printf("Duração: %d minutos\n", atual->duracao);
            printf("Avaliação: %.1f\n", atual->avaliacao);
            printf("Preço do Ingresso: R$%.2f\n", atual->precoIngresso);
            return;
        }
        atual = atual->prox;
    }

    printf("Filme não encontrado.\n");
}//MODIFICADO
