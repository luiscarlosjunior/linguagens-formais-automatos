/*
 * Linguagens Formais e Autômatos
 *
 * Gramática Sensível ao Contexto — Autômato Linearmente Limitado (LBA)
 * Reconhece a linguagem L = { a^n b^n c^n | n >= 1 }
 *
 * Definição formal:
 *   M = (Q, Σ, Γ, δ, q0, F)
 *   Q = {q0, q1, q2, q3, q4}
 *   Σ = {a, b, c}
 *   Γ = {a, b, c, X, Y, Z}
 *   q0 = estado inicial
 *   F  = {q4}
 *
 * Gramática sensível ao contexto equivalente:
 *   S  → aSBC | aBC
 *   CB → BC
 *   aB → ab
 *   bB → bb
 *   bC → bc
 *   cC → cc
 */

#include <stdio.h>
#include <string.h>

#define TAM_FITA 256

/* ==================== Fita do LBA ======================== */

typedef struct {
    char celulas[TAM_FITA];
    int tamanho;
} Fita;

/* Inicializa a fita com a palavra de entrada */
void fita_inicializar(Fita *f, const char *palavra)
{
    int tam = (int)strlen(palavra);
    if (tam >= TAM_FITA)
        tam = TAM_FITA - 1;
    memcpy(f->celulas, palavra, tam);
    f->celulas[tam] = '\0';
    f->tamanho = tam;
}

/* Imprime o conteúdo atual da fita entre colchetes */
void fita_imprimir(const Fita *f)
{
    int i;
    printf("[");
    for (i = 0; i < f->tamanho; i++)
        printf("%c", f->celulas[i]);
    printf("]");
}

/* ============= Autômato Linearmente Limitado ============= */

/*
 * Algoritmo de marcação para reconhecer a^n b^n c^n:
 *
 *   1. Encontra o 'a' mais à esquerda não marcado, marca como 'X'.
 *   2. Move à direita até encontrar 'b' não marcado, marca como 'Y'.
 *   3. Move à direita até encontrar 'c' não marcado, marca como 'Z'.
 *   4. Rebobina ao início e repete a partir do passo 1.
 *   5. Quando não há mais 'a', verifica se todos os símbolos foram marcados.
 */

/* Imprime o estado da fita com indicador de posição */
static void imprimir_passo(const Fita *f, int pos, const char *descricao)
{
    int i;
    printf("    ");
    fita_imprimir(f);
    printf("  pos=%d", pos);
    if (descricao)
        printf("  %s", descricao);
    printf("\n");

    /* Seta indicadora de posição */
    printf("    ");
    printf(" ");  /* colchete de abertura */
    for (i = 0; i < pos; i++)
        printf(" ");
    printf("^\n");
}

/*
 * Simula o LBA sobre a palavra de entrada.
 * Retorna 1 se aceita, 0 se rejeita.
 */
int lba_aceita(const char *palavra)
{
    Fita fita;
    int pos;
    int passo = 0;

    /* Palavra vazia é rejeitada */
    if (strlen(palavra) == 0) {
        printf("    (palavra vazia)\n");
        return 0;
    }

    fita_inicializar(&fita, palavra);

    printf("    Fita inicial: ");
    fita_imprimir(&fita);
    printf("\n\n");

    pos = 0;

    while (1) {
        /* Passo 1: encontrar próximo 'a' não marcado */
        while (pos < fita.tamanho && fita.celulas[pos] == 'X')
            pos++;

        /* Se não há mais 'a', verificar se tudo foi marcado */
        if (pos >= fita.tamanho || fita.celulas[pos] != 'a') {
            int i;
            for (i = 0; i < fita.tamanho; i++) {
                if (fita.celulas[i] != 'X' &&
                    fita.celulas[i] != 'Y' &&
                    fita.celulas[i] != 'Z')
                    return 0;  /* símbolo não marcado restante */
            }
            return 1;  /* todos marcados → aceita */
        }

        passo++;
        printf("    --- Iteração %d ---\n", passo);

        /* Marca 'a' como 'X' */
        fita.celulas[pos] = 'X';
        imprimir_passo(&fita, pos, "marca a → X");
        pos++;

        /* Passo 2: pular 'a's não marcados e 'Y's, encontrar 'b' */
        while (pos < fita.tamanho &&
               (fita.celulas[pos] == 'a' || fita.celulas[pos] == 'Y'))
            pos++;

        if (pos >= fita.tamanho || fita.celulas[pos] != 'b')
            return 0;  /* nenhum 'b' correspondente */

        /* Marca 'b' como 'Y' */
        fita.celulas[pos] = 'Y';
        imprimir_passo(&fita, pos, "marca b → Y");
        pos++;

        /* Passo 3: pular 'b's não marcados e 'Z's, encontrar 'c' */
        while (pos < fita.tamanho &&
               (fita.celulas[pos] == 'b' || fita.celulas[pos] == 'Z'))
            pos++;

        if (pos >= fita.tamanho || fita.celulas[pos] != 'c')
            return 0;  /* nenhum 'c' correspondente */

        /* Marca 'c' como 'Z' */
        fita.celulas[pos] = 'Z';
        imprimir_passo(&fita, pos, "marca c → Z");

        /* Passo 4: rebobinar ao início */
        pos = 0;

        printf("    Fita atual:    ");
        fita_imprimir(&fita);
        printf("  (rebobina)\n\n");
    }
}

/* ========================= Main ========================== */

int main(void)
{
    const char *testes[] = {
        "abc", "aabbcc", "aaabbbccc",
        "aabbc", "abbc", "", "ab", "aabbccc"
    };
    int n_testes = (int)(sizeof(testes) / sizeof(testes[0]));
    int i;

    printf("================================================\n");
    printf(" Gramática Sensível ao Contexto\n");
    printf(" Autômato Linearmente Limitado (LBA)\n");
    printf(" L = { a^n b^n c^n | n >= 1 }\n");
    printf("================================================\n\n");

    printf("Definição formal do LBA:\n");
    printf("  M = ({q0..q4}, {a,b,c}, {a,b,c,X,Y,Z}, δ, q0, {q4})\n\n");

    printf("Gramática sensível ao contexto:\n");
    printf("  S  → aSBC | aBC\n");
    printf("  CB → BC\n");
    printf("  aB → ab\n");
    printf("  bB → bb\n");
    printf("  bC → bc\n");
    printf("  cC → cc\n\n");

    printf("Algoritmo de marcação na fita:\n");
    printf("  1. Encontra 'a' não marcado, marca como X\n");
    printf("  2. Encontra 'b' não marcado, marca como Y\n");
    printf("  3. Encontra 'c' não marcado, marca como Z\n");
    printf("  4. Rebobina e repete até marcar tudo\n\n");

    printf("------------------------------------------------\n");
    printf(" Testando palavras\n");
    printf("------------------------------------------------\n\n");

    for (i = 0; i < n_testes; i++) {
        int resultado;

        if (strlen(testes[i]) == 0)
            printf("Palavra: ε (vazia)\n");
        else
            printf("Palavra: \"%s\"\n", testes[i]);

        resultado = lba_aceita(testes[i]);
        printf("  Resultado: %s\n\n", resultado ? "ACEITA ✓" : "REJEITA ✗");
    }

    return 0;
}
