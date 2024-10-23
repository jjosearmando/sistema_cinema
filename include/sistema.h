#ifndef SISTEMA_H
#define SISTEMA_H

/**
 * @file sistema.h
 * @brief Declara as funções principais do sistema de cinema, incluindo os menus e a autenticação do administrador.
 *
 * Este arquivo de cabeçalho contém as declarações das funções principais que controlam o fluxo do sistema
 * de cinema, incluindo os menus de usuário e administrador, além da definição das credenciais do administrador.
 */


#define ADMIN_LOGIN "admin@gmail.com" /**< Email de login predefinido para o administrador. */
#define ADMIN_SENHA "1234"            /**< Senha predefinida para o administrador. */

#include "../include/filme.h"
#include "../include/usuario.h"

/**
 * @brief Exibe o menu principal do sistema de cinema.
 *
 * Esta função apresenta o menu principal do sistema, onde os usuários podem escolher entre
 * cadastrar, fazer login ou sair do sistema. As listas encadeadas de usuários e filmes são passadas
 * como ponteiros duplos para que possam ser modificadas durante a execução do programa.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários cadastrados.
 * @param filmes Ponteiro para a lista encadeada de filmes no catálogo.
 */
void menuPrincipal(Usuario **usuarios, Filme **filmes);

/**
 * @brief Exibe o menu de administração para o administrador do sistema.
 *
 * Esta função apresenta o menu de administração, onde o administrador pode realizar operações como
 * adicionar, editar, excluir filmes, buscar usuários e filmes. A função também permite gerenciar o catálogo de filmes.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários cadastrados.
 * @param filmes Ponteiro para a lista encadeada de filmes no catálogo.
 */
void menuAdministrador(Usuario **usuarios, Filme **filmes);

/**
 * @brief Exibe o menu de usuário para usuários comuns do sistema.
 *
 * Esta função apresenta o menu de usuário, onde os usuários podem visualizar os filmes disponíveis
 * no catálogo e comprar ingressos para sessões de filmes. Apenas a lista de filmes é manipulada
 * pelos usuários comuns.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes no catálogo.
 */
void menuUsuario(Filme *filmes);

/**
 * @brief Mostra uma mensagem de boas-vindas ao usuário após o login.
 *
 * Esta função exibe uma mensagem de boas-vindas ao usuário que faz login com sucesso.
 */
void mostrarBoasVindas();

#endif // SISTEMA_H