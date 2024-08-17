#ifndef SISTEMA_H
#define SISTEMA_H

/**
 * @file sistema.h
 * @brief Declara as funções principais do sistema de cinema, incluindo os menus e a autenticação do administrador.
 *
 * Este arquivo de cabeçalho contém as declarações das funções principais que controlam o fluxo do sistema
 * de cinema, incluindo os menus de usuário e administrador, além da definição das credenciais do administrador.
 */

#include "usuario.h"
#include "filme.h"

#define ADMIN_LOGIN "admin@gmail.com" /**< Email de login predefinido para o administrador. */
#define ADMIN_SENHA "1234"            /**< Senha predefinida para o administrador. */

/**
 * @brief Exibe o menu principal do sistema de cinema.
 *
 * Esta função apresenta o menu principal do sistema, onde os usuários podem escolher entre
 * cadastrar, fazer login ou sair do sistema.
 *
 * @param usuarios Ponteiro para o array de usuários cadastrados.
 * @param numUsuarios Ponteiro para o número total de usuários cadastrados.
 * @param filmes Ponteiro para o array de filmes no catálogo.
 * @param numFilmes Ponteiro para o número total de filmes no catálogo.
 */
void menuPrincipal(Usuario **usuarios, int *numUsuarios, Filme **filmes, int *numFilmes);

/**
 * @brief Exibe o menu de administração para o administrador do sistema.
 *
 * Esta função apresenta o menu de administração, onde o administrador pode realizar operações como
 * adicionar, editar, excluir filmes, e visualizar filmes em promoção.
 *
 * @param filmes Ponteiro para o array de filmes no catálogo.
 * @param numFilmes Ponteiro para o número total de filmes no catálogo.
 */
void menuAdministrador(Filme **filmes, int *numFilmes);

/**
 * @brief Exibe o menu de usuário para usuários comuns do sistema.
 *
 * Esta função apresenta o menu de usuário, onde os usuários podem visualizar filmes disponíveis
 * e comprar ingressos.
 *
 * @param filmes Array de filmes no catálogo.
 * @param numFilmes Número total de filmes no catálogo.
 */
void menuUsuario(Filme *filmes, int numFilmes);

/**
 * @brief Mostra uma mensagem de boas-vindas ao usuário após o login.
 *
 * Esta função exibe uma mensagem de boas-vindas personalizada após o usuário fazer login com sucesso.
 */
void mostrarBoasVindas();

#endif // SISTEMA_H
