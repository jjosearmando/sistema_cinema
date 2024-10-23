#include "../include/sistema.h"
#include "../include/usuario.h"
#include "../include/filme.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

void mostrarBoasVindas() {
    printf("Bem-vindo ao Cinema, aproveite sua sessão!\n");
}

void menuPrincipal(Usuario **usuarios, Filme **filmes) {
    int opcao;
    do {
        printf("\nSistema de Cinema\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");

        opcao = lerOpcao(1, 3);

        if (opcao == 1) {
            cadastrarUsuario(usuarios);  // Passa o ponteiro para a lista de usuários
        } else if (opcao == 2) {
            int loginResult = login(*usuarios);  // Passa a lista de usuários para login
            if (loginResult == 2) {
                menuAdministrador(usuarios, filmes);  // Passa as listas para o menu administrador
            } else if (loginResult == 1) {
                menuUsuario(*filmes);  // Passa a lista de filmes para o menu de usuário
            }
        }
    } while (opcao != 3);

    printf("Saindo do sistema...\n");
}

void menuAdministrador(Usuario **usuarios, Filme **filmes) {
    int opcao;
    do {
        printf("\nMenu Administrador:\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Listar Filmes\n");
        printf("3. Editar Filme\n");
        printf("4. Excluir Filme\n");
        printf("5. Buscar Filme\n");
        printf("6. Buscar Usuário\n");
        printf("7. Sair\n");

        opcao = lerOpcao(1, 7);

        switch (opcao) {
            case 1:
                adicionarFilme(filmes);  // Passa o ponteiro para a lista de filmes
                break;
            case 2:
                verFilmes(*filmes);  // Passa a lista de filmes
                break;
            case 3:
                editarFilme(*filmes);  // Passa a lista de filmes
                break;
            case 4:
                excluirFilme(filmes);  // Passa o ponteiro para a lista de filmes
                break;
            case 5:
                buscarFilme(*filmes);  // Passa a lista de filmes
                break;
            case 6:
                buscarUsuario(*usuarios);  // Passa a lista de usuários
                break;
            case 7:
                printf("Saindo do menu administrador...\n");
                break;
        }
    } while (opcao != 7);
}

void menuUsuario(Filme *filmes) {
    int opcao;
    do {
        printf("\nMenu Usuário:\n");
        printf("1. Ver Filmes do Catálogo\n");
        printf("2. Comprar Ingresso\n");
        printf("3. Buscar Filme\n");
        printf("4. Sair\n");

        opcao = lerOpcao(1, 4);

        switch (opcao) {
            case 1:
                verFilmes(filmes);  // Passa a lista de filmes
                break;
            case 2:
                comprarIngresso(filmes);  // Passa a lista de filmes
                break;
            case 3:
                buscarFilme(filmes);  // Passa a lista de filmes
                break;
            case 4:
                printf("Saindo...\n");
                break;
        }
    } while (opcao != 4);
}
