/*
 * =============================================================================
 * Linguagens Formais e Autômatos
 * =============================================================================
 * Minimização de AFD  (Algoritmo de Preenchimento de Tabela)
 *
 * Descrição:
 *   Implementação do algoritmo de preenchimento de tabela (table-filling /
 *   Myhill–Nerode) para minimizar um Autômato Finito Determinístico (AFD).
 *
 *   Passos do algoritmo:
 *     1. Remover estados inalcançáveis a partir do estado inicial.
 *     2. Inicializar: marcar todo par (p, q) em que exatamente um dos dois
 *        é estado de aceitação (pares trivialmente distinguíveis).
 *     3. Iterar: para cada par não marcado (p, q), verificar se existe
 *        algum símbolo a tal que (δ(p,a), δ(q,a)) já está marcado.
 *        Se sim, marcar (p, q) também (são distinguíveis).
 *        Repetir até que nenhuma nova marcação ocorra (ponto fixo).
 *     4. Fundir: pares que permanecem não-marcados são equivalentes.
 *        Unir seus estados para obter o AFD mínimo.
 *
 *   Exemplo:
 *     Um AFD com 6 estados que reconhece cadeias binárias cujo número
 *     de 0's é par. Os estados q1 e q3, q2 e q4, entre outros, são
 *     equivalentes, permitindo redução para 2 estados.
 *
 * Compilação:
 *   gcc -Wall -Wextra -std=c99 -o minimizacao minimizacao.c
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_ESTADOS  20
#define MAX_SIMBOLOS  5

/* ========================= Estrutura do AFD ============================ */
typedef struct {
    int num_estados;
    int num_simbolos;
    char alfabeto[MAX_SIMBOLOS];
    int transicao[MAX_ESTADOS][MAX_SIMBOLOS];
    int estado_inicial;
    int eh_aceitacao[MAX_ESTADOS];
    const char *nomes_estados[MAX_ESTADOS];
} AFD;

/* ================ Passo 1: remoção de estados inalcançáveis ============ */

/*
 * Percorre o AFD a partir do estado inicial (BFS) e marca os estados
 * acessíveis.  Retorna o número de estados alcançáveis.
 */
static int marcar_alcancaveis(const AFD *afd, int alcancavel[])
{
    memset(alcancavel, 0, sizeof(int) * MAX_ESTADOS);

    int fila[MAX_ESTADOS];
    int inicio = 0, fim = 0;

    alcancavel[afd->estado_inicial] = 1;
    fila[fim++] = afd->estado_inicial;

    while (inicio < fim) {
        int q = fila[inicio++];
        for (int s = 0; s < afd->num_simbolos; s++) {
            int destino = afd->transicao[q][s];
            if (destino >= 0 && !alcancavel[destino]) {
                alcancavel[destino] = 1;
                fila[fim++] = destino;
            }
        }
    }

    int contagem = 0;
    for (int i = 0; i < afd->num_estados; i++)
        contagem += alcancavel[i];
    return contagem;
}

/* ========= Passo 2–3: preenchimento da tabela de distinção ============= */

/*
 * Tabela triangular inferior: marcado[p][q] com p > q indica que
 * os estados p e q são distinguíveis.
 */
static void preencher_tabela(const AFD *afd, int alcancavel[],
                             int marcado[MAX_ESTADOS][MAX_ESTADOS])
{
    memset(marcado, 0, sizeof(int) * MAX_ESTADOS * MAX_ESTADOS);

    /*
     * Passo 2: marcar pares (p, q) trivialmente distinguíveis.
     * Se um é de aceitação e o outro não, são distinguíveis.
     */
    for (int p = 0; p < afd->num_estados; p++) {
        if (!alcancavel[p]) continue;
        for (int q = 0; q < p; q++) {
            if (!alcancavel[q]) continue;
            if (afd->eh_aceitacao[p] != afd->eh_aceitacao[q])
                marcado[p][q] = 1;
        }
    }

    /*
     * Passo 3: iterar até ponto fixo.
     * Para cada par não-marcado (p, q), se existe símbolo a tal que
     * o par (δ(p,a), δ(q,a)) já está marcado, então (p, q) também
     * é distinguível.
     */
    int mudou = 1;
    while (mudou) {
        mudou = 0;
        for (int p = 0; p < afd->num_estados; p++) {
            if (!alcancavel[p]) continue;
            for (int q = 0; q < p; q++) {
                if (!alcancavel[q]) continue;
                if (marcado[p][q]) continue;   /* já distinguíveis */

                for (int s = 0; s < afd->num_simbolos; s++) {
                    int dp = afd->transicao[p][s];
                    int dq = afd->transicao[q][s];

                    /* Normaliza para p' > q' na tabela triangular */
                    int maior = dp > dq ? dp : dq;
                    int menor = dp > dq ? dq : dp;

                    if (maior != menor && marcado[maior][menor]) {
                        marcado[p][q] = 1;
                        mudou = 1;
                        break;
                    }
                }
            }
        }
    }
}

/* =========== Passo 4: determinar classes de equivalência =============== */

/*
 * Atribui a cada estado alcançável um representante de sua classe de
 * equivalência (o menor índice da classe).
 * Retorna o número de classes distintas.
 */
static int determinar_classes(const AFD *afd, int alcancavel[],
                              int marcado[MAX_ESTADOS][MAX_ESTADOS],
                              int classe[])
{
    /* Inicialmente, cada estado é seu próprio representante */
    for (int i = 0; i < afd->num_estados; i++)
        classe[i] = i;

    /*
     * Para cada par não-marcado (equivalente), unimos os estados
     * atribuindo ao de maior índice o representante do menor.
     */
    for (int p = 0; p < afd->num_estados; p++) {
        if (!alcancavel[p]) continue;
        for (int q = 0; q < p; q++) {
            if (!alcancavel[q]) continue;
            if (!marcado[p][q]) {
                /* p e q são equivalentes — unir classes */
                int rep_antigo = classe[p];
                int rep_novo   = classe[q];
                if (rep_antigo != rep_novo) {
                    /* Atualiza todos que apontam para rep_antigo */
                    for (int k = 0; k < afd->num_estados; k++) {
                        if (classe[k] == rep_antigo)
                            classe[k] = rep_novo;
                    }
                }
            }
        }
    }

    /* Renumera classes sequencialmente: 0, 1, 2, ... */
    int mapeamento[MAX_ESTADOS];
    memset(mapeamento, -1, sizeof(mapeamento));
    int num_classes = 0;

    for (int i = 0; i < afd->num_estados; i++) {
        if (!alcancavel[i]) {
            classe[i] = -1;
            continue;
        }
        if (mapeamento[classe[i]] < 0)
            mapeamento[classe[i]] = num_classes++;
        classe[i] = mapeamento[classe[i]];
    }

    return num_classes;
}

/* ============= Construção do AFD mínimo a partir das classes =========== */

static void construir_afd_minimo(const AFD *original, int alcancavel[],
                                 int classe[], int num_classes,
                                 AFD *minimo)
{
    memset(minimo, 0, sizeof(AFD));
    minimo->num_estados  = num_classes;
    minimo->num_simbolos = original->num_simbolos;
    memcpy(minimo->alfabeto, original->alfabeto, sizeof(original->alfabeto));

    /* Inicializa transições como indefinidas */
    memset(minimo->transicao, -1, sizeof(minimo->transicao));

    /* Estado inicial do AFD mínimo */
    minimo->estado_inicial = classe[original->estado_inicial];

    /* Nomes dos estados do AFD mínimo */
    static const char *nomes_min[] = {
        "M0", "M1", "M2", "M3", "M4", "M5", "M6", "M7",
        "M8", "M9", "M10","M11","M12","M13","M14","M15",
        "M16","M17","M18","M19"
    };
    for (int i = 0; i < num_classes && i < MAX_ESTADOS; i++)
        minimo->nomes_estados[i] = nomes_min[i];

    /*
     * Para cada estado alcançável do AFD original, propagamos as
     * transições para o AFD mínimo usando as classes de equivalência.
     */
    for (int q = 0; q < original->num_estados; q++) {
        if (!alcancavel[q]) continue;
        int cq = classe[q];

        /* Se o estado original é de aceitação, a classe também é */
        if (original->eh_aceitacao[q])
            minimo->eh_aceitacao[cq] = 1;

        for (int s = 0; s < original->num_simbolos; s++) {
            int destino = original->transicao[q][s];
            if (destino >= 0 && alcancavel[destino])
                minimo->transicao[cq][s] = classe[destino];
        }
    }
}

/* ======================== Impressão e simulação ======================== */

static void imprimir_tabela_distincao(const AFD *afd, int alcancavel[],
                                      int marcado[MAX_ESTADOS][MAX_ESTADOS])
{
    printf("  Tabela de Distinção (X = distinguíveis):\n\n");

    /* Cabeçalho */
    printf("  %8s", "");
    for (int q = 0; q < afd->num_estados - 1; q++) {
        if (!alcancavel[q]) continue;
        printf("  %-4s", afd->nomes_estados[q]);
    }
    printf("\n");

    for (int p = 1; p < afd->num_estados; p++) {
        if (!alcancavel[p]) continue;
        printf("  %-8s", afd->nomes_estados[p]);
        for (int q = 0; q < p; q++) {
            if (!alcancavel[q]) continue;
            printf("  %-4s", marcado[p][q] ? "X" : "-");
        }
        printf("\n");
    }
    printf("\n");
}

static void imprimir_tabela_transicao(const AFD *afd)
{
    printf("  %-10s", "Estado");
    for (int s = 0; s < afd->num_simbolos; s++)
        printf("| %-10c", afd->alfabeto[s]);
    printf("\n  ");
    for (int s = 0; s <= afd->num_simbolos; s++)
        printf("-----------");
    printf("\n");

    for (int i = 0; i < afd->num_estados; i++) {
        const char *seta    = (i == afd->estado_inicial) ? "->" : "  ";
        const char *estrela = afd->eh_aceitacao[i] ? "*" : " ";
        printf(" %s%s%-7s", seta, estrela, afd->nomes_estados[i]);

        for (int s = 0; s < afd->num_simbolos; s++) {
            int d = afd->transicao[i][s];
            if (d >= 0)
                printf("| %-10s", afd->nomes_estados[d]);
            else
                printf("| %-10s", "—");
        }
        printf("\n");
    }
    printf("\n");
}

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
        if (idx < 0) return 0;
        estado = afd->transicao[estado][idx];
        if (estado < 0) return 0;
    }
    return afd->eh_aceitacao[estado];
}

/* ============================== main =================================== */
int main(void)
{
    printf("==========================================================\n");
    printf(" Minimização de AFD — Algoritmo de Preenchimento de Tabela\n");
    printf("==========================================================\n\n");

    /*
     * AFD de exemplo: reconhece cadeias binárias com número par de 0's.
     *
     * O AFD possui estados redundantes de propósito:
     *   q0 (par, início)      — aceitação
     *   q1 (ímpar)            — rejeição
     *   q2 (par, via '1')     — aceitação  ← equivalente a q0
     *   q3 (ímpar, via '1')   — rejeição   ← equivalente a q1
     *   q4 (par, via '11')    — aceitação  ← equivalente a q0/q2
     *   q5 (ímpar, via '11')  — rejeição   ← equivalente a q1/q3
     *
     * Após minimização, devemos obter apenas 2 estados: PAR e ÍMPAR.
     *
     *   Σ = {0, 1}
     */
    AFD afd;
    memset(&afd, 0, sizeof(AFD));

    afd.num_estados  = 6;
    afd.num_simbolos = 2;
    afd.alfabeto[0]  = '0';
    afd.alfabeto[1]  = '1';

    afd.nomes_estados[0] = "q0";
    afd.nomes_estados[1] = "q1";
    afd.nomes_estados[2] = "q2";
    afd.nomes_estados[3] = "q3";
    afd.nomes_estados[4] = "q4";
    afd.nomes_estados[5] = "q5";

    afd.estado_inicial = 0;

    /* Estados de aceitação: q0, q2, q4 (número par de 0's) */
    afd.eh_aceitacao[0] = 1;
    afd.eh_aceitacao[1] = 0;
    afd.eh_aceitacao[2] = 1;
    afd.eh_aceitacao[3] = 0;
    afd.eh_aceitacao[4] = 1;
    afd.eh_aceitacao[5] = 0;

    /*
     * Transições (projetadas para criar estados redundantes):
     *
     *   δ(q0, '0') = q1    δ(q0, '1') = q2
     *   δ(q1, '0') = q0    δ(q1, '1') = q3
     *   δ(q2, '0') = q3    δ(q2, '1') = q4
     *   δ(q3, '0') = q2    δ(q3, '1') = q5
     *   δ(q4, '0') = q5    δ(q4, '1') = q0
     *   δ(q5, '0') = q4    δ(q5, '1') = q1
     *
     * Observação: q0 ≡ q2 ≡ q4 (todos "par") e q1 ≡ q3 ≡ q5 (todos "ímpar").
     */
    afd.transicao[0][0] = 1;  afd.transicao[0][1] = 2;
    afd.transicao[1][0] = 0;  afd.transicao[1][1] = 3;
    afd.transicao[2][0] = 3;  afd.transicao[2][1] = 4;
    afd.transicao[3][0] = 2;  afd.transicao[3][1] = 5;
    afd.transicao[4][0] = 5;  afd.transicao[4][1] = 0;
    afd.transicao[5][0] = 4;  afd.transicao[5][1] = 1;

    /* --- Imprime o AFD original --- */
    printf("AFD original (%d estados):\n", afd.num_estados);
    printf("  Linguagem: cadeias binárias com número par de 0's\n\n");
    imprimir_tabela_transicao(&afd);

    /* --- Passo 1: estados alcançáveis --- */
    printf("----------------------------------------------------------\n");
    printf(" Passo 1: Remoção de estados inalcançáveis\n");
    printf("----------------------------------------------------------\n\n");

    int alcancavel[MAX_ESTADOS];
    int num_alcancaveis = marcar_alcancaveis(&afd, alcancavel);

    printf("  Estados alcançáveis: {");
    int primeiro = 1;
    for (int i = 0; i < afd.num_estados; i++) {
        if (alcancavel[i]) {
            if (!primeiro) printf(", ");
            printf("%s", afd.nomes_estados[i]);
            primeiro = 0;
        }
    }
    printf("}  (%d de %d)\n\n", num_alcancaveis, afd.num_estados);

    /* --- Passos 2–3: tabela de distinção --- */
    printf("----------------------------------------------------------\n");
    printf(" Passos 2–3: Preenchimento da tabela de distinção\n");
    printf("----------------------------------------------------------\n\n");

    int marcado[MAX_ESTADOS][MAX_ESTADOS];
    preencher_tabela(&afd, alcancavel, marcado);
    imprimir_tabela_distincao(&afd, alcancavel, marcado);

    /* --- Passo 4: classes de equivalência --- */
    printf("----------------------------------------------------------\n");
    printf(" Passo 4: Classes de equivalência\n");
    printf("----------------------------------------------------------\n\n");

    int classe[MAX_ESTADOS];
    int num_classes = determinar_classes(&afd, alcancavel, marcado, classe);

    /* Imprime as classes */
    printf("  %d classes de equivalência encontradas:\n", num_classes);
    for (int c = 0; c < num_classes; c++) {
        printf("    Classe %d: {", c);
        int prim = 1;
        for (int i = 0; i < afd.num_estados; i++) {
            if (classe[i] == c) {
                if (!prim) printf(", ");
                printf("%s", afd.nomes_estados[i]);
                prim = 0;
            }
        }
        printf("}\n");
    }
    printf("\n");

    /* --- Construção e impressão do AFD mínimo --- */
    printf("----------------------------------------------------------\n");
    printf(" AFD Mínimo\n");
    printf("----------------------------------------------------------\n\n");

    AFD afd_min;
    construir_afd_minimo(&afd, alcancavel, classe, num_classes, &afd_min);

    printf("  Reduzido de %d para %d estados.\n\n", afd.num_estados,
           afd_min.num_estados);
    imprimir_tabela_transicao(&afd_min);

    /* --- Testes: verifica que o AFD mínimo aceita a mesma linguagem --- */
    printf("----------------------------------------------------------\n");
    printf(" Testes de equivalência (AFD original vs. AFD mínimo)\n");
    printf("----------------------------------------------------------\n\n");

    const char *casos_teste[] = {"", "0", "1", "00", "01", "10", "11",
                                 "000", "001", "100", "110", "0110", "0010"};
    int num_testes = 13;
    int acertos = 0;

    for (int i = 0; i < num_testes; i++) {
        int res_orig = afd_aceita(&afd, casos_teste[i]);
        int res_min  = afd_aceita(&afd_min, casos_teste[i]);
        int iguais   = (res_orig == res_min);

        printf("  \"%s\"%*s orig=%s  min=%s  %s\n",
               casos_teste[i],
               (int)(5 - strlen(casos_teste[i])), "",
               res_orig ? "ACEITA" : "REJEITA",
               res_min  ? "ACEITA" : "REJEITA",
               iguais   ? "✓" : "✗ DIVERGÊNCIA");
        if (iguais) acertos++;
    }

    printf("\n==========================================================\n");
    printf(" Resumo: %d/%d testes equivalentes\n", acertos, num_testes);
    printf("==========================================================\n");

    return 0;
}
