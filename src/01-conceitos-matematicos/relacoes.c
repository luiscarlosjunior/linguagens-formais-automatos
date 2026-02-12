/*
 * Linguagens Formais e Autômatos
 * Capítulo 1 - Conceitos Matemáticos: Relações Binárias
 *
 * Este programa demonstra relações binárias e suas propriedades:
 *   - Reflexividade: ∀a ∈ S, (a, a) ∈ R
 *   - Simetria: se (a, b) ∈ R então (b, a) ∈ R
 *   - Transitividade: se (a, b) ∈ R e (b, c) ∈ R então (a, c) ∈ R
 *   - Fecho transitivo via algoritmo de Warshall
 *
 * Exemplo: relação R sobre o conjunto S = {0, 1, 2}
 *          R = {(0,1), (1,2), (0,2)}
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 3  /* Cardinalidade do conjunto S = {0, 1, 2} */

/* Imprime a matriz de relação de forma legível */
void imprimir_matriz(const char *nome, bool R[N][N]) {
    printf("%s:\n", nome);
    printf("    ");
    for (int j = 0; j < N; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("  %d ", i);
        for (int j = 0; j < N; j++)
            printf("%d ", R[i][j] ? 1 : 0);
        printf("\n");
    }
    printf("\n");
}

/* Imprime os pares ordenados da relação */
void imprimir_pares(const char *nome, bool R[N][N]) {
    printf("%s = {", nome);
    bool primeiro = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (R[i][j]) {
                if (!primeiro)
                    printf(", ");
                printf("(%d,%d)", i, j);
                primeiro = false;
            }
        }
    }
    printf("}\n");
}

/*
 * Reflexividade: uma relação R é reflexiva se, para todo elemento a
 * do conjunto, o par (a, a) pertence a R.
 */
bool eh_reflexiva(bool R[N][N]) {
    for (int i = 0; i < N; i++) {
        if (!R[i][i])
            return false;
    }
    return true;
}

/*
 * Simetria: uma relação R é simétrica se, sempre que (a, b) ∈ R,
 * então (b, a) ∈ R também.
 */
bool eh_simetrica(bool R[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (R[i][j] && !R[j][i])
                return false;
        }
    }
    return true;
}

/*
 * Transitividade: uma relação R é transitiva se, sempre que
 * (a, b) ∈ R e (b, c) ∈ R, então (a, c) ∈ R.
 */
bool eh_transitiva(bool R[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (R[i][j]) {
                for (int k = 0; k < N; k++) {
                    if (R[j][k] && !R[i][k])
                        return false;
                }
            }
        }
    }
    return true;
}

/*
 * Fecho transitivo (algoritmo de Warshall):
 * Calcula a menor relação transitiva R+ que contém R.
 * O algoritmo itera por todos os vértices intermediários k e
 * adiciona (i, j) sempre que existem (i, k) e (k, j).
 */
void fecho_transitivo(bool R[N][N], bool resultado[N][N]) {
    /* Copia a relação original para o resultado */
    memcpy(resultado, R, sizeof(bool) * N * N);

    /* Algoritmo de Warshall */
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (resultado[i][k] && resultado[k][j])
                    resultado[i][j] = true;
            }
        }
    }
}

/* Verifica e exibe as propriedades de uma relação */
void verificar_propriedades(const char *nome, bool R[N][N]) {
    printf("Propriedades de %s:\n", nome);
    printf("  Reflexiva:   %s\n", eh_reflexiva(R) ? "Sim" : "Não");
    printf("  Simétrica:   %s\n", eh_simetrica(R) ? "Sim" : "Não");
    printf("  Transitiva:  %s\n", eh_transitiva(R) ? "Sim" : "Não");
    printf("\n");
}

int main(void) {
    printf("=== Relações Binárias e Propriedades ===\n\n");
    printf("Conjunto S = {0, 1, 2}\n\n");

    /*
     * Relação R1 = {(0,1), (1,2), (0,2)}
     * Representada como matriz booleana: R[i][j] = true se (i,j) ∈ R
     */
    bool R1[N][N] = {
        {false, true,  true },  /* 0 -> 1, 0 -> 2 */
        {false, false, true },  /* 1 -> 2           */
        {false, false, false}
    };

    imprimir_pares("R1", R1);
    imprimir_matriz("Matriz de R1", R1);
    verificar_propriedades("R1", R1);

    /* Fecho transitivo de R1 */
    bool R1_fecho[N][N];
    fecho_transitivo(R1, R1_fecho);
    imprimir_pares("R1+ (fecho transitivo)", R1_fecho);
    imprimir_matriz("Matriz de R1+", R1_fecho);

    printf("--- Exemplo adicional ---\n\n");

    /*
     * Relação R2 = {(0,0), (1,1), (2,2), (0,1), (1,0)}
     * Esta relação é reflexiva e simétrica, mas não transitiva?
     * Vamos verificar.
     */
    bool R2[N][N] = {
        {true,  true,  false},
        {true,  true,  false},
        {false, false, true }
    };

    imprimir_pares("R2", R2);
    imprimir_matriz("Matriz de R2", R2);
    verificar_propriedades("R2", R2);

    return 0;
}
