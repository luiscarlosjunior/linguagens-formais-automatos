/*
 * =============================================================================
 * Linguagens Formais e Autômatos
 * =============================================================================
 * Expressões Regulares — Casamento Básico (implementação recursiva)
 *
 * Descrição:
 *   Implementação didática de um casador (matcher) de expressões regulares
 *   simples, sem usar a biblioteca POSIX <regex.h>.  O objetivo é mostrar
 *   como a semântica de concatenação, escolha e fecho de Kleene — operações
 *   fundamentais das expressões regulares formais — se traduzem em código.
 *
 *   Operadores suportados:
 *     c       — literal: casa exatamente o caractere c
 *     .       — curinga: casa qualquer caractere único
 *     c*      — fecho de Kleene: zero ou mais ocorrências de c (ou de .)
 *
 *   A relação com a teoria:
 *     Na construção de Thompson, cada operador da expressão regular é
 *     convertido em um fragmento de AFND (autômato finito não-determinístico)
 *     usando transições-ε.  Aqui, em vez de construir o autômato
 *     explicitamente, simulamos o não-determinismo por meio de recursão:
 *     cada chamada recursiva corresponde a "tentar" um caminho do AFND.
 *
 * Compilação:
 *   gcc -Wall -Wextra -std=c99 -o regex_basico regex_basico.c
 * =============================================================================
 */

#include <stdio.h>

/* -------------------------------------------------------------------------
 * match_aqui  —  tenta casar regex com texto a partir da posição corrente
 *
 * Parâmetros:
 *   regex  — ponteiro para o padrão (expressão regular)
 *   texto  — ponteiro para a cadeia de entrada
 *
 * Retorna 1 se regex casa com o texto inteiro (casamento ancorado ao
 * início e ao fim), 0 caso contrário.
 *
 * A lógica segue diretamente as regras de derivação de expressões regulares:
 *   - Se regex está vazio, o casamento é bem-sucedido (ε casa com ε).
 *   - Se o próximo operador é '*', tratamos o fecho de Kleene.
 *   - Senão, verificamos se o primeiro caractere casa e avançamos.
 * ------------------------------------------------------------------------- */
static int match_estrela(char c, const char *regex, const char *texto);

static int match_aqui(const char *regex, const char *texto)
{
    /* Caso base: padrão vazio casa se o texto também foi totalmente consumido */
    if (regex[0] == '\0')
        return texto[0] == '\0';

    /*
     * Fecho de Kleene (c* ou .*)
     * Quando regex[1] == '*', delegamos para match_estrela, que tenta
     * zero ou mais repetições do caractere/curinga regex[0].
     * Isso corresponde à regra:  L(r*) = {ε} ∪ L(r)·L(r*)
     */
    if (regex[1] == '*')
        return match_estrela(regex[0], regex + 2, texto);

    /*
     * Casamento de um caractere:
     *   - regex[0] == '.' casa com qualquer caractere (exceto fim da cadeia)
     *   - regex[0] == texto[0] casa literalmente
     * Após casar, avançamos ambos os ponteiros (concatenação).
     */
    if (texto[0] != '\0' && (regex[0] == '.' || regex[0] == texto[0]))
        return match_aqui(regex + 1, texto + 1);

    /* Nenhuma regra se aplicou — casamento falhou */
    return 0;
}

/* -------------------------------------------------------------------------
 * match_estrela  —  trata o operador '*' (fecho de Kleene)
 *
 * Parâmetros:
 *   c      — o caractere (ou '.') que pode se repetir
 *   regex  — restante do padrão após 'c*'
 *   texto  — cadeia de entrada na posição corrente
 *
 * Estratégia: tenta casar o restante do padrão com zero, uma, duas, ...
 * repetições de c.  Isso é equivalente a explorar todos os caminhos do
 * AFND gerado pela construção de Thompson para r*.
 * ------------------------------------------------------------------------- */
static int match_estrela(char c, const char *regex, const char *texto)
{
    /*
     * Laço: a cada iteração, tentamos casar o restante do padrão (regex)
     * com a posição corrente de texto.  Se falhar, consumimos mais um
     * caractere que casa com c e tentamos novamente.
     *
     * A primeira iteração corresponde a zero repetições (ε ∈ L(c*)).
     */
    const char *p = texto;
    for (;;) {
        if (match_aqui(regex, p))
            return 1;

        /* Se chegamos ao fim da cadeia ou o próximo caractere não casa, paramos. */
        if (*p == '\0' || (c != '.' && *p != c))
            break;

        /* Avança explicitamente para tentar mais uma repetição de c. */
        p++;
    }
    return 0;
}

/* -------------------------------------------------------------------------
 * match  —  interface principal: verifica se regex casa com texto inteiro
 *
 * A expressão regular é ancorada: deve casar a cadeia do início ao fim.
 * Isso equivale a verificar se texto ∈ L(regex).
 * ------------------------------------------------------------------------- */
static int match(const char *regex, const char *texto)
{
    return match_aqui(regex, texto);
}

/* -------------------------------------------------------------------------
 * Funções auxiliares de teste
 * ------------------------------------------------------------------------- */

/* Executa um caso de teste e imprime o resultado */
static void executar_teste(const char *regex, const char *texto,
                           int esperado, int *acertos, int *total)
{
    int resultado = match(regex, texto);
    int correto = (resultado == esperado);

    printf("  regex=\"%-6s\"  texto=\"%-8s\"  → %s  (esperado: %s) %s\n",
           regex, texto,
           resultado ? "CASA  " : "NÃO CASA",
           esperado  ? "CASA  " : "NÃO CASA",
           correto   ? "✓" : "✗ FALHA");

    (*total)++;
    if (correto)
        (*acertos)++;
}

/* =========================================================================
 * main  —  demonstração e testes do casador de expressões regulares
 * ========================================================================= */
int main(void)
{
    printf("==========================================================\n");
    printf(" Expressões Regulares — Casamento Básico\n");
    printf(" Operadores: literal, '.' (curinga), '*' (Kleene)\n");
    printf("==========================================================\n\n");

    int acertos = 0;
    int total   = 0;

    /*
     * Grupo 1: fecho de Kleene  —  a*b
     * L(a*b) = { b, ab, aab, aaab, ... }
     * A linguagem regular gerada é a mesma do AFND com transição-ε
     * da construção de Thompson para a*·b.
     */
    printf("--- Teste: regex \"a*b\" ---\n");
    printf("    L(a*b) = { b, ab, aab, aaab, ... }\n\n");

    executar_teste("a*b", "b",    1, &acertos, &total);
    executar_teste("a*b", "ab",   1, &acertos, &total);
    executar_teste("a*b", "aab",  1, &acertos, &total);
    executar_teste("a*b", "ba",   0, &acertos, &total);
    executar_teste("a*b", "abb",  0, &acertos, &total);

    printf("\n");

    /*
     * Grupo 2: curinga  —  a.b
     * L(a.b) = { axb | x ∈ Σ }, onde Σ é qualquer caractere.
     * O '.' corresponde a uma transição que aceita qualquer símbolo
     * do alfabeto — como um AFND com |Σ| transições saindo do estado.
     */
    printf("--- Teste: regex \"a.b\" ---\n");
    printf("    L(a.b) = { axb | x é qualquer caractere }\n\n");

    executar_teste("a.b", "axb",  1, &acertos, &total);
    executar_teste("a.b", "a0b",  1, &acertos, &total);
    executar_teste("a.b", "ab",   0, &acertos, &total);
    executar_teste("a.b", "axxb", 0, &acertos, &total);

    printf("\n");

    /*
     * Grupo 3: curinga + Kleene  —  .*
     * L(.*) = Σ*  (todas as cadeias possíveis)
     * Isso corresponde ao autômato universal que aceita tudo.
     */
    printf("--- Teste: regex \".*\" ---\n");
    printf("    L(.*) = Σ* (toda cadeia)\n\n");

    executar_teste(".*", "",       1, &acertos, &total);
    executar_teste(".*", "abc",    1, &acertos, &total);
    executar_teste(".*", "12345",  1, &acertos, &total);

    printf("\n");

    /*
     * Grupo 4: testes adicionais — combinações
     */
    printf("--- Testes adicionais ---\n\n");

    executar_teste("a*",  "",      1, &acertos, &total);  /* ε ∈ L(a*) */
    executar_teste("a*",  "aaa",   1, &acertos, &total);
    executar_teste("ab",  "ab",    1, &acertos, &total);
    executar_teste("ab",  "abc",   0, &acertos, &total);
    executar_teste("a.*b","axyzb", 1, &acertos, &total);  /* a seguido de qualquer coisa e b */
    executar_teste("a.*b","ab",    1, &acertos, &total);  /* .* pode ser ε */

    printf("\n");

    /* --- Resumo --- */
    printf("==========================================================\n");
    printf(" Resumo: %d/%d testes corretos\n", acertos, total);
    printf("==========================================================\n");

    return 0;
}
