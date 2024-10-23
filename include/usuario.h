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
 * @brief Estrutura que representa um usuário no sistema.
 *
 * A estrutura contém informações sobre o nome, email e senha do usuário, além de um ponteiro para o próximo usuário,
 * formando uma lista encadeada.
 */
typedef struct Usuario {
    char nome[MAX_NOME];    /**< Nome do usuário. */
    char email[MAX_EMAIL];  /**< Email do usuário. */
    char senha[MAX_SENHA];  /**< Senha do usuário. */
    struct Usuario *prox;   /**< Ponteiro para o próximo usuário na lista encadeada. */
} Usuario;

/**
 * @brief Cadastra um novo usuário no sistema.
 *
 * Esta função aloca memória para um novo usuário, preenche seus dados e o adiciona à lista encadeada de usuários cadastrados.
 *
 * @param usuarios Ponteiro para o ponteiro da lista encadeada de usuários.
 */
void cadastrarUsuario(Usuario **usuarios);

/**
 * @brief Realiza o login de um usuário no sistema.
 *
 * Esta função verifica se as credenciais fornecidas correspondem a um usuário cadastrado e,
 * em caso de sucesso, autentica o usuário no sistema.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários cadastrados.
 * @return int Retorna 1 se o login for bem-sucedido, 0 caso contrário.
 */
int login(Usuario *usuarios);

/**
 * @brief Salva os dados dos usuários em um arquivo binário.
 *
 * Esta função salva as informações de todos os usuários cadastrados na lista encadeada em um arquivo binário
 * para que possam ser recuperadas em execuções futuras do programa.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários cadastrados.
 */
void salvarUsuarios(Usuario *usuarios);

/**
 * @brief Carrega os dados dos usuários de um arquivo binário.
 *
 * Esta função carrega as informações de usuários de um arquivo binário e preenche a lista encadeada de usuários cadastrados.
 *
 * @param usuarios Ponteiro para o ponteiro da lista encadeada de usuários.
 */
void carregarUsuarios(Usuario **usuarios);

/**
 * @brief Carrega os dados dos usuários a partir de um arquivo de texto.
 *
 * Esta função carrega as informações de usuários de um arquivo de texto e preenche a lista encadeada de usuários cadastrados.
 *
 * @param usuarios Ponteiro para o ponteiro da lista encadeada de usuários.
 */
void carregarUsuariosTxt(Usuario **usuarios);

/**
 * @brief Salva os dados dos usuários no arquivo de texto em ordem alfabética.
 *
 * Esta função salva as informações de todos os usuários cadastrados na lista encadeada em um arquivo de texto em ordem alfabética.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários cadastrados.
 */
void salvarUsuariosTxt(Usuario *usuarios);

/**
 * @brief Função de comparação para ordenação de usuários por nome.
 *
 * Esta função é utilizada para comparar dois usuários pelo nome durante o processo de ordenação.
 *
 * @param a Ponteiro para o primeiro usuário.
 * @param b Ponteiro para o segundo usuário.
 * 
 * @return Retorna um valor negativo se o nome do primeiro usuário for menor, 
 *         zero se forem iguais, ou um valor positivo se o nome do segundo usuário for menor.
 */
int compararUsuarios(const void *a, const void *b);

/**
 * @brief Ordena a lista encadeada de usuários em ordem alfabética pelo nome.
 *
 * Esta função ordena a lista encadeada de usuários em ordem alfabética pelo nome dos usuários.
 *
 * @param usuarios Ponteiro para o ponteiro da lista encadeada de usuários.
 */
void ordenarUsuarios(Usuario **usuarios);

/**
 * @brief Busca um usuário pelo nome na lista encadeada de usuários.
 *
 * Esta função busca um usuário pelo nome na lista encadeada de usuários cadastrados.
 *
 * @param usuarios Ponteiro para a lista encadeada de usuários.
 */
void buscarUsuario(Usuario *usuarios);

#endif // USUARIO_H