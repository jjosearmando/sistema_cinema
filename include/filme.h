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
#define MAX_HORARIOS 10  /**< Define o número máximo de horários por dia para exibição de filmes. */

/**
 * @brief Estrutura que representa um filme no sistema.
 *
 * A estrutura contém informações sobre o filme, como nome, duração, avaliação, preço do ingresso,
 * a quantidade de ingressos disponíveis por dia da semana, os horários de exibição, e um ponteiro para o próximo filme,
 * formando uma lista encadeada.
 */
typedef struct Filme {
    char nome[MAX_NOME];  /**< Nome do filme. */
    int duracao;          /**< Duração do filme em minutos. */
    float avaliacao;      /**< Avaliação do filme (0.0 a 10.0). */
    float precoIngresso;  /**< Preço do ingresso para o filme. */
    int quantidadeIngressosDisponiveis[7];  /**< Quantidade de ingressos disponíveis por dia da semana. */
    int diasSemana[7][MAX_HORARIOS];  /**< Horários de exibição por dia da semana. */
    struct Filme *prox;   /**< Ponteiro para o próximo filme na lista encadeada. */
} Filme;

/**
 * @brief Adiciona um novo filme ao catálogo.
 *
 * Esta função aloca memória para um novo filme, preenche seus dados e o adiciona à lista encadeada de filmes.
 *
 * @param filmes Ponteiro para o ponteiro da lista encadeada de filmes.
 */
void adicionarFilme(Filme **filmes);

/**
 * @brief Exibe a lista de filmes disponíveis no catálogo.
 *
 * Esta função lista todos os filmes atualmente disponíveis no catálogo percorrendo a lista encadeada.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void verFilmes(Filme *filmes);

/**
 * @brief Edita as informações de um filme no catálogo.
 *
 * Esta função permite que o usuário edite os detalhes de um filme existente no catálogo.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void editarFilme(Filme *filmes);

/**
 * @brief Exclui um filme do catálogo.
 *
 * Esta função remove um filme do catálogo e libera a memória associada a ele.
 *
 * @param filmes Ponteiro para o ponteiro da lista encadeada de filmes.
 */
void excluirFilme(Filme **filmes);

/**
 * @brief Salva os filmes em um arquivo binário.
 *
 * Esta função salva os dados de todos os filmes presentes na lista encadeada em um arquivo binário.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void salvarFilmes(Filme *filmes);

/**
 * @brief Carrega os filmes de um arquivo binário.
 *
 * Esta função carrega os dados de filmes de um arquivo binário e os adiciona à lista encadeada de filmes.
 *
 * @param filmes Ponteiro para o ponteiro da lista encadeada de filmes.
 */
void carregarFilmes(Filme **filmes);

/**
 * @brief Realiza a compra de ingressos para um filme.
 *
 * Esta função permite que o usuário compre ingressos para um filme em um dia e horário específicos.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void comprarIngresso(Filme *filmes);

/**
 * @brief Carrega os dados dos filmes a partir de um arquivo de texto.
 *
 * Esta função carrega os dados de filmes de um arquivo de texto e os adiciona à lista encadeada de filmes.
 *
 * @param filmes Ponteiro para o ponteiro da lista encadeada de filmes.
 */
void carregarFilmesTxt(Filme **filmes);

/**
 * @brief Salva os dados dos filmes em um arquivo de texto em ordem alfabética.
 *
 * Esta função salva os dados de todos os filmes presentes na lista encadeada em um arquivo de texto em ordem alfabética.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void salvarFilmesTxt(Filme *filmes);

/**
 * @brief Função de comparação para ordenação de filmes por nome.
 *
 * Esta função é utilizada para comparar dois filmes pelo nome durante o processo de ordenação.
 *
 * @param a Ponteiro para o primeiro filme.
 * @param b Ponteiro para o segundo filme.
 * 
 * @return Retorna um valor negativo se o nome do primeiro filme for menor, 
 *         zero se forem iguais, ou um valor positivo se o nome do segundo filme for menor.
 */
int compararFilmes(const void *a, const void *b);

/**
 * @brief Ordena a lista encadeada de filmes em ordem alfabética pelo nome.
 *
 * Esta função ordena a lista encadeada de filmes em ordem alfabética pelo nome dos filmes.
 *
 * @param filmes Ponteiro para o ponteiro da lista encadeada de filmes.
 */
void ordenarFilmes(Filme **filmes);

/**
 * @brief Busca um filme pelo nome na lista encadeada de filmes.
 *
 * Esta função busca um filme pelo nome na lista encadeada de filmes.
 *
 * @param filmes Ponteiro para a lista encadeada de filmes.
 */
void buscarFilme(Filme *filmes);

#endif // FILME_H