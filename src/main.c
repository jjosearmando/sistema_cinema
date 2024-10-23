#include "../include/sistema.h"
#include "../include/usuario.h"
#include "../include/filme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    Usuario *usuarios = NULL;
    Filme *filmes = NULL;

    // Carregar usuários e filmes a partir dos arquivos texto
    carregarUsuariosTxt(&usuarios);
    carregarFilmesTxt(&filmes);

    // Verificar se o administrador já existe
    Usuario *atual = usuarios;
    int adminExiste = 0;

    while (atual != NULL) {
        if (strcmp(atual->email, ADMIN_LOGIN) == 0) {
            adminExiste = 1;
            break;
        }
        atual = atual->prox;  // Percorre a lista de usuários
    }

    // Se o administrador não existir, criar um novo usuário administrador
    if (!adminExiste) {
        Usuario *admin = (Usuario *)malloc(sizeof(Usuario));
        if (admin == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
        strcpy(admin->email, ADMIN_LOGIN);
        strcpy(admin->senha, ADMIN_SENHA);
        strcpy(admin->nome, "Administrador");

        // Inserir o administrador no início da lista de usuários
        admin->prox = usuarios;
        usuarios = admin;
    }

    // Exibir o menu principal
    menuPrincipal(&usuarios, &filmes);

    // Salvar os usuários e filmes em arquivos texto
    salvarUsuariosTxt(usuarios);
    salvarFilmesTxt(filmes);

    // Liberar a memória alocada para as listas encadeadas
    Usuario *tempUsuario;
    while (usuarios != NULL) {
        tempUsuario = usuarios;
        usuarios = usuarios->prox;
        free(tempUsuario);
    }

    Filme *tempFilme;
    while (filmes != NULL) {
        tempFilme = filmes;
        filmes = filmes->prox;
        free(tempFilme);
    }

    return 0;
}