/*
 * Linguagens Formais e Autômatos
 *
 * Busca de Padrões com Autômato Finito
 * Demonstrates a practical application of finite automata:
 * string pattern matching using a DFA constructed from a pattern.
 *
 * Similar to the approach used in grep and text search tools.
 */

#include <stdio.h>
#include <string.h>

#define MAX_PADRAO      64
#define MAX_TEXTO       256
#define MAX_ALFABETO    26
#define MAX_ESTADOS     (MAX_PADRAO + 1)
#define MAX_OCORRENCIAS 64

/* ================ Autômato Finito para Busca ============= */

typedef struct {
    int tabela[MAX_ESTADOS][MAX_ALFABETO];  /* tabela de transições */
    char padrao[MAX_PADRAO];
    int tam_padrao;
    char alfabeto[MAX_ALFABETO];
    int tam_alfabeto;
} AFDBusca;

/* Retorna o índice do caractere no alfabeto, ou -1 se ausente */
static int indice_char(const AFDBusca *afd, char c)
{
    int i;
    for (i = 0; i < afd->tam_alfabeto; i++) {
        if (afd->alfabeto[i] == c)
            return i;
    }
    return -1;
}

/* Extrai caracteres únicos do padrão para formar o alfabeto */
static void construir_alfabeto(AFDBusca *afd)
{
    int i;
    afd->tam_alfabeto = 0;
    for (i = 0; i < afd->tam_padrao; i++) {
        if (indice_char(afd, afd->padrao[i]) == -1)
            afd->alfabeto[afd->tam_alfabeto++] = afd->padrao[i];
    }
}

/*
 * Constrói a tabela de transições do AFD para busca de padrão.
 *
 * Para cada estado j e caractere c, δ(j, c) é o comprimento do
 * maior prefixo próprio de P que também é sufixo de P[0..j-1]c.
 *
 * Método baseado na construção descrita em Cormen et al. (CLRS).
 */
static void construir_afd(AFDBusca *afd, const char *padrao)
{
    int estado, ci;

    strncpy(afd->padrao, padrao, MAX_PADRAO - 1);
    afd->padrao[MAX_PADRAO - 1] = '\0';
    afd->tam_padrao = (int)strlen(afd->padrao);

    construir_alfabeto(afd);

    for (estado = 0; estado <= afd->tam_padrao; estado++) {
        for (ci = 0; ci < afd->tam_alfabeto; ci++) {
            char c = afd->alfabeto[ci];
            int k = estado + 1;
            if (k > afd->tam_padrao)
                k = afd->tam_padrao;

            /* Encontra o maior k tal que P[0..k-1] é sufixo de P[0..estado-1]c */
            while (k > 0) {
                if (afd->padrao[k - 1] == c) {
                    int j, match = 1;
                    for (j = 0; j < k - 1; j++) {
                        int pos = estado - (k - 1) + j;
                        if (pos < 0 || afd->padrao[j] != afd->padrao[pos]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match)
                        break;
                }
                k--;
            }
            afd->tabela[estado][ci] = k;
        }
    }
}

/* ================ Impressão do AFD ======================= */

/* Imprime a tabela de transições do AFD */
static void imprimir_tabela(const AFDBusca *afd)
{
    int estado, ci;

    printf("  Tabela de transições δ(estado, caractere) → próximo estado:\n\n");

    printf("  Estado │");
    for (ci = 0; ci < afd->tam_alfabeto; ci++)
        printf("  '%c' ", afd->alfabeto[ci]);
    printf("\n");

    printf("  ───────┼");
    for (ci = 0; ci < afd->tam_alfabeto; ci++)
        printf("──────");
    printf("\n");

    for (estado = 0; estado <= afd->tam_padrao; estado++) {
        if (estado == afd->tam_padrao)
            printf("  *q%-4d│", estado);
        else
            printf("   q%-4d│", estado);
        for (ci = 0; ci < afd->tam_alfabeto; ci++)
            printf("  q%-3d", afd->tabela[estado][ci]);
        printf("\n");
    }

    printf("\n  Estado inicial: q0\n");
    printf("  Estado de aceitação (*): q%d\n\n", afd->tam_padrao);
}

/* ================ Busca no Texto ========================= */

/*
 * Executa a busca do padrão no texto usando o AFD construído.
 * Imprime as transições passo a passo e retorna o número de ocorrências.
 */
static int buscar_padrao(const AFDBusca *afd, const char *texto)
{
    int tam_texto = (int)strlen(texto);
    int estado = 0;
    int i;
    int ocorrencias[MAX_OCORRENCIAS];
    int num_ocorrencias = 0;

    printf("  Rastreamento passo a passo:\n\n");
    printf("  Pos │ Char │ Estado → Próximo │\n");
    printf("  ────┼──────┼──────────────────┼───────────────────\n");

    for (i = 0; i < tam_texto; i++) {
        int ci = indice_char(afd, texto[i]);
        int proximo = (ci >= 0) ? afd->tabela[estado][ci] : 0;

        printf("  %3d │ '%c'  │ q%d → q%-10d│", i, texto[i], estado, proximo);

        if (proximo == afd->tam_padrao) {
            int pos_inicio = i - afd->tam_padrao + 1;
            printf(" ✓ Encontrado na posição %d", pos_inicio);
            if (num_ocorrencias < MAX_OCORRENCIAS)
                ocorrencias[num_ocorrencias++] = pos_inicio;
        }
        printf("\n");

        estado = proximo;
    }

    printf("\n");

    if (num_ocorrencias > 0) {
        printf("  Resultado: %d ocorrência(s) encontrada(s) ✓\n", num_ocorrencias);
        printf("  Posições: {");
        for (i = 0; i < num_ocorrencias; i++) {
            if (i > 0)
                printf(", ");
            printf("%d", ocorrencias[i]);
        }
        printf("}\n");
    } else {
        printf("  Resultado: Padrão não encontrado ✗\n");
    }

    return num_ocorrencias;
}

/* ================ Execução de Exemplo ==================== */

static void executar_busca(const char *padrao, const char *texto)
{
    AFDBusca afd;
    int ci;

    printf("  Padrão: \"%s\" (tamanho %d)\n", padrao, (int)strlen(padrao));
    printf("  Texto:  \"%s\" (tamanho %d)\n\n", texto, (int)strlen(texto));

    construir_afd(&afd, padrao);

    printf("  Construção do AFD:\n");
    printf("  Q = {q0, ..., q%d}  (q%d = aceitação)\n",
           afd.tam_padrao, afd.tam_padrao);
    printf("  Σ = {");
    for (ci = 0; ci < afd.tam_alfabeto; ci++) {
        if (ci > 0)
            printf(", ");
        printf("'%c'", afd.alfabeto[ci]);
    }
    printf("}\n\n");

    imprimir_tabela(&afd);
    buscar_padrao(&afd, texto);
}

/* ========================= Main ========================== */

int main(void)
{
    printf("================================================\n");
    printf(" Busca de Padrões com Autômato Finito\n");
    printf("================================================\n\n");

    printf("Aplicação de Autômatos Finitos Determinísticos:\n\n");
    printf("  Um AFD pode ser construído a partir de um padrão P\n");
    printf("  para buscar todas as ocorrências de P em um texto T.\n");
    printf("  O AFD percorre o texto em tempo O(n), onde n = |T|.\n\n");
    printf("  Cada estado q_k indica que os últimos k caracteres\n");
    printf("  lidos coincidem com P[0..k-1]. Ao atingir q_m\n");
    printf("  (m = |P|), uma ocorrência é encontrada.\n\n");
    printf("  Este é o princípio usado em ferramentas como grep.\n\n");

    /* ---------- Exemplo 1 ---------- */
    printf("------------------------------------------------\n");
    printf(" Exemplo 1: Padrão \"aba\" em \"ababababaaba\"\n");
    printf("------------------------------------------------\n\n");

    executar_busca("aba", "ababababaaba");

    printf("\n");

    /* ---------- Exemplo 2 ---------- */
    printf("------------------------------------------------\n");
    printf(" Exemplo 2: Padrão \"aab\" em \"aabaabaaab\"\n");
    printf("------------------------------------------------\n\n");

    executar_busca("aab", "aabaabaaab");

    printf("\n");

    return 0;
}
