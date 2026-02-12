/*
 * =============================================================================
 * Linguagens Formais e Autômatos
 * =============================================================================
 * Conversão AFND → AFD  (Construção de Subconjuntos)
 *
 * Descrição:
 *   Implementação do algoritmo de construção de subconjuntos (subset
 *   construction) para converter um Autômato Finito Não-Determinístico
 *   (AFND) em um Autômato Finito Determinístico (AFD) equivalente.
 *
 *   O algoritmo parte do princípio de que cada "estado" do AFD resultante
 *   corresponde a um subconjunto de estados do AFND original.
 *
 *   Passos do algoritmo:
 *     1. O estado inicial do AFD é o conjunto {q₀} (estado inicial do AFND).
 *     2. Para cada conjunto de estados S e cada símbolo a do alfabeto,
 *        calcula-se  δ_AFD(S, a) = ⋃_{q ∈ S} δ_AFND(q, a).
 *     3. Se o conjunto resultante é novo, adiciona-se à fila de exploração.
 *     4. Um estado do AFD é de aceitação se o subconjunto correspondente
 *        contém pelo menos um estado de aceitação do AFND.
 *
 *   Exemplo utilizado:
 *     AFND que reconhece cadeias sobre {a, b} contendo "ab" como subcadeia
 *     (o mesmo AFND do capítulo 03).
 *
 * Compilação:
 *   gcc -Wall -Wextra -std=c99 -o conversao_afnd_afd conversao_afnd_afd.c
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>

/* Limites do autômato */
#define MAX_ESTADOS_AFND  10
#define MAX_SIMBOLOS       5

/*
 * Como um AFD resultante da construção de subconjuntos pode ter até
 * 2^n estados (onde n = número de estados do AFND), limitamos a um
 * valor prático.
 */
#define MAX_ESTADOS_AFD   32

/* Tipo bitmask para representar conjuntos de estados do AFND */
typedef unsigned int ConjuntoEstados;

/* ========================== Estrutura do AFND ========================== */
typedef struct {
    int num_estados;
    int num_simbolos;
    char alfabeto[MAX_SIMBOLOS];
    ConjuntoEstados transicao[MAX_ESTADOS_AFND][MAX_SIMBOLOS];
    int estado_inicial;
    ConjuntoEstados estados_aceitacao;   /* bitmask */
    const char *nomes_estados[MAX_ESTADOS_AFND];
} AFND;

/* ========================== Estrutura do AFD =========================== */
typedef struct {
    int num_estados;
    int num_simbolos;
    char alfabeto[MAX_SIMBOLOS];
    int transicao[MAX_ESTADOS_AFD][MAX_SIMBOLOS];
    int estado_inicial;
    int eh_aceitacao[MAX_ESTADOS_AFD];

    /*
     * Cada estado do AFD corresponde a um subconjunto de estados do AFND.
     * Armazenamos essa correspondência para impressão e verificação.
     */
    ConjuntoEstados subconjunto[MAX_ESTADOS_AFD];
} AFD;

/* ===================== Funções auxiliares de impressão ================== */

/* Imprime um conjunto de estados (bitmask) usando nomes do AFND */
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
            if (!primeiro) printf(", ");
            printf("%s", afnd->nomes_estados[i]);
            primeiro = 0;
        }
    }
    printf("}");
}

/* ==================== Construção de Subconjuntos ======================= */

/*
 * Dado um conjunto de estados do AFND e um índice de símbolo,
 * calcula a união dos conjuntos de estados destino:
 *   mover(S, a) = ⋃_{q ∈ S} δ(q, a)
 */
static ConjuntoEstados mover(const AFND *afnd, ConjuntoEstados conjunto,
                             int idx_simbolo)
{
    ConjuntoEstados resultado = 0;
    for (int q = 0; q < afnd->num_estados; q++) {
        if (conjunto & (1u << q))
            resultado |= afnd->transicao[q][idx_simbolo];
    }
    return resultado;
}

/*
 * Procura se um subconjunto já foi registrado como estado do AFD.
 * Retorna o índice no AFD ou -1 se não encontrado.
 */
static int buscar_subconjunto(const AFD *afd, ConjuntoEstados conjunto)
{
    for (int i = 0; i < afd->num_estados; i++) {
        if (afd->subconjunto[i] == conjunto)
            return i;
    }
    return -1;
}

/*
 * Executa a construção de subconjuntos.
 *
 * Utiliza uma fila (BFS) para explorar todos os subconjuntos acessíveis
 * a partir do estado inicial {q₀}.
 */
static void construir_afd(const AFND *afnd, AFD *afd)
{
    memset(afd, 0, sizeof(AFD));

    /* O AFD herda o alfabeto do AFND */
    afd->num_simbolos = afnd->num_simbolos;
    memcpy(afd->alfabeto, afnd->alfabeto, sizeof(afnd->alfabeto));

    /* Fila para BFS dos subconjuntos */
    int fila[MAX_ESTADOS_AFD];
    int inicio_fila = 0;
    int fim_fila    = 0;

    /*
     * Passo 1: estado inicial do AFD = {q₀}
     * Corresponde ao conjunto contendo apenas o estado inicial do AFND.
     */
    ConjuntoEstados conj_inicial = (1u << afnd->estado_inicial);
    afd->subconjunto[0] = conj_inicial;
    afd->eh_aceitacao[0] = (conj_inicial & afnd->estados_aceitacao) != 0;
    afd->estado_inicial  = 0;
    afd->num_estados     = 1;
    fila[fim_fila++]     = 0;

    printf("  Explorando subconjuntos (BFS):\n\n");

    /*
     * Passo 2–3: para cada subconjunto não processado, calcular transições
     */
    while (inicio_fila < fim_fila) {
        int idx_atual = fila[inicio_fila++];
        ConjuntoEstados conj_atual = afd->subconjunto[idx_atual];

        printf("  Estado D%d = ", idx_atual);
        imprimir_conjunto(afnd, conj_atual);
        printf("%s\n", afd->eh_aceitacao[idx_atual] ? "  (aceitação)" : "");

        for (int s = 0; s < afnd->num_simbolos; s++) {
            /* Calcula δ_AFD(S, a) = mover(S, a) */
            ConjuntoEstados conj_destino = mover(afnd, conj_atual, s);

            printf("    δ(D%d, '%c') = mover(", idx_atual, afnd->alfabeto[s]);
            imprimir_conjunto(afnd, conj_atual);
            printf(", '%c') = ", afnd->alfabeto[s]);
            imprimir_conjunto(afnd, conj_destino);

            /* Verifica se este subconjunto já existe no AFD */
            int idx_destino = buscar_subconjunto(afd, conj_destino);

            if (idx_destino < 0) {
                /* Verifica se o AFD ainda cabe nos limites */
                if (afd->num_estados >= MAX_ESTADOS_AFD) {
                    fprintf(stderr,
                            "Erro: número de estados do AFD excede o limite "
                            "(%d). Aumente MAX_ESTADOS_AFD.\n",
                            MAX_ESTADOS_AFD);
                    return;
                }
                /* Novo subconjunto: adiciona como novo estado do AFD */
                idx_destino = afd->num_estados;
                afd->subconjunto[idx_destino] = conj_destino;
                afd->eh_aceitacao[idx_destino] =
                    (conj_destino & afnd->estados_aceitacao) != 0;
                afd->num_estados++;
                fila[fim_fila++] = idx_destino;
                printf("  → novo estado D%d", idx_destino);
            } else {
                printf("  → D%d (existente)", idx_destino);
            }
            printf("\n");

            afd->transicao[idx_atual][s] = idx_destino;
        }
        printf("\n");
    }
}

/* =================== Simulação do AFD resultante ======================= */

static int afd_aceita(const AFD *afd, const char *palavra)
{
    int estado = afd->estado_inicial;
    size_t tam = strlen(palavra);

    for (size_t i = 0; i < tam; i++) {
        int idx = -1;
        for (int s = 0; s < afd->num_simbolos; s++) {
            if (afd->alfabeto[s] == palavra[i]) {
                idx = s;
                break;
            }
        }
        if (idx < 0) return 0;  /* símbolo fora do alfabeto */
        estado = afd->transicao[estado][idx];
    }
    return afd->eh_aceitacao[estado];
}

/* =================== Impressão do AFD resultante ======================= */

static void imprimir_afd(const AFND *afnd, const AFD *afd)
{
    printf("  Tabela de Transições do AFD resultante:\n");
    printf("  %-14s", "Estado");
    for (int s = 0; s < afd->num_simbolos; s++)
        printf("| %-14c", afd->alfabeto[s]);
    printf("| Subconjunto\n  ");
    for (int s = 0; s <= afd->num_simbolos + 1; s++)
        printf("---------------");
    printf("\n");

    for (int i = 0; i < afd->num_estados; i++) {
        const char *seta    = (i == afd->estado_inicial) ? "->" : "  ";
        const char *estrela = afd->eh_aceitacao[i] ? "*" : " ";
        printf(" %s%sD%-10d", seta, estrela, i);

        for (int s = 0; s < afd->num_simbolos; s++)
            printf("| D%-13d", afd->transicao[i][s]);

        printf("| ");
        imprimir_conjunto(afnd, afd->subconjunto[i]);
        printf("\n");
    }
    printf("\n");
}

/* ============================== main =================================== */
int main(void)
{
    printf("==========================================================\n");
    printf(" Conversão AFND → AFD (Construção de Subconjuntos)\n");
    printf(" Linguagem: cadeias sobre {a,b} contendo \"ab\"\n");
    printf("==========================================================\n\n");

    /* --- Construção do AFND (mesmo do capítulo 03) --- */
    AFND afnd;
    memset(&afnd, 0, sizeof(AFND));

    afnd.num_estados = 3;
    afnd.nomes_estados[0] = "q0";
    afnd.nomes_estados[1] = "q1";
    afnd.nomes_estados[2] = "q2";

    afnd.num_simbolos = 2;
    afnd.alfabeto[0] = 'a';
    afnd.alfabeto[1] = 'b';

    afnd.estado_inicial    = 0;
    afnd.estados_aceitacao = (1u << 2);  /* F = {q2} */

    /* δ(q0, 'a') = {q0, q1},  δ(q0, 'b') = {q0} */
    afnd.transicao[0][0] = (1u << 0) | (1u << 1);
    afnd.transicao[0][1] = (1u << 0);

    /* δ(q1, 'a') = ∅,          δ(q1, 'b') = {q2} */
    afnd.transicao[1][0] = 0;
    afnd.transicao[1][1] = (1u << 2);

    /* δ(q2, 'a') = {q2},       δ(q2, 'b') = {q2} */
    afnd.transicao[2][0] = (1u << 2);
    afnd.transicao[2][1] = (1u << 2);

    printf("AFND original:\n");
    printf("  Q  = {q0, q1, q2}\n");
    printf("  Σ  = {a, b}\n");
    printf("  q₀ = q0\n");
    printf("  F  = {q2}\n\n");

    /* --- Executa a construção de subconjuntos --- */
    printf("----------------------------------------------------------\n");
    printf(" Algoritmo de Construção de Subconjuntos\n");
    printf("----------------------------------------------------------\n\n");

    AFD afd;
    construir_afd(&afnd, &afd);

    /* --- Imprime o AFD resultante --- */
    printf("----------------------------------------------------------\n");
    printf(" AFD Resultante\n");
    printf("----------------------------------------------------------\n\n");

    printf("  Número de estados: %d\n\n", afd.num_estados);
    imprimir_afd(&afnd, &afd);

    /* --- Testes de aceitação no AFD resultante --- */
    printf("----------------------------------------------------------\n");
    printf(" Testes de aceitação no AFD\n");
    printf("----------------------------------------------------------\n\n");

    const char *casos_teste[]        = {"ab", "aab", "ba", "bab", "bbb", "aabb", ""};
    const int   resultados_esperados[] = {1,    1,     0,    1,     0,     1,      0};
    int num_testes = 7;

    int acertos = 0;
    for (int i = 0; i < num_testes; i++) {
        int resultado = afd_aceita(&afd, casos_teste[i]);
        int correto   = (resultado == resultados_esperados[i]);
        printf("  \"%s\"%*s→ %s  (esperado: %s) %s\n",
               casos_teste[i],
               (int)(6 - strlen(casos_teste[i])), "",
               resultado ? "ACEITA" : "REJEITA",
               resultados_esperados[i] ? "ACEITA" : "REJEITA",
               correto ? "✓" : "✗ FALHA");
        if (correto) acertos++;
    }

    printf("\n==========================================================\n");
    printf(" Resumo: %d/%d testes corretos\n", acertos, num_testes);
    printf("==========================================================\n");

    return 0;
}
