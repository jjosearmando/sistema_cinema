#ifndef USUARIO_H
#define USUARIO_H

/**
 * @file usuario.h
 * @brief Define a estrutura de dados e as funções relacionadas aos usuários no sistema de cinema.
 *
 * Este arquivo de cabeçalho contém a definição da estrutura `Usuario`, que representa um usuário no sistema,
 * bem como as declarações de funções para manipular usuários, como cadastrar, fazer login, salvar e carregar usuários.
 */

#define MAX_NOME 100  /**< Tamanho máximo para o nome do usuário. */
#define MAX_EMAIL 80  /**< Tamanho máximo para o email do usuário. */
#define MAX_SENHA 20  /**< Tamanho máximo para a senha do usuário. */

/**
 * @struct Usuario
 * @brief Estrutura que representa um usuário no sistema de cinema.
 *
 * A estrutura `Usuario` contém informações básicas sobre um usuário, incluindo seu nome,
 * email e senha.
 */
typedef struct {
    char nome[MAX_NOME];   /**< Nome do usuário. */
    char email[MAX_EMAIL]; /**< Email do usuário. */
    char senha[MAX_SENHA]; /**< Senha do usuário. */
} Usuario;

/**
 * @brief Cadastra um novo usuário no sistema.
 *
 * Esta função aloca memória para um novo usuário, preenche seus dados e o adiciona à lista de usuários cadastrados.
 *
 * @param usuarios Ponteiro para o array de usuários.
 * @param numUsuarios Ponteiro para o número total de usuários cadastrados.
 */
void cadastrarUsuario(Usuario **usuarios, int *numUsuarios);

/**
 * @brief Realiza o login de um usuário no sistema.
 *
 * Esta função verifica se as credenciais fornecidas correspondem a um usuário cadastrado e,
 * em caso de sucesso, autentica o usuário no sistema.
 *
 * @param usuarios Array de usuários cadastrados.
 * @param numUsuarios Número total de usuários cadastrados.
 * @return int Retorna 1 se o login for bem-sucedido, 0 caso contrário.
 */
int login(Usuario *usuarios, int numUsuarios);

/**
 * @brief Salva os dados dos usuários em um arquivo binário.
 *
 * Esta função salva as informações de todos os usuários cadastrados em um arquivo binário
 * para que possam ser recuperadas em execuções futuras do programa.
 *
 * @param usuarios Array de usuários cadastrados.
 * @param numUsuarios Número total de usuários cadastrados.
 */
void salvarUsuarios(Usuario *usuarios, int numUsuarios);

/**
 * @brief Carrega os dados dos usuários de um arquivo binário.
 *
 * Esta função carrega as informações de usuários de um arquivo binário e preenche a lista de usuários cadastrados.
 *
 * @param usuarios Ponteiro para o array de usuários.
 * @param numUsuarios Ponteiro para o número total de usuários cadastrados.
 */
void carregarUsuarios(Usuario **usuarios, int *numUsuarios);

#endif // USUARIO_H
