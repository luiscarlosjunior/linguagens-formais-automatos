/*
 * Linguagens Formais e Autômatos
 * Capítulo 1 - Conceitos Matemáticos: Operações com Conjuntos
 *
 * Este programa demonstra as operações fundamentais da teoria dos conjuntos
 * utilizadas no estudo de linguagens formais e autômatos:
 *   - União (A ∪ B)
 *   - Interseção (A ∩ B)
 *   - Diferença (A - B)
 *   - Complemento (Ā relativo a um conjunto universal U)
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX 100

/* Estrutura que representa um conjunto de inteiros */
typedef struct {
    int elementos[MAX];
    int tamanho;
} Conjunto;

/* Verifica se um elemento pertence ao conjunto */
bool pertence(Conjunto *c, int elem) {
    for (int i = 0; i < c->tamanho; i++) {
        if (c->elementos[i] == elem)
            return true;
    }
    return false;
}

/* Adiciona um elemento ao conjunto (sem duplicatas) */
void adicionar(Conjunto *c, int elem) {
    /* Não adiciona se o elemento já pertence ao conjunto */
    if (pertence(c, elem))
        return;

    /* Verifica capacidade antes de escrever no array */
    if (c->tamanho >= MAX) {
        fprintf(stderr,
                "Erro: conjunto atingiu a capacidade máxima (%d elementos). "
                "Elemento %d não foi adicionado.\n",
                MAX, elem);
        return;
    }

    c->elementos[c->tamanho] = elem;
    c->tamanho++;
}

/* Imprime os elementos do conjunto no formato {e1, e2, ...} */
void imprimir(const char *nome, Conjunto *c) {
    printf("%s = {", nome);
    for (int i = 0; i < c->tamanho; i++) {
        printf("%d", c->elementos[i]);
        if (i < c->tamanho - 1)
            printf(", ");
    }
    printf("}\n");
}

/*
 * União: A ∪ B = {x | x ∈ A ou x ∈ B}
 * Contém todos os elementos que pertencem a A ou a B (ou a ambos).
 */
Conjunto uniao(Conjunto *a, Conjunto *b) {
    Conjunto resultado = {.tamanho = 0};
    for (int i = 0; i < a->tamanho; i++)
        adicionar(&resultado, a->elementos[i]);
    for (int i = 0; i < b->tamanho; i++)
        adicionar(&resultado, b->elementos[i]);
    return resultado;
}

/*
 * Interseção: A ∩ B = {x | x ∈ A e x ∈ B}
 * Contém apenas os elementos que pertencem a ambos os conjuntos.
 */
Conjunto intersecao(Conjunto *a, Conjunto *b) {
    Conjunto resultado = {.tamanho = 0};
    for (int i = 0; i < a->tamanho; i++) {
        if (pertence(b, a->elementos[i]))
            adicionar(&resultado, a->elementos[i]);
    }
    return resultado;
}

/*
 * Diferença: A - B = {x | x ∈ A e x ∉ B}
 * Contém os elementos que pertencem a A mas não pertencem a B.
 */
Conjunto diferenca(Conjunto *a, Conjunto *b) {
    Conjunto resultado = {.tamanho = 0};
    for (int i = 0; i < a->tamanho; i++) {
        if (!pertence(b, a->elementos[i]))
            adicionar(&resultado, a->elementos[i]);
    }
    return resultado;
}

/*
 * Complemento: Ā = U - A = {x | x ∈ U e x ∉ A}
 * Contém todos os elementos do conjunto universal U que não pertencem a A.
 */
Conjunto complemento(Conjunto *a, Conjunto *universo) {
    return diferenca(universo, a);
}

int main(void) {
    printf("=== Operações com Conjuntos ===\n\n");

    /* Definição dos conjuntos A e B */
    Conjunto A = {.elementos = {1, 2, 3, 4}, .tamanho = 4};
    Conjunto B = {.elementos = {3, 4, 5, 6}, .tamanho = 4};

    /* Conjunto universal U = {1, 2, 3, 4, 5, 6, 7, 8} */
    Conjunto U = {.elementos = {1, 2, 3, 4, 5, 6, 7, 8}, .tamanho = 8};

    imprimir("A", &A);
    imprimir("B", &B);
    imprimir("U", &U);
    printf("\n");

    /* União: A ∪ B */
    Conjunto uni = uniao(&A, &B);
    imprimir("A ∪ B", &uni);

    /* Interseção: A ∩ B */
    Conjunto inter = intersecao(&A, &B);
    imprimir("A ∩ B", &inter);

    /* Diferença: A - B */
    Conjunto dif_ab = diferenca(&A, &B);
    imprimir("A - B", &dif_ab);

    /* Diferença: B - A */
    Conjunto dif_ba = diferenca(&B, &A);
    imprimir("B - A", &dif_ba);

    /* Complemento de A em relação a U */
    Conjunto comp_a = complemento(&A, &U);
    imprimir("Complemento de A", &comp_a);

    /* Complemento de B em relação a U */
    Conjunto comp_b = complemento(&B, &U);
    imprimir("Complemento de B", &comp_b);

    return 0;
}
