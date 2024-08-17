#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Declara funções utilitárias e variáveis globais para o sistema de cinema.
 *
 * Este arquivo de cabeçalho contém declarações de funções auxiliares e variáveis globais
 * que são usadas em várias partes do sistema de cinema, como validação de email e opções de menu.
 */

/**
 * @brief Array de strings que representa os dias da semana.
 *
 * O array `diasDaSemana` é utilizado para converter índices de dias da semana em
 * nomes legíveis, como "Domingo", "Segunda-feira", etc.
 */
extern const char *diasDaSemana[];

/**
 * @brief Valida o formato de um email.
 *
 * Esta função verifica se o email fornecido está no formato correto, contendo um caractere '@'
 * e se tem menos de 80 caracteres. A função também pode ser expandida para verificar domínios específicos.
 *
 * @param email O email a ser validado.
 * @return int Retorna 1 se o email for válido, 0 caso contrário.
 */
int validarEmail(const char *email);

/**
 * @brief Verifica se uma opção está dentro de um intervalo válido.
 *
 * Esta função verifica se a opção fornecida está dentro dos limites mínimos e máximos especificados.
 *
 * @param opcao A opção escolhida pelo usuário.
 * @param min O valor mínimo permitido para a opção.
 * @param max O valor máximo permitido para a opção.
 * @return int Retorna 1 se a opção estiver dentro do intervalo, 0 caso contrário.
 */
int validarEntrada(int opcao, int min, int max);

/**
 * @brief Lê e valida uma opção numérica do usuário.
 *
 * Esta função solicita ao usuário que insira uma opção numérica dentro de um intervalo específico.
 * Ela garante que a entrada seja válida e repete a solicitação até que uma entrada válida seja recebida.
 *
 * @param min Valor mínimo aceitável.
 * @param max Valor máximo aceitável.
 * @return int A opção numérica validada escolhida pelo usuário.
 */
int lerOpcao(int min, int max);

#endif // UTILS_H
