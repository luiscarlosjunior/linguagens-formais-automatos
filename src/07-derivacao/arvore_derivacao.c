/*
 * Linguagens Formais e Autômatos
 *
 * Árvore de Derivação para Gramática Livre de Contexto
 *
 * Gramática:
 *   S → aSb | ab
 *
 * Gera a linguagem L = { a^n b^n | n >= 1 }
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILHOS 4

/* ==================== Nó da Árvore ======================= */

typedef struct No {
    char simbolo[16];           /* símbolo gramatical ou terminal */
    struct No *filhos[MAX_FILHOS];
    int num_filhos;
} No;

/* Cria um novo nó com o símbolo dado */
No *criar_no(const char *simbolo)
{
    No *no = (No *)malloc(sizeof(No));
    if (!no) {
        fprintf(stderr, "Erro: falha ao alocar memória.\n");
        exit(1);
    }
    strncpy(no->simbolo, simbolo, sizeof(no->simbolo) - 1);
    no->simbolo[sizeof(no->simbolo) - 1] = '\0';
    no->num_filhos = 0;
    return no;
}

/* Adiciona um filho ao nó pai */
void adicionar_filho(No *pai, No *filho)
{
    if (pai->num_filhos >= MAX_FILHOS) {
        fprintf(stderr, "Erro: número máximo de filhos excedido.\n");
        return;
    }
    pai->filhos[pai->num_filhos++] = filho;
}

/* Imprime a árvore com indentação para visualizar a estrutura */
void imprimir_arvore(No *no, int nivel)
{
    int i;
    if (!no)
        return;

    /* Indentação com linhas verticais */
    for (i = 0; i < nivel; i++) {
        if (i == nivel - 1)
            printf("├── ");
        else
            printf("│   ");
    }
    printf("%s\n", no->simbolo);

    for (i = 0; i < no->num_filhos; i++)
        imprimir_arvore(no->filhos[i], nivel + 1);
}

/* Imprime a fronteira (yield) da árvore — os terminais da esquerda para a direita */
void imprimir_derivacao(No *no)
{
    int i;
    if (!no)
        return;

    /* Se é folha (terminal), imprime o símbolo */
    if (no->num_filhos == 0) {
        printf("%s", no->simbolo);
        return;
    }

    /* Percorre os filhos recursivamente */
    for (i = 0; i < no->num_filhos; i++)
        imprimir_derivacao(no->filhos[i]);
}

/* Libera toda a memória da árvore */
void liberar_arvore(No *no)
{
    int i;
    if (!no)
        return;

    for (i = 0; i < no->num_filhos; i++)
        liberar_arvore(no->filhos[i]);

    free(no);
}

/* ============== Construção das Árvores =================== */

/*
 * Constrói a árvore para "ab":
 *   S → ab
 *
 *   S
 *   ├── a
 *   └── b
 */
No *construir_ab(void)
{
    No *s = criar_no("S");
    adicionar_filho(s, criar_no("a"));
    adicionar_filho(s, criar_no("b"));
    return s;
}

/*
 * Constrói a árvore para "aabb":
 *   S → aSb → a(ab)b
 *
 *   S
 *   ├── a
 *   ├── S
 *   │   ├── a
 *   │   └── b
 *   └── b
 */
No *construir_aabb(void)
{
    No *s = criar_no("S");
    No *s_interno = criar_no("S");

    adicionar_filho(s_interno, criar_no("a"));
    adicionar_filho(s_interno, criar_no("b"));

    adicionar_filho(s, criar_no("a"));
    adicionar_filho(s, s_interno);
    adicionar_filho(s, criar_no("b"));

    return s;
}

/*
 * Constrói a árvore para "aaabbb":
 *   S → aSb → a(aSb)b → a(a(ab)b)b
 *
 *   S
 *   ├── a
 *   ├── S
 *   │   ├── a
 *   │   ├── S
 *   │   │   ├── a
 *   │   │   └── b
 *   │   └── b
 *   └── b
 */
No *construir_aaabbb(void)
{
    No *s = criar_no("S");
    No *s_medio = criar_no("S");
    No *s_interno = criar_no("S");

    /* Nível mais interno: S → ab */
    adicionar_filho(s_interno, criar_no("a"));
    adicionar_filho(s_interno, criar_no("b"));

    /* Nível médio: S → aSb */
    adicionar_filho(s_medio, criar_no("a"));
    adicionar_filho(s_medio, s_interno);
    adicionar_filho(s_medio, criar_no("b"));

    /* Nível externo: S → aSb */
    adicionar_filho(s, criar_no("a"));
    adicionar_filho(s, s_medio);
    adicionar_filho(s, criar_no("b"));

    return s;
}

/* Imprime a sequência de derivação mais à esquerda para a^n b^n */
void imprimir_sequencia_derivacao(int n)
{
    int i;

    printf("  Derivação mais à esquerda:\n  ");
    printf("S");

    /* Passos S → aSb (n-1 vezes) */
    for (i = 1; i < n; i++) {
        int j;
        printf(" ⇒ ");
        for (j = 0; j < i; j++)
            printf("a");
        printf("S");
        for (j = 0; j < i; j++)
            printf("b");
    }

    /* Último passo: S → ab */
    printf(" ⇒ ");
    for (i = 0; i < n; i++)
        printf("a");
    for (i = 0; i < n; i++)
        printf("b");

    printf("\n");
}

/* ========================= Main ========================== */

int main(void)
{
    No *arvore;

    printf("============================================\n");
    printf(" Árvore de Derivação\n");
    printf(" Gramática: S → aSb | ab\n");
    printf(" L = { a^n b^n | n >= 1 }\n");
    printf("============================================\n\n");

    /* ---------- Derivação de "ab" (n=1) ---------- */
    printf("--------------------------------------------\n");
    printf(" Palavra: \"ab\" (n=1)\n");
    printf("--------------------------------------------\n");
    printf("  Produção usada: S → ab\n\n");

    arvore = construir_ab();

    printf("  Árvore de derivação:\n");
    imprimir_arvore(arvore, 0);
    printf("\n");

    printf("  Fronteira (yield): ");
    imprimir_derivacao(arvore);
    printf("\n\n");

    imprimir_sequencia_derivacao(1);
    printf("\n");

    liberar_arvore(arvore);

    /* ---------- Derivação de "aabb" (n=2) ---------- */
    printf("--------------------------------------------\n");
    printf(" Palavra: \"aabb\" (n=2)\n");
    printf("--------------------------------------------\n");
    printf("  Produções usadas: S → aSb, S → ab\n\n");

    arvore = construir_aabb();

    printf("  Árvore de derivação:\n");
    imprimir_arvore(arvore, 0);
    printf("\n");

    printf("  Fronteira (yield): ");
    imprimir_derivacao(arvore);
    printf("\n\n");

    imprimir_sequencia_derivacao(2);
    printf("\n");

    liberar_arvore(arvore);

    /* ---------- Derivação de "aaabbb" (n=3) ---------- */
    printf("--------------------------------------------\n");
    printf(" Palavra: \"aaabbb\" (n=3)\n");
    printf("--------------------------------------------\n");
    printf("  Produções usadas: S → aSb, S → aSb, S → ab\n\n");

    arvore = construir_aaabbb();

    printf("  Árvore de derivação:\n");
    imprimir_arvore(arvore, 0);
    printf("\n");

    printf("  Fronteira (yield): ");
    imprimir_derivacao(arvore);
    printf("\n\n");

    imprimir_sequencia_derivacao(3);
    printf("\n");

    liberar_arvore(arvore);

    return 0;
}
