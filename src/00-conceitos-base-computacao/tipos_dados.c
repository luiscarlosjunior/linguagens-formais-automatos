/*
 * Linguagens Formais e Autômatos
 * Capítulo 0 - Conceitos Base da Computação: Tipos de Dados
 *
 * Este programa demonstra os tipos primitivos da linguagem C,
 * sua representação binária interna e os limites de cada tipo.
 * Conceitos abordados:
 *   - Tamanho em bytes de cada tipo (sizeof)
 *   - Intervalo de valores (limits.h / float.h)
 *   - Representação binária de inteiros
 *   - Diferença entre tipos com e sem sinal
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

/* Imprime a representação binária de um unsigned long de n bits */
static void imprimir_binario(unsigned long valor, int nbits) {
    for (int i = nbits - 1; i >= 0; i--) {
        putchar((valor >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 4 == 0)
            putchar(' '); /* separa nibbles para legibilidade */
    }
}

int main(void) {
    printf("=== Tipos de Dados em C ===\n\n");

    /* --- Tamanhos dos tipos --- */
    printf("--- Tamanho em bytes (sizeof) ---\n");
    printf("  char   : %zu byte(s)\n", sizeof(char));
    printf("  short  : %zu byte(s)\n", sizeof(short));
    printf("  int    : %zu byte(s)\n", sizeof(int));
    printf("  long   : %zu byte(s)\n", sizeof(long));
    printf("  float  : %zu byte(s)\n", sizeof(float));
    printf("  double : %zu byte(s)\n", sizeof(double));
    printf("  _Bool  : %zu byte(s)\n", sizeof(_Bool));
    printf("\n");

    /* --- Limites de tipos inteiros --- */
    printf("--- Limites de tipos inteiros ---\n");
    printf("  char   : %d  a  %d\n",  CHAR_MIN,  CHAR_MAX);
    printf("  short  : %d  a  %d\n",  SHRT_MIN,  SHRT_MAX);
    printf("  int    : %d  a  %d\n",   INT_MIN,   INT_MAX);
    printf("  long   : %ld a  %ld\n", LONG_MIN,  LONG_MAX);
    printf("  uchar  : 0   a  %u\n",  UCHAR_MAX);
    printf("  uint   : 0   a  %u\n",  UINT_MAX);
    printf("\n");

    /* --- Limites de ponto flutuante --- */
    printf("--- Limites de ponto flutuante ---\n");
    printf("  float  : %.2e  a  %.2e (%.6g precisao)\n",
           (double)FLT_MIN, (double)FLT_MAX, (double)FLT_EPSILON);
    printf("  double : %.2e  a  %.2e (%.15g precisao)\n",
           DBL_MIN, DBL_MAX, DBL_EPSILON);
    printf("\n");

    /* --- Representação binária de inteiros --- */
    printf("--- Representacao binaria de inteiros (8 bits) ---\n");

    unsigned char exemplos[] = {0, 1, 42, 127, 128, 255};
    int n = (int)(sizeof(exemplos) / sizeof(exemplos[0]));

    printf("  %-8s %-12s %-6s\n", "Decimal", "Binario", "Hex");
    printf("  %-8s %-12s %-6s\n", "-------", "-------", "---");
    for (int i = 0; i < n; i++) {
        printf("  %-8u ", (unsigned)exemplos[i]);
        imprimir_binario(exemplos[i], 8);
        printf("  0x%02X\n", (unsigned)exemplos[i]);
    }
    printf("\n");

    /* --- Complemento de dois --- */
    printf("--- Complemento de dois (interpretacao com sinal, 8 bits) ---\n");

    signed char com_sinal[] = {0, 1, 127, -1, -128};
    int m = (int)(sizeof(com_sinal) / sizeof(com_sinal[0]));

    printf("  %-8s %-12s %-6s\n", "Decimal", "Binario", "Hex");
    printf("  %-8s %-12s %-6s\n", "-------", "-------", "---");
    for (int i = 0; i < m; i++) {
        unsigned char bits = (unsigned char)com_sinal[i];
        printf("  %-8d ", (int)com_sinal[i]);
        imprimir_binario(bits, 8);
        printf("  0x%02X\n", (unsigned)bits);
    }
    printf("\n");

    /* --- Tipo booleano --- */
    printf("--- Tipo booleano (_Bool / stdbool.h) ---\n");
    _Bool verdadeiro = 1;
    _Bool falso      = 0;
    printf("  verdadeiro = %d\n", (int)verdadeiro);
    printf("  falso      = %d\n", (int)falso);
    printf("  sizeof(_Bool) = %zu byte(s)\n", sizeof(_Bool));
    printf("\n");

    /* --- Struct como tipo composto --- */
    printf("--- Struct: tipo composto ---\n");

    typedef struct {
        char  simbolo;
        int   codigo_ascii;
        _Bool e_letra;
    } InfoChar;

    InfoChar letras[] = {
        {'A', 65, 1},
        {'z', 122, 1},
        {'0', 48, 0},
        {' ', 32, 0}
    };

    printf("  %-8s %-14s %-8s\n", "Simbolo", "Codigo ASCII", "E letra?");
    printf("  %-8s %-14s %-8s\n", "-------", "------------", "--------");
    for (int i = 0; i < 4; i++) {
        printf("  '%c'     %-14d %s\n",
               letras[i].simbolo,
               letras[i].codigo_ascii,
               letras[i].e_letra ? "sim" : "nao");
    }
    printf("\n");

    printf("Observacao: em C, 'A' == 65 (o tipo char e um inteiro pequeno).\n");
    printf("A diferenca 'a' - 'A' = %d (sempre 32 no ASCII).\n", 'a' - 'A');

    return 0;
}
