/*
 * Linguagens Formais e Autômatos
 * Capítulo 2 - Alfabetos, Palavras e Linguagens
 *
 * Este programa demonstra os conceitos fundamentais:
 *   - Alfabeto (Σ): conjunto finito e não vazio de símbolos
 *   - Palavra (w): sequência finita de símbolos do alfabeto
 *   - Comprimento de uma palavra |w|
 *   - Palavra vazia (ε): palavra com comprimento zero
 *   - Concatenação de palavras
 *   - Reverso de uma palavra (w^R)
 *   - Potência de uma palavra (w^n)
 *   - Fecho de Kleene (Σ*): conjunto de todas as palavras sobre Σ
 */

#include <stdio.h>
#include <string.h>

#define MAX_PALAVRA 256

/*
 * Comprimento de uma palavra.
 * O comprimento |w| é o número de símbolos na palavra.
 * |ε| = 0 (a palavra vazia tem comprimento zero).
 */
int comprimento(const char *palavra) {
    return (int)strlen(palavra);
}

/*
 * Reverso de uma palavra.
 * Se w = a1 a2 ... an, então w^R = an ... a2 a1.
 * Exemplo: (abc)^R = cba
 */
void reverso(const char *palavra, char *resultado) {
    int len = comprimento(palavra);
    for (int i = 0; i < len; i++)
        resultado[i] = palavra[len - 1 - i];
    resultado[len] = '\0';
}

/*
 * Concatenação de duas palavras.
 * Se u = a1...am e v = b1...bn, então u·v = a1...am b1...bn.
 * Propriedade: |u·v| = |u| + |v|
 * Elemento neutro: w·ε = ε·w = w
 *
 * Pré-condição: o buffer `resultado` deve ter pelo menos MAX_PALAVRA bytes.
 */
void concatenar(const char *u, const char *v, char *resultado) {
    size_t lu = strlen(u);
    size_t lv = strlen(v);
    if (lu + lv >= MAX_PALAVRA) {
        fprintf(stderr, "Erro: concatenação excede o tamanho máximo (%d).\n",
                MAX_PALAVRA);
        resultado[0] = '\0';
        return;
    }
    strcpy(resultado, u);
    strcat(resultado, v);
}

/*
 * Potência de uma palavra.
 * w^0 = ε (palavra vazia)
 * w^n = w · w^(n-1), para n ≥ 1
 * Exemplo: (ab)^3 = ababab
 *
 * Pré-condição: o buffer `resultado` deve ter pelo menos MAX_PALAVRA bytes.
 */
void potencia(const char *palavra, int n, char *resultado) {
    size_t lp = strlen(palavra);
    resultado[0] = '\0';
    for (int i = 0; i < n; i++) {
        if (strlen(resultado) + lp >= MAX_PALAVRA) {
            fprintf(stderr, "Erro: potência excede o tamanho máximo (%d).\n",
                    MAX_PALAVRA);
            return;
        }
        strcat(resultado, palavra);
    }
}

/*
 * Geração do fecho de Kleene Σ* até um comprimento máximo.
 * Σ* = {ε} ∪ Σ ∪ Σ² ∪ Σ³ ∪ ...
 * Σ* contém todas as palavras possíveis sobre o alfabeto Σ,
 * incluindo a palavra vazia ε.
 *
 * Esta função gera todas as palavras de comprimento 0 até max_len
 * sobre o alfabeto fornecido.
 */
void gerar_palavras(const char *alfabeto, int tam_alfa, int max_len,
                    char palavra[], int pos) {
    /* Imprime a palavra atual (inclui ε quando pos == 0) */
    palavra[pos] = '\0';
    if (pos == 0)
        printf("  ε");
    else
        printf("  %s", palavra);
    printf("\n");

    /* Gera recursivamente palavras maiores */
    if (pos < max_len) {
        for (int i = 0; i < tam_alfa; i++) {
            palavra[pos] = alfabeto[i];
            gerar_palavras(alfabeto, tam_alfa, max_len, palavra, pos + 1);
        }
    }
}

int main(void) {
    printf("=== Alfabetos, Palavras e Linguagens ===\n\n");

    /* --- Alfabeto --- */
    char sigma[] = {'a', 'b'};
    int tam_sigma = 2;
    printf("Alfabeto Σ = {");
    for (int i = 0; i < tam_sigma; i++) {
        printf("%c", sigma[i]);
        if (i < tam_sigma - 1)
            printf(", ");
    }
    printf("}\n\n");

    /* --- Comprimento --- */
    const char *w1 = "abba";
    printf("Palavra w1 = \"%s\"\n", w1);
    printf("|w1| = %d\n", comprimento(w1));
    printf("|ε|  = %d  (palavra vazia)\n\n", comprimento(""));

    /* --- Reverso --- */
    char rev[MAX_PALAVRA];
    reverso(w1, rev);
    printf("Reverso de \"%s\" = \"%s\"\n\n", w1, rev);

    /* --- Concatenação --- */
    const char *u = "ab";
    const char *v = "ba";
    char concat[MAX_PALAVRA];
    concatenar(u, v, concat);
    printf("Concatenação: \"%s\" · \"%s\" = \"%s\"\n", u, v, concat);
    printf("|u·v| = %d = |u| + |v| = %d + %d\n\n",
           comprimento(concat), comprimento(u), comprimento(v));

    /* Concatenação com a palavra vazia (elemento neutro) */
    char concat_eps[MAX_PALAVRA];
    concatenar(w1, "", concat_eps);
    printf("Elemento neutro: \"%s\" · ε = \"%s\"\n\n", w1, concat_eps);

    /* --- Potência de palavra --- */
    const char *base = "ab";
    printf("Potência de \"%s\":\n", base);
    for (int n = 0; n <= 4; n++) {
        char pot[MAX_PALAVRA];
        potencia(base, n, pot);
        printf("  (\"%s\")^%d = \"%s\"  (comprimento %d)\n",
               base, n, pot, comprimento(pot));
    }
    printf("\n");

    /* --- Fecho de Kleene Σ* --- */
    printf("Fecho de Kleene Σ* (palavras de comprimento 0 a 3):\n");
    printf("Σ* = {ε} ∪ Σ¹ ∪ Σ² ∪ Σ³ ∪ ...\n\n");
    char buffer[MAX_PALAVRA];
    gerar_palavras(sigma, tam_sigma, 3, buffer, 0);

    printf("\nTotal de palavras de comprimento 0 a 3 sobre Σ = {a, b}:\n");
    printf("  |Σ|^0 + |Σ|^1 + |Σ|^2 + |Σ|^3 = 1 + 2 + 4 + 8 = 15\n");

    return 0;
}
