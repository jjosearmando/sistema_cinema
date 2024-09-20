#ifndef FILME_H
#define FILME_H

/**
 * @file filme.h
 * @brief Define a estrutura de dados e as funções relacionadas a filmes no sistema de cinema.
 *
 * Este arquivo de cabeçalho contém a definição da estrutura `Filme`, que representa um filme no sistema,
 * bem como as declarações de funções para manipular filmes, como adicionar, editar, excluir e salvar filmes.
 */

#define MAX_NOME 100 /**< Define o tamanho máximo para o nome do filme. */

#define MAX_HORARIOS 10  // Define um número máximo de horários por dia

typedef struct {
    char nome[MAX_NOME];
    int duracao;
    float avaliacao;
    float precoIngresso;
    int diasSemana[7][MAX_HORARIOS]; // Matriz para armazenar horários por dia da semana
    int quantidadeIngressosDisponiveis[7]; // Array para ingressos disponíveis por dia da semana
} Filme;


/**
 * @brief Adiciona um novo filme ao catálogo.
 *
 * Esta função aloca memória para um novo filme, preenche seus dados e o adiciona ao catálogo.
 *
 * @param filmes Ponteiro para o array de filmes.
 * @param numFilmes Ponteiro para o número total de filmes no catálogo.
 */
void adicionarFilme(Filme **filmes, int *numFilmes);

/**
 * @brief Exibe a lista de filmes disponíveis no catálogo.
 *
 * Esta função lista todos os filmes atualmente disponíveis no catálogo.
 *
 * @param filmes Array de filmes.
 * @param numFilmes Número total de filmes no catálogo.
 */
void verFilmes(Filme *filmes, int numFilmes);

/**
 * @brief Edita as informações de um filme no catálogo.
 *
 * Esta função permite que o usuário edite os detalhes de um filme existente no catálogo.
 *
 * @param filmes Array de filmes.
 * @param numFilmes Número total de filmes no catálogo.
 */
void editarFilme(Filme *filmes, int numFilmes);

/**
 * @brief Exclui um filme do catálogo.
 *
 * Esta função remove um filme do catálogo e libera a memória associada a ele.
 *
 * @param filmes Ponteiro para o array de filmes.
 * @param numFilmes Ponteiro para o número total de filmes no catálogo.
 */
void excluirFilme(Filme **filmes, int *numFilmes);

/**
 * @brief Salva os filmes em um arquivo binário.
 *
 * Esta função salva os dados de todos os filmes em um arquivo binário para persistência.
 *
 * @param filmes Array de filmes.
 * @param numFilmes Número total de filmes no catálogo.
 */
void salvarFilmes(Filme *filmes, int numFilmes);

/**
 * @brief Carrega os filmes de um arquivo binário.
 *
 * Esta função carrega os dados de filmes de um arquivo binário e preenche o catálogo.
 *
 * @param filmes Ponteiro para o array de filmes.
 * @param numFilmes Ponteiro para o número total de filmes no catálogo.
 */
void carregarFilmes(Filme **filmes, int *numFilmes);

/**
 * @brief Realiza a compra de ingressos para um filme.
 *
 * Esta função permite que o usuário compre ingressos para um filme em um dia e horário específicos.
 *
 * @param filmes Array de filmes.
 * @param numFilmes Número total de filmes no catálogo.
 */
void comprarIngresso(Filme *filmes, int numFilmes);

/**
 * Carrega os dados dos filmes a partir de um arquivo de texto.
 *
 * @param filmes Ponteiro para o array dinâmico de filmes. Após a execução, o array conterá os filmes lidos do arquivo.
 * @param numFilmes Ponteiro para a variável que armazenará a quantidade de filmes carregados.
 */
void carregarFilmesTxt(Filme **filmes, int *numFilmes);

/**
 * Salva os dados dos filmes no arquivo de texto em ordem alfabética.
 *
 * @param filmes Ponteiro para o array de filmes a serem salvos.
 * @param numFilmes Número de filmes no array.
 */
void salvarFilmesTxt(Filme *filmes, int numFilmes);

/**
 * Função de comparação para ordenação de filmes por nome.
 *
 * @param a Ponteiro para o primeiro filme.
 * @param b Ponteiro para o segundo filme.
 * 
 * @return Retorna um valor negativo se o nome do primeiro filme for menor, 
 *         zero se forem iguais, ou um valor positivo se o nome do segundo filme for menor.
 */
int compararFilmes(const void *a, const void *b);

/**
 * Ordena o array de filmes em ordem alfabética pelo nome.
 *
 * @param filmes Ponteiro para o array de filmes a serem ordenados.
 * @param numFilmes Número de filmes no array.
 */
void ordenarFilmes(Filme *filmes, int numFilmes);

/**
 * Busca um filme pelo nome no array de filmes.
 *
 * @param filmes Ponteiro para o array de filmes.
 * @param numFilmes Número de filmes no array.
 */
void buscarFilme(Filme *filmes, int numFilmes);

#endif // FILME_H
