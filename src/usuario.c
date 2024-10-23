#include "../include/usuario.h"
#include "../include/utils.h"
#include "../include/sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int emailJaCadastrado(Usuario *usuarios, const char *email) {
    Usuario *atual = usuarios;
    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            return 1;
        }
        atual = atual->prox; // Percorre a lista encadeada
    }
    return 0;
}//MODIFICADO

void cadastrarUsuario(Usuario **usuarios) {
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("Nome: ");
    fgets(novoUsuario->nome, MAX_NOME, stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = 0;

    do {
        printf("Email (formato usuario@dominio.com): ");
        fgets(novoUsuario->email, MAX_EMAIL, stdin);
        novoUsuario->email[strcspn(novoUsuario->email, "\n")] = 0;

        if (!validarEmail(novoUsuario->email)) {
            printf("Email inválido! Tente novamente.\n");
        } else if (emailJaCadastrado(*usuarios, novoUsuario->email)) {
            printf("Email já cadastrado! Tente novamente.\n");
        }
    } while (!validarEmail(novoUsuario->email) || emailJaCadastrado(*usuarios, novoUsuario->email));

    printf("Senha: ");
    fgets(novoUsuario->senha, MAX_SENHA, stdin);
    novoUsuario->senha[strcspn(novoUsuario->senha, "\n")] = 0;

    // Inserir o novo usuário no início da lista
    novoUsuario->prox = *usuarios;
    *usuarios = novoUsuario;

    printf("Usuário cadastrado com sucesso!\n");
}//MODIFICADO

int login(Usuario *usuarios) {
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];

    printf("Email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Senha: ");
    fgets(senha, MAX_SENHA, stdin);
    senha[strcspn(senha, "\n")] = 0;

    if (strcmp(email, ADMIN_LOGIN) == 0 && strcmp(senha, ADMIN_SENHA) == 0) {
        mostrarBoasVindas();
        return 2;
    }

    Usuario *atual = usuarios;
    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0 && strcmp(atual->senha, senha) == 0) {
            mostrarBoasVindas();
            return 1;
        }
        atual = atual->prox; // Percorre a lista encadeada
    }

    printf("Email ou senha incorretos!\n");
    return 0;
}//MODIFICADO

void salvarUsuarios(Usuario *usuarios) {
    FILE *file = fopen("data/usuarios.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para salvar usuários!\n");
        return;
    }

    Usuario *atual = usuarios;
    int numUsuarios = 0;

    // Contando o número de usuários
    while (atual != NULL) {
        numUsuarios++;
        atual = atual->prox;
    }

    fwrite(&numUsuarios, sizeof(int), 1, file);

    // Salvando cada usuário
    atual = usuarios;
    while (atual != NULL) {
        fwrite(atual, sizeof(Usuario) - sizeof(Usuario *), 1, file);  // Ignoramos o ponteiro 'prox'
        atual = atual->prox;
    }

    fclose(file);
    printf("Usuários salvos com sucesso!\n");
}//MODIFICADO

void carregarUsuarios(Usuario **usuarios) {
    FILE *file = fopen("data/usuarios.dat", "rb");
    if (file == NULL) {
        printf("Nenhum usuário encontrado. Iniciando novo arquivo.\n");
        return;
    }

    int numUsuarios;
    fread(&numUsuarios, sizeof(int), 1, file);

    Usuario *ultimo = NULL;
    for (int i = 0; i < numUsuarios; i++) {
        Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
        if (novoUsuario == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }

        fread(novoUsuario, sizeof(Usuario) - sizeof(Usuario *), 1, file);
        novoUsuario->prox = NULL;

        if (*usuarios == NULL) {
            *usuarios = novoUsuario;
        } else {
            ultimo->prox = novoUsuario;
        }
        ultimo = novoUsuario;
    }

    fclose(file);
    printf("Usuários carregados com sucesso!\n");
}//MODIFICADO

void carregarUsuariosTxt(Usuario **usuarios) {
    FILE *file = fopen("data/usuarios.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de usuários encontrado. Iniciando novo arquivo.\n");
        return;
    }

    int numUsuarios;
    fscanf(file, "%d\n", &numUsuarios);

    Usuario *ultimo = NULL;
    for (int i = 0; i < numUsuarios; i++) {
        Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
        if (novoUsuario == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }

        fgets(novoUsuario->nome, MAX_NOME, file);
        novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = 0;

        fgets(novoUsuario->email, MAX_EMAIL, file);
        novoUsuario->email[strcspn(novoUsuario->email, "\n")] = 0;

        fgets(novoUsuario->senha, MAX_SENHA, file);
        novoUsuario->senha[strcspn(novoUsuario->senha, "\n")] = 0;

        novoUsuario->prox = NULL;

        if (*usuarios == NULL) {
            *usuarios = novoUsuario;
        } else {
            ultimo->prox = novoUsuario;
        }
        ultimo = novoUsuario;
    }

    fclose(file);
    printf("Usuários carregados com sucesso de formato texto!\n");
}//MODIFICADO

void salvarUsuariosTxt(Usuario *usuarios) {
    FILE *file = fopen("data/usuarios.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para salvar usuários!\n");
        return;
    }

    int numUsuarios = 0;
    Usuario *atual = usuarios;

    // Contando o número de usuários
    while (atual != NULL) {
        numUsuarios++;
        atual = atual->prox;
    }

    fprintf(file, "%d\n", numUsuarios);

    // Salvando cada usuário
    atual = usuarios;
    while (atual != NULL) {
        fprintf(file, "%s\n", atual->nome);
        fprintf(file, "%s\n", atual->email);
        fprintf(file, "%s\n", atual->senha);
        atual = atual->prox;
    }

    fclose(file);
    printf("Usuários salvos com sucesso!\n");
}//MODIFICADO

int compararUsuarios(const void *a, const void *b) {
    Usuario *usuarioA = (Usuario *)a;
    Usuario *usuarioB = (Usuario *)b;
    return strcmp(usuarioA->nome, usuarioB->nome);
}

void ordenarUsuarios(Usuario **usuarios) {
    if (*usuarios == NULL) {
        return;  // Lista vazia, nada a ordenar
    }

    int trocou;
    Usuario *atual;
    Usuario *anterior = NULL;
    Usuario *fim = NULL;

    // Bubble sort adaptado para lista encadeada
    do {
        trocou = 0;
        atual = *usuarios;

        while (atual->prox != fim) {
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                // Se os nomes estão fora de ordem, trocamos os nós
                char tempNome[MAX_NOME];
                char tempEmail[MAX_EMAIL];
                char tempSenha[MAX_SENHA];

                // Trocar nome
                strcpy(tempNome, atual->nome);
                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->prox->nome, tempNome);

                // Trocar email
                strcpy(tempEmail, atual->email);
                strcpy(atual->email, atual->prox->email);
                strcpy(atual->prox->email, tempEmail);

                // Trocar senha
                strcpy(tempSenha, atual->senha);
                strcpy(atual->senha, atual->prox->senha);
                strcpy(atual->prox->senha, tempSenha);

                trocou = 1;  // Houve troca
            }
            atual = atual->prox;
        }
        fim = atual;
    } while (trocou);
}

void buscarUsuario(Usuario *usuarios) {
    char email[MAX_EMAIL];
    printf("Digite o email do usuário que deseja buscar: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;

    Usuario *atual = usuarios;
    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            printf("Usuário encontrado:\n");
            printf("Nome: %s\n", atual->nome);
            printf("Email: %s\n", atual->email);
            return;
        }
        atual = atual->prox;
    }

    printf("Usuário não encontrado.\n");
}//MODIFICADO
