#include "sistema.h"
#include "usuario.h"
#include "filme.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void mostrarBoasVindas() {
    printf("Bem-vindo ao Cinema, aproveite sua sessão!\n");
}

void menuPrincipal(Usuario **usuarios, int *numUsuarios, Filme **filmes, int *numFilmes) {
    int opcao;
    do {
        printf("\nSistema de Cinema\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");

        opcao = lerOpcao(1, 3);

        if (opcao == 1) {
            cadastrarUsuario(usuarios, numUsuarios);
        } else if (opcao == 2) {
            int loginResult = login(*usuarios, *numUsuarios);
            if (loginResult == 2) {
                menuAdministrador(usuarios, numUsuarios, filmes, numFilmes);
            } else if (loginResult == 1) {
                menuUsuario(*filmes, *numFilmes);
            }
        }
    } while (opcao != 3);

    printf("Saindo do sistema...\n");
}

void menuAdministrador(Usuario **usuarios, int *numUsuarios, Filme **filmes, int *numFilmes) {
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
                adicionarFilme(filmes, numFilmes);
                break;
            case 2:
                verFilmes(*filmes, *numFilmes);
                break;
            case 3:
                editarFilme(*filmes, *numFilmes);
                break;
            case 4:
                excluirFilme(filmes, numFilmes);
                break;
            case 5:
                buscarFilme(*filmes, *numFilmes);
                break;
            case 6:
                buscarUsuario(*usuarios, *numUsuarios);
                break;
            case 7:
                printf("Saindo do menu administrador...\n");
                break;
        }
    } while (opcao != 7);
}

void menuUsuario(Filme *filmes, int numFilmes) {
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
                verFilmes(filmes, numFilmes);
                break;
            case 2:
                comprarIngresso(filmes, numFilmes);
                break;
            case 3:
                buscarFilme(filmes, numFilmes);
                break;
            case 4:
                printf("Saindo...\n");
                break;
        }
    } while (opcao != 4);
}
