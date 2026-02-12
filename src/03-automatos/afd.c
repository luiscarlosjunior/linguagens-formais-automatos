/*
 * =============================================================================
 * Linguagens Formais e Autômatos
 * =============================================================================
 * Autômato Finito Determinístico (AFD)
 *
 * Descrição:
 *   Implementação de um AFD que reconhece cadeias binárias terminadas em "01".
 *
 * Definição formal do AFD:
 *   M = (Q, Σ, δ, q0, F)
 *   Q  = {q0, q1, q2}
 *   Σ  = {0, 1}
 *   q0 = estado inicial
 *   F  = {q2}
 *
 *   Tabela de transições δ:
 *     δ(q0, '0') = q1    δ(q0, '1') = q0
 *     δ(q1, '0') = q1    δ(q1, '1') = q2
 *     δ(q2, '0') = q1    δ(q2, '1') = q0
 *
 * Compilação:
 *   gcc -Wall -Wextra -std=c99 -o afd afd.c
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>

/* Número máximo de estados e símbolos do alfabeto */
#define MAX_ESTADOS  10
#define MAX_SIMBOLOS  5

/* Representação do AFD como estrutura */
typedef struct {
    int num_estados;                              /* |Q|: quantidade de estados */
    int num_simbolos;                             /* |Σ|: tamanho do alfabeto   */
    char alfabeto[MAX_SIMBOLOS];                  /* Σ: símbolos do alfabeto    */
    int transicao[MAX_ESTADOS][MAX_SIMBOLOS];     /* δ: tabela de transições    */
    int estado_inicial;                           /* q₀: estado inicial         */
    int estados_aceitacao[MAX_ESTADOS];           /* F: estados de aceitação    */
    int num_estados_aceitacao;                    /* |F|                        */
    const char *nomes_estados[MAX_ESTADOS];       /* Nomes legíveis dos estados */
} AFD;

/*
 * Retorna o índice do símbolo no alfabeto do AFD.
 * Retorna -1 se o símbolo não pertence ao alfabeto.
 */
static int indice_simbolo(const AFD *afd, char simbolo)
{
    for (int i = 0; i < afd->num_simbolos; i++) {
        if (afd->alfabeto[i] == simbolo)
            return i;
    }
    return -1;
}

/*
 * Verifica se um estado pertence ao conjunto de estados de aceitação F.
 */
static int eh_estado_aceitacao(const AFD *afd, int estado)
{
    for (int i = 0; i < afd->num_estados_aceitacao; i++) {
        if (afd->estados_aceitacao[i] == estado)
            return 1;
    }
    return 0;
}

/*
 * Simula o AFD sobre a palavra de entrada.
 *
 * Percorre cada símbolo da palavra, aplicando a função de transição δ,
 * e verifica se o estado final pertence a F.
 *
 * Retorna 1 se a palavra é aceita, 0 caso contrário.
 */
static int afd_aceita(AFD *afd, const char *palavra)
{
    int estado_atual = afd->estado_inicial;
    size_t tamanho = strlen(palavra);

    printf("  Entrada: \"%s\"\n", palavra);
    printf("  Rastreamento: %s", afd->nomes_estados[estado_atual]);

    for (size_t i = 0; i < tamanho; i++) {
        int idx = indice_simbolo(afd, palavra[i]);
        if (idx < 0) {
            printf("\n  ERRO: símbolo '%c' não pertence ao alfabeto!\n", palavra[i]);
            return 0;
        }

        int proximo_estado = afd->transicao[estado_atual][idx];
        printf(" --'%c'--> %s", palavra[i], afd->nomes_estados[proximo_estado]);
        estado_atual = proximo_estado;
    }

    int aceita = eh_estado_aceitacao(afd, estado_atual);
    printf("\n  Estado final: %s (%s)\n",
           afd->nomes_estados[estado_atual],
           aceita ? "ACEITAÇÃO" : "rejeição");

    return aceita;
}

/*
 * Imprime a tabela de transições do AFD de forma legível.
 */
static void imprimir_tabela_transicao(const AFD *afd)
{
    printf("  Tabela de Transições δ:\n");
    printf("  %-8s", "Estado");
    for (int j = 0; j < afd->num_simbolos; j++)
        printf("| %-8c", afd->alfabeto[j]);
    printf("\n  ");
    for (int j = 0; j <= afd->num_simbolos; j++)
        printf("---------");
    printf("\n");

    for (int i = 0; i < afd->num_estados; i++) {
        /* Marca estados de aceitação com '*' e estado inicial com '->' */
        char prefixo[4] = "  ";
        if (i == afd->estado_inicial)
            snprintf(prefixo, sizeof(prefixo), "->");
        if (eh_estado_aceitacao(afd, i))
            printf(" %s*%-6s", prefixo, afd->nomes_estados[i]);
        else
            printf(" %s %-6s", prefixo, afd->nomes_estados[i]);

        for (int j = 0; j < afd->num_simbolos; j++)
            printf("| %-8s", afd->nomes_estados[afd->transicao[i][j]]);
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    printf("==========================================================\n");
    printf(" Autômato Finito Determinístico (AFD)\n");
    printf(" Linguagem: cadeias binárias terminadas em \"01\"\n");
    printf("==========================================================\n\n");

    /* --- Construção do AFD --- */
    AFD afd;
    memset(&afd, 0, sizeof(AFD));

    /* Q = {q0, q1, q2} */
    afd.num_estados = 3;
    afd.nomes_estados[0] = "q0";
    afd.nomes_estados[1] = "q1";
    afd.nomes_estados[2] = "q2";

    /* Σ = {0, 1} */
    afd.num_simbolos = 2;
    afd.alfabeto[0] = '0';
    afd.alfabeto[1] = '1';

    /* Estado inicial: q0 */
    afd.estado_inicial = 0;

    /* F = {q2} */
    afd.num_estados_aceitacao = 1;
    afd.estados_aceitacao[0] = 2;

    /* Tabela de transições δ */
    /* δ(q0, '0') = q1,  δ(q0, '1') = q0 */
    afd.transicao[0][0] = 1;
    afd.transicao[0][1] = 0;

    /* δ(q1, '0') = q1,  δ(q1, '1') = q2 */
    afd.transicao[1][0] = 1;
    afd.transicao[1][1] = 2;

    /* δ(q2, '0') = q1,  δ(q2, '1') = q0 */
    afd.transicao[2][0] = 1;
    afd.transicao[2][1] = 0;

    /* Exibe a definição formal */
    printf("Definição formal:\n");
    printf("  Q  = {q0, q1, q2}\n");
    printf("  Σ  = {0, 1}\n");
    printf("  q₀ = q0\n");
    printf("  F  = {q2}\n\n");

    imprimir_tabela_transicao(&afd);

    /* --- Casos de teste --- */
    const char *casos_teste[] = {"101", "100", "0001", "11", ""};
    const int resultados_esperados[] = {1, 0, 1, 0, 0};
    int num_testes = 5;

    printf("----------------------------------------------------------\n");
    printf(" Testes de aceitação\n");
    printf("----------------------------------------------------------\n\n");

    int acertos = 0;
    for (int i = 0; i < num_testes; i++) {
        printf("Teste %d:\n", i + 1);
        int resultado = afd_aceita(&afd, casos_teste[i]);
        int correto = (resultado == resultados_esperados[i]);
        printf("  Resultado: %s | Esperado: %s | %s\n\n",
               resultado ? "ACEITA" : "REJEITA",
               resultados_esperados[i] ? "ACEITA" : "REJEITA",
               correto ? "✓ OK" : "✗ FALHA");
        if (correto)
            acertos++;
    }

    printf("==========================================================\n");
    printf(" Resumo: %d/%d testes corretos\n", acertos, num_testes);
    printf("==========================================================\n");

    return 0;
}
