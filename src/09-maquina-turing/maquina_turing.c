/*
 * Linguagens Formais e Autômatos
 *
 * Máquina de Turing — Reconhecedor de a^n b^n
 * Simula uma Máquina de Turing que reconhece L = { a^n b^n | n >= 1 }
 *
 * Definição formal:
 *   M = (Q, Σ, Γ, δ, q0, q_aceita, q_rejeita)
 *   Q = {q0, q1, q2, q3, q_aceita, q_rejeita}
 *   Σ = {a, b}
 *   Γ = {a, b, X, Y, _}
 *   q0 = estado inicial
 *   q_aceita = estado de aceitação
 *   q_rejeita = estado de rejeição
 *
 * Algoritmo de marcação:
 *   1. Em q0, encontra 'a' mais à esquerda, marca como 'X', vai para q1.
 *   2. Em q1, move à direita até encontrar 'b', marca como 'Y', vai para q2.
 *   3. Em q2, move à esquerda até encontrar 'X', vai para q0.
 *   4. Em q0, se encontra 'Y', avança por todos os 'Y's em q3.
 *   5. Em q3, se encontra '_', aceita.
 */

#include <stdio.h>
#include <string.h>

#define TAM_FITA   256
#define MAX_PASSOS 1000
#define BRANCO     '_'

/* ==================== Estados da MT ====================== */

typedef enum {
    Q0,          /* busca próximo 'a' não marcado           */
    Q1,          /* move à direita buscando 'b'             */
    Q2,          /* move à esquerda voltando ao início       */
    Q3,          /* verifica se restam apenas 'Y's e branco */
    Q_ACEITA,
    Q_REJEITA
} Estado;

/* Retorna o nome textual do estado */
static const char *nome_estado(Estado e)
{
    switch (e) {
        case Q0:        return "q0";
        case Q1:        return "q1";
        case Q2:        return "q2";
        case Q3:        return "q3";
        case Q_ACEITA:  return "q_aceita";
        case Q_REJEITA: return "q_rejeita";
    }
    return "??";
}

/* ===================== Fita da MT ======================== */

typedef struct {
    char celulas[TAM_FITA];
    int cabeca;    /* posição do cabeçote de leitura/escrita */
    int tamanho;   /* comprimento útil da fita              */
} Fita;

/* Inicializa a fita com a palavra, preenchendo o resto com branco */
static void fita_inicializar(Fita *f, const char *palavra)
{
    int tam = (int)strlen(palavra);
    int i;
    if (tam >= TAM_FITA - 1) {
        fprintf(stderr, "Aviso: entrada truncada para %d caracteres.\n", TAM_FITA - 2);
        tam = TAM_FITA - 2;
    }
    memcpy(f->celulas, palavra, tam);
    f->celulas[tam] = BRANCO;
    for (i = tam + 1; i < TAM_FITA; i++)
        f->celulas[i] = BRANCO;
    f->tamanho = tam + 1;
    f->cabeca = 0;
}

/* Imprime a fita com o cabeçote indicado por colchetes */
static void fita_imprimir(const Fita *f, int limite)
{
    int i;
    for (i = 0; i < limite; i++) {
        if (i == f->cabeca)
            printf("[%c]", f->celulas[i]);
        else
            printf(" %c ", f->celulas[i]);
    }
}

/* ============ Função de Transição da MT ================== */

/*
 * Tabela de transições δ(estado, símbolo) → (novo_estado, escrita, direção)
 *   D = direita (+1), E = esquerda (-1)
 *
 *   δ(q0, a) = (q1, X, D)   — marca 'a' como X, busca 'b'
 *   δ(q0, Y) = (q3, Y, D)   — todos os 'a's marcados, verifica
 *   δ(q0, _) = (q_rejeita)  — fita vazia
 *
 *   δ(q1, a) = (q1, a, D)   — pula 'a's não marcados
 *   δ(q1, Y) = (q1, Y, D)   — pula 'Y's já marcados
 *   δ(q1, b) = (q2, Y, E)   — marca 'b' como Y, volta
 *
 *   δ(q2, a) = (q2, a, E)   — volta por 'a's
 *   δ(q2, Y) = (q2, Y, E)   — volta por 'Y's
 *   δ(q2, X) = (q0, X, D)   — encontrou último X, reinicia
 *
 *   δ(q3, Y) = (q3, Y, D)   — pula 'Y's restantes
 *   δ(q3, _) = (q_aceita)   — tudo marcado → aceita
 */

/* Simula um passo da MT. Retorna 1 se a máquina ainda está executando. */
static int mt_passo(Fita *f, Estado *estado)
{
    char simbolo = f->celulas[f->cabeca];

    switch (*estado) {
    case Q0:
        if (simbolo == 'a') {
            f->celulas[f->cabeca] = 'X';
            f->cabeca++;
            *estado = Q1;
        } else if (simbolo == 'Y') {
            f->cabeca++;
            *estado = Q3;
        } else {
            *estado = Q_REJEITA;
        }
        break;

    case Q1:
        if (simbolo == 'a' || simbolo == 'Y') {
            f->cabeca++;
        } else if (simbolo == 'b') {
            f->celulas[f->cabeca] = 'Y';
            f->cabeca--;
            *estado = Q2;
        } else {
            *estado = Q_REJEITA;
        }
        break;

    case Q2:
        if (simbolo == 'a' || simbolo == 'Y') {
            f->cabeca--;
        } else if (simbolo == 'X') {
            f->cabeca++;
            *estado = Q0;
        } else {
            *estado = Q_REJEITA;
        }
        break;

    case Q3:
        if (simbolo == 'Y') {
            f->cabeca++;
        } else if (simbolo == BRANCO) {
            *estado = Q_ACEITA;
        } else {
            *estado = Q_REJEITA;
        }
        break;

    case Q_ACEITA:
    case Q_REJEITA:
        return 0;
    }

    return (*estado != Q_ACEITA && *estado != Q_REJEITA);
}

/* ============= Simulação Completa da MT ================== */

/*
 * Simula a MT sobre a palavra de entrada.
 * Retorna 1 se aceita, 0 se rejeita.
 */
static int mt_simular(const char *palavra)
{
    Fita fita;
    Estado estado = Q0;
    int passo = 0;
    int limite;

    /* Palavra vazia é rejeitada */
    if (strlen(palavra) == 0) {
        printf("    (palavra vazia → rejeita imediatamente)\n");
        return 0;
    }

    fita_inicializar(&fita, palavra);
    limite = fita.tamanho;

    printf("    Passo  Estado      Fita\n");
    printf("    -----  ----------  ");
    {
        int k;
        for (k = 0; k < limite * 3; k++)
            printf("-");
    }
    printf("\n");

    /* Imprime configuração inicial */
    printf("    %3d    %-10s  ", passo, nome_estado(estado));
    fita_imprimir(&fita, limite);
    printf("\n");

    while (estado != Q_ACEITA && estado != Q_REJEITA && passo < MAX_PASSOS) {
        mt_passo(&fita, &estado);
        passo++;
        printf("    %3d    %-10s  ", passo, nome_estado(estado));
        fita_imprimir(&fita, limite);
        printf("\n");
    }

    if (passo >= MAX_PASSOS && estado != Q_ACEITA && estado != Q_REJEITA) {
        printf("    (limite de %d passos atingido — resultado inconclusivo)\n", MAX_PASSOS);
        return -1;  /* inconclusivo */
    }

    return (estado == Q_ACEITA) ? 1 : 0;
}

/* ================= Tabela de Transições ================== */

static void imprimir_tabela_transicoes(void)
{
    printf("Tabela de transições δ(estado, símbolo) → (estado, escrita, dir):\n\n");
    printf("    Estado  Símbolo  →  Novo Estado  Escrita  Direção\n");
    printf("    ------  -------     -----------  -------  -------\n");
    printf("    q0      a        →  q1           X        D\n");
    printf("    q0      Y        →  q3           Y        D\n");
    printf("    q0      outro    →  q_rejeita    —        —\n");
    printf("    q1      a        →  q1           a        D\n");
    printf("    q1      Y        →  q1           Y        D\n");
    printf("    q1      b        →  q2           Y        E\n");
    printf("    q1      outro    →  q_rejeita    —        —\n");
    printf("    q2      a        →  q2           a        E\n");
    printf("    q2      Y        →  q2           Y        E\n");
    printf("    q2      X        →  q0           X        D\n");
    printf("    q2      outro    →  q_rejeita    —        —\n");
    printf("    q3      Y        →  q3           Y        D\n");
    printf("    q3      _        →  q_aceita     —        —\n");
    printf("    q3      outro    →  q_rejeita    —        —\n");
    printf("\n");
}

/* ========================= Main ========================== */

int main(void)
{
    const char *testes[] = {
        "ab", "aabb", "aaabbb",
        "aab", "abb", "ba", "", "aabbb"
    };
    int n_testes = (int)(sizeof(testes) / sizeof(testes[0]));
    int i;

    printf("================================================\n");
    printf(" Máquina de Turing\n");
    printf(" L = { a^n b^n | n >= 1 }\n");
    printf("================================================\n\n");

    printf("Definição formal:\n");
    printf("  M = (Q, Σ, Γ, δ, q0, q_aceita, q_rejeita)\n");
    printf("  Q = {q0, q1, q2, q3, q_aceita, q_rejeita}\n");
    printf("  Σ = {a, b}\n");
    printf("  Γ = {a, b, X, Y, _}\n");
    printf("  q0 = estado inicial\n");
    printf("  q_aceita = estado de aceitação\n");
    printf("  q_rejeita = estado de rejeição\n\n");

    imprimir_tabela_transicoes();

    printf("Algoritmo de marcação na fita:\n");
    printf("  1. Encontra 'a' não marcado, marca como X\n");
    printf("  2. Move à direita, encontra 'b' não marcado, marca como Y\n");
    printf("  3. Move à esquerda até encontrar X, reinicia\n");
    printf("  4. Quando só restam X's e Y's, verifica e aceita\n\n");

    printf("------------------------------------------------\n");
    printf(" Testando palavras\n");
    printf("------------------------------------------------\n\n");

    for (i = 0; i < n_testes; i++) {
        int resultado;

        if (strlen(testes[i]) == 0)
            printf("Palavra: ε (vazia)\n");
        else
            printf("Palavra: \"%s\"\n", testes[i]);

        resultado = mt_simular(testes[i]);
        if (resultado == 1)
            printf("  Resultado: ACEITA ✓\n\n");
        else if (resultado == -1)
            printf("  Resultado: INCONCLUSIVO ?\n\n");
        else
            printf("  Resultado: REJEITA ✗\n\n");
    }

    return 0;
}
