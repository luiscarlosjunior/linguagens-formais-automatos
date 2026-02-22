/*
 * Linguagens Formais e Autômatos
 * Capítulo 0 - Conceitos Base da Computação: Representação Binária
 *
 * Este programa demonstra a representação de informação em sistemas
 * de numeração utilizados em computação:
 *   - Conversão decimal ↔ binário (inteiros sem sinal)
 *   - Conversão decimal ↔ hexadecimal
 *   - Operações bit a bit (AND, OR, XOR, NOT, deslocamentos)
 *   - Uso de máscaras de bits
 */

#include <stdio.h>

#define BITS 16  /* trabalharemos com inteiros de 16 bits nos exemplos */

/* Imprime os 'nbits' menos significativos de 'valor' em binário,
 * separando nibbles com espaço para facilitar a leitura.            */
static void imprimir_binario(unsigned int valor, int nbits) {
    for (int i = nbits - 1; i >= 0; i--) {
        putchar((valor >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 4 == 0)
            putchar(' ');
    }
}

int main(void) {
    printf("=== Representacao Binaria e Sistemas de Numeracao ===\n\n");

    /* --- Conversão decimal → binário --- */
    printf("--- Conversao decimal -> binario ---\n");

    unsigned int decimais[] = {0, 1, 7, 8, 10, 42, 100, 255, 1000};
    int nd = (int)(sizeof(decimais) / sizeof(decimais[0]));

    printf("  %-8s  %-20s  %-6s\n", "Decimal", "Binario (16 bits)", "Hex");
    printf("  %-8s  %-20s  %-6s\n", "-------", "-----------------", "---");
    for (int i = 0; i < nd; i++) {
        printf("  %-8u  ", decimais[i]);
        imprimir_binario(decimais[i], BITS);
        printf("  0x%04X\n", decimais[i]);
    }
    printf("\n");

    /* --- Conversão binário → decimal (ilustração manual) --- */
    printf("--- Conversao binario -> decimal (pesos posicionais) ---\n");

    /* 1011 0101 = 181 */
    unsigned int b = 0xB5;  /* 1011 0101 */
    printf("  Numero binario: ");
    imprimir_binario(b, 8);
    printf("\n");
    printf("  Calculo: 1×128 + 0×64 + 1×32 + 1×16 + 0×8 + 1×4 + 0×2 + 1×1\n");
    printf("         = 128 + 32 + 16 + 4 + 1 = %u\n\n", b);

    /* --- Operações bit a bit --- */
    printf("--- Operacoes bit a bit ---\n");

    unsigned int A = 0b10110100;  /* 180 */
    unsigned int B = 0b01101110;  /* 110 */

    printf("  A         = ");
    imprimir_binario(A, 8);
    printf("  (%u)\n", A);

    printf("  B         = ");
    imprimir_binario(B, 8);
    printf("  (%u)\n\n", B);

    printf("  A AND B   = ");
    imprimir_binario(A & B, 8);
    printf("  (%u)  [1 onde ambos sao 1]\n", A & B);

    printf("  A OR  B   = ");
    imprimir_binario(A | B, 8);
    printf("  (%u)  [1 onde ao menos um e 1]\n", A | B);

    printf("  A XOR B   = ");
    imprimir_binario(A ^ B, 8);
    printf("  (%u)  [1 onde sao diferentes]\n", A ^ B);

    printf("  NOT A     = ");
    imprimir_binario((~A) & 0xFF, 8);
    printf("  (%u)  [inverte todos os bits (8 bits)]\n\n", (~A) & 0xFF);

    /* --- Deslocamentos --- */
    printf("--- Deslocamentos (shift) ---\n");

    unsigned int x = 0b00001010;  /* 10 */
    printf("  x          = ");
    imprimir_binario(x, 8);
    printf("  (%u)\n", x);

    printf("  x << 1     = ");
    imprimir_binario(x << 1, 8);
    printf("  (%u)  [multiplica por 2]\n", x << 1);

    printf("  x << 2     = ");
    imprimir_binario(x << 2, 8);
    printf("  (%u)  [multiplica por 4]\n", x << 2);

    printf("  x >> 1     = ");
    imprimir_binario(x >> 1, 8);
    printf("  (%u)  [divide por 2 (parte inteira)]\n\n", x >> 1);

    /* --- Máscaras de bits --- */
    printf("--- Mascaras de bits ---\n");

    unsigned int flags = 0b10110010;  /* byte de "flags" de estado */

    /* Verificar se o bit n está ativo: (flags >> n) & 1 */
    printf("  flags = ");
    imprimir_binario(flags, 8);
    printf("  (0x%02X)\n\n", flags);

    for (int bit = 7; bit >= 0; bit--) {
        int ativo = (flags >> bit) & 1;
        printf("  Bit %d: %s\n", bit, ativo ? "ATIVO  (1)" : "inativo (0)");
    }
    printf("\n");

    /* Ligar o bit 0 (OR com máscara)  */
    unsigned int ligar_bit0 = flags | (1u << 0);
    printf("  Ligar bit 0  (OR  com 0x01): ");
    imprimir_binario(ligar_bit0, 8);
    printf("  (0x%02X)\n", ligar_bit0);

    /* Desligar o bit 7 (AND com NOT da máscara) */
    unsigned int desligar_bit7 = flags & ~(1u << 7);
    printf("  Desligar bit7 (AND com ~0x80): ");
    imprimir_binario(desligar_bit7, 8);
    printf("  (0x%02X)\n", desligar_bit7);

    /* Alternar o bit 1 (XOR com máscara) */
    unsigned int alternar_bit1 = flags ^ (1u << 1);
    printf("  Alternar bit1 (XOR com 0x02): ");
    imprimir_binario(alternar_bit1, 8);
    printf("  (0x%02X)\n\n", alternar_bit1);

    /* --- Codificação ASCII --- */
    printf("--- Codificacao ASCII ---\n");

    char texto[] = "Ola!";
    printf("  String: \"%s\"\n", texto);
    printf("  %-8s %-8s %-20s %-6s\n", "Char", "Decimal", "Binario (8 bits)", "Hex");
    printf("  %-8s %-8s %-20s %-6s\n", "----", "-------", "---------------", "---");
    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char c = (unsigned char)texto[i];
        printf("  '%-5c'  %-8u ", (char)c, (unsigned)c);
        imprimir_binario(c, 8);
        printf("  0x%02X\n", (unsigned)c);
    }

    return 0;
}
