#include "usuario.h"
#include "utils.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int emailJaCadastrado(Usuario *usuarios, int numUsuarios, const char *email){
    for(int i = 0; i < numUsuarios; i++){
        if(strcmp(usuarios[i].email, email) == 0){
            return 1;
        }
    }
    return 0;
}

void cadastrarUsuario(Usuario **usuarios, int *numUsuarios){
    Usuario novoUsuario;
    printf("Nome: ");
    fgets(novoUsuario.nome, MAX_NOME, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;

    do{
        printf("Email (formato usuario@dominio.com): ");
        fgets(novoUsuario.email, MAX_EMAIL, stdin);
        novoUsuario.email[strcspn(novoUsuario.email, "\n")] = 0;

        if(!validarEmail(novoUsuario.email)){
            printf("Email inválido! Tente novamente.\n");
        } 
        else if(emailJaCadastrado(*usuarios, *numUsuarios, novoUsuario.email)){
            printf("Email já cadastrado! Tente novamente.\n");
        }
    }while(!validarEmail(novoUsuario.email) || emailJaCadastrado(*usuarios, *numUsuarios, novoUsuario.email));

    printf("Senha: ");
    fgets(novoUsuario.senha, MAX_SENHA, stdin);
    novoUsuario.senha[strcspn(novoUsuario.senha, "\n")] = 0;

    *usuarios = realloc(*usuarios, (*numUsuarios + 1) * sizeof(Usuario));
    if(*usuarios == NULL){
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    (*usuarios)[*numUsuarios] = novoUsuario;
    (*numUsuarios)++;
    printf("Usuário cadastrado com sucesso!\n");
}

int login(Usuario *usuarios, int numUsuarios){
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    printf("Email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Senha: ");
    fgets(senha, MAX_SENHA, stdin);
    senha[strcspn(senha, "\n")] = 0;

    if(strcmp(email, ADMIN_LOGIN) == 0 && strcmp(senha, ADMIN_SENHA) == 0){
        mostrarBoasVindas();
        return 2;
    }

    for(int i = 0; i < numUsuarios; i++){
        if(strcmp(usuarios[i].email, email) == 0 && strcmp(usuarios[i].senha, senha) == 0){
            mostrarBoasVindas();
            return 1; 
        }
    }

    printf("Email ou senha incorretos!\n");
    return 0;
}

void salvarUsuarios(Usuario *usuarios, int numUsuarios){

    FILE *file = fopen("data/usuarios.dat", "wb");
    if(file == NULL){
        printf("Erro ao abrir arquivo para salvar usuários!\n");
        return;
    }
    fwrite(&numUsuarios, sizeof(int), 1, file);
    fwrite(usuarios, sizeof(Usuario), numUsuarios, file);
    fclose(file);
}

void carregarUsuarios(Usuario **usuarios, int *numUsuarios){
    FILE *file = fopen("data/usuarios.dat", "rb");
    if(file == NULL){
        printf("Nenhum usuário encontrado. Iniciando novo arquivo.\n");
        return;
    }
    fread(numUsuarios, sizeof(int), 1, file);
    *usuarios = malloc(*numUsuarios * sizeof(Usuario));
    if(*usuarios == NULL){
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    fread(*usuarios, sizeof(Usuario), *numUsuarios, file);
    fclose(file);
}