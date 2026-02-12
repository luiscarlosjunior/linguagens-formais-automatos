/*
 * =============================================================================
 * Linguagens Formais e Autômatos
 * =============================================================================
 * Autômato Finito Não-Determinístico (AFND)
 *
 * Descrição:
 *   Implementação de um AFND que reconhece cadeias sobre {a, b} que contêm
 *   "ab" como subcadeia.
 *
 * Definição formal do AFND:
 *   M = (Q, Σ, δ, q0, F)
 *   Q  = {q0, q1, q2}
 *   Σ  = {a, b}
 *   q0 = estado inicial
 *   F  = {q2}
 *
 *   Tabela de transições δ (retorna conjuntos de estados):
 *     δ(q0, 'a') = {q0, q1}    δ(q0, 'b') = {q0}
 *     δ(q1, 'a') = ∅           δ(q1, 'b') = {q2}
 *     δ(q2, 'a') = {q2}        δ(q2, 'b') = {q2}
 *
 * Representação de conjuntos:
 *   Utilizamos bitmask (máscara de bits) para representar conjuntos de estados.
 *   Bit i ligado significa que o estado qi pertence ao conjunto.
 *     Ex.: 0b101 = {q0, q2},  0b010 = {q1}
 *
 * Compilação:
 *   gcc -Wall -Wextra -std=c99 -o afnd afnd.c
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>

/* Número máximo de estados e símbolos do alfabeto */
#define MAX_ESTADOS  10
#define MAX_SIMBOLOS  5

/*
 * Cada posição da tabela de transição armazena uma bitmask representando
 * o conjunto de estados destino.
 */
typedef unsigned int ConjuntoEstados;

/* Representação do AFND como estrutura */
typedef struct {
    int num_estados;                              /* |Q|: quantidade de estados  */
    int num_simbolos;                             /* |Σ|: tamanho do alfabeto    */
    char alfabeto[MAX_SIMBOLOS];                  /* Σ: símbolos do alfabeto     */
    ConjuntoEstados transicao[MAX_ESTADOS][MAX_SIMBOLOS]; /* δ: transições      */
    int estado_inicial;                           /* q₀: estado inicial          */
    ConjuntoEstados estados_aceitacao;            /* F: bitmask de aceitação     */
    const char *nomes_estados[MAX_ESTADOS];       /* Nomes legíveis dos estados  */
} AFND;

/*
 * Retorna o índice do símbolo no alfabeto do AFND.
 * Retorna -1 se o símbolo não pertence ao alfabeto.
 */
static int indice_simbolo(const AFND *afnd, char simbolo)
{
    for (int i = 0; i < afnd->num_simbolos; i++) {
        if (afnd->alfabeto[i] == simbolo)
            return i;
    }
    return -1;
}

/*
 * Imprime um conjunto de estados representado como bitmask.
 * Formato: {q0, q2} ou ∅ para conjunto vazio.
 */
static void imprimir_conjunto(const AFND *afnd, ConjuntoEstados conjunto)
{
    if (conjunto == 0) {
        printf("∅");
        return;
    }

    printf("{");
    int primeiro = 1;
    for (int i = 0; i < afnd->num_estados; i++) {
        if (conjunto & (1u << i)) {
            if (!primeiro)
                printf(", ");
            printf("%s", afnd->nomes_estados[i]);
            primeiro = 0;
        }
    }
    printf("}");
}

/*
 * Verifica se um conjunto de estados contém algum estado de aceitação.
 * Retorna 1 se a interseção entre o conjunto e F é não-vazia.
 */
static int contem_estado_aceitacao(const AFND *afnd, ConjuntoEstados conjunto)
{
    return (conjunto & afnd->estados_aceitacao) != 0;
}

/*
 * Simula o AFND sobre a palavra de entrada.
 *
 * Em cada passo, para cada estado no conjunto atual e o símbolo lido,
 * calcula a união dos conjuntos de estados destino (δ estendida).
 *
 * Retorna 1 se a palavra é aceita, 0 caso contrário.
 */
static int afnd_aceita(AFND *afnd, const char *palavra)
{
    /* Conjunto inicial contém apenas o estado inicial */
    ConjuntoEstados estados_atuais = (1u << afnd->estado_inicial);
    size_t tamanho = strlen(palavra);

    printf("  Entrada: \"%s\"\n", palavra);
    printf("  Rastreamento:\n");
    printf("    Estados atuais: ");
    imprimir_conjunto(afnd, estados_atuais);
    printf("\n");

    for (size_t i = 0; i < tamanho; i++) {
        int idx = indice_simbolo(afnd, palavra[i]);
        if (idx < 0) {
            printf("    ERRO: símbolo '%c' não pertence ao alfabeto!\n", palavra[i]);
            return 0;
        }

        /* Calcula a união de δ(q, símbolo) para todo q no conjunto atual */
        ConjuntoEstados proximos_estados = 0;
        for (int q = 0; q < afnd->num_estados; q++) {
            if (estados_atuais & (1u << q))
                proximos_estados |= afnd->transicao[q][idx];
        }

        printf("    --'%c'--> ", palavra[i]);
        imprimir_conjunto(afnd, proximos_estados);
        printf("\n");

        estados_atuais = proximos_estados;

        /* Se o conjunto ficou vazio, não há caminho possível */
        if (estados_atuais == 0) {
            printf("    Conjunto vazio — nenhum caminho possível.\n");
            break;
        }
    }

    int aceita = contem_estado_aceitacao(afnd, estados_atuais);
    printf("  Estados finais: ");
    imprimir_conjunto(afnd, estados_atuais);
    printf(" ∩ F = ");
    imprimir_conjunto(afnd, estados_atuais & afnd->estados_aceitacao);
    printf(" → %s\n", aceita ? "ACEITA" : "REJEITA");

    return aceita;
}

/*
 * Imprime a tabela de transições do AFND.
 */
static void imprimir_tabela_transicao(const AFND *afnd)
{
    printf("  Tabela de Transições δ:\n");
    printf("  %-8s", "Estado");
    for (int j = 0; j < afnd->num_simbolos; j++)
        printf("| %-14c", afnd->alfabeto[j]);
    printf("\n  ");
    for (int j = 0; j <= afnd->num_simbolos; j++)
        printf("---------------");
    printf("\n");

    for (int i = 0; i < afnd->num_estados; i++) {
        /* Marca estado inicial com '->' e estados de aceitação com '*' */
        const char *seta = (i == afnd->estado_inicial) ? "->" : "  ";
        const char *estrela = (afnd->estados_aceitacao & (1u << i)) ? "*" : " ";
        printf(" %s%s%-6s", seta, estrela, afnd->nomes_estados[i]);

        for (int j = 0; j < afnd->num_simbolos; j++) {
            printf("| ");
            /* Imprime o conjunto de estados destino dentro da célula */
            ConjuntoEstados dest = afnd->transicao[i][j];
            if (dest == 0) {
                printf("%-13s", "∅");
            } else {
                /* Monta a string do conjunto */
                char buf[64];
                int pos = 0;
                buf[pos++] = '{';
                int primeiro = 1;
                for (int k = 0; k < afnd->num_estados; k++) {
                    if (dest & (1u << k)) {
                        if (!primeiro) {
                            buf[pos++] = ',';
                            buf[pos++] = ' ';
                        }
                        const char *nome = afnd->nomes_estados[k];
                        size_t len = strlen(nome);
                        memcpy(buf + pos, nome, len);
                        pos += (int)len;
                        primeiro = 0;
                    }
                }
                buf[pos++] = '}';
                buf[pos] = '\0';
                printf("%-13s", buf);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    printf("==========================================================\n");
    printf(" Autômato Finito Não-Determinístico (AFND)\n");
    printf(" Linguagem: cadeias sobre {a,b} contendo \"ab\"\n");
    printf("==========================================================\n\n");

    /* --- Construção do AFND --- */
    AFND afnd;
    memset(&afnd, 0, sizeof(AFND));

    /* Q = {q0, q1, q2} */
    afnd.num_estados = 3;
    afnd.nomes_estados[0] = "q0";
    afnd.nomes_estados[1] = "q1";
    afnd.nomes_estados[2] = "q2";

    /* Σ = {a, b} */
    afnd.num_simbolos = 2;
    afnd.alfabeto[0] = 'a';
    afnd.alfabeto[1] = 'b';

    /* Estado inicial: q0 */
    afnd.estado_inicial = 0;

    /* F = {q2} — bitmask: bit 2 ligado = 0b100 = 4 */
    afnd.estados_aceitacao = (1u << 2);

    /*
     * Tabela de transições δ (valores são bitmasks de conjuntos de estados)
     * Bit 0 = q0, Bit 1 = q1, Bit 2 = q2
     */

    /* δ(q0, 'a') = {q0, q1} = 0b011 = 3 */
    afnd.transicao[0][0] = (1u << 0) | (1u << 1);
    /* δ(q0, 'b') = {q0}     = 0b001 = 1 */
    afnd.transicao[0][1] = (1u << 0);

    /* δ(q1, 'a') = ∅         = 0b000 = 0 */
    afnd.transicao[1][0] = 0;
    /* δ(q1, 'b') = {q2}     = 0b100 = 4 */
    afnd.transicao[1][1] = (1u << 2);

    /* δ(q2, 'a') = {q2}     = 0b100 = 4 */
    afnd.transicao[2][0] = (1u << 2);
    /* δ(q2, 'b') = {q2}     = 0b100 = 4 */
    afnd.transicao[2][1] = (1u << 2);

    /* Exibe a definição formal */
    printf("Definição formal:\n");
    printf("  Q  = {q0, q1, q2}\n");
    printf("  Σ  = {a, b}\n");
    printf("  q₀ = q0\n");
    printf("  F  = {q2}\n\n");

    imprimir_tabela_transicao(&afnd);

    /* --- Casos de teste --- */
    const char *casos_teste[]        = {"ab", "aab", "ba", "bab", "bbb"};
    const int   resultados_esperados[] = {1,    1,     0,    1,     0};
    int num_testes = 5;

    printf("----------------------------------------------------------\n");
    printf(" Testes de aceitação\n");
    printf("----------------------------------------------------------\n\n");

    int acertos = 0;
    for (int i = 0; i < num_testes; i++) {
        printf("Teste %d:\n", i + 1);
        int resultado = afnd_aceita(&afnd, casos_teste[i]);
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
