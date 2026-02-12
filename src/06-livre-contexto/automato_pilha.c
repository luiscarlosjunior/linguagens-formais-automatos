/*
 * Linguagens Formais e Autômatos
 *
 * Autômato com Pilha (AP) - Pushdown Automaton
 * Reconhece a linguagem L = { a^n b^n | n >= 1 }
 *
 * Definição formal:
 *   M = (Q, Σ, Γ, δ, q0, Z0, F)
 *   Q  = {q0, q1, q2}
 *   Σ  = {a, b}
 *   Γ  = {A, Z}
 *   q0 = estado inicial
 *   Z0 = Z (símbolo inicial da pilha)
 *   F  = {q2}
 *
 * Transições:
 *   δ(q0, a, Z) = {(q0, AZ)}
 *   δ(q0, a, A) = {(q0, AA)}
 *   δ(q0, b, A) = {(q1, ε)}
 *   δ(q1, b, A) = {(q1, ε)}
 *   δ(q1, ε, Z) = {(q2, Z)}
 */

#include <stdio.h>
#include <string.h>

#define TAM_PILHA 256

/* ========================= Pilha ========================= */

typedef struct {
    char dados[TAM_PILHA];
    int topo;
} Pilha;

/* Inicializa a pilha vazia */
void pilha_inicializar(Pilha *p)
{
    p->topo = -1;
}

/* Verifica se a pilha está vazia */
int pilha_vazia(const Pilha *p)
{
    return p->topo == -1;
}

/* Empilha um caractere */
int pilha_push(Pilha *p, char c)
{
    if (p->topo >= TAM_PILHA - 1)
        return 0;
    p->dados[++(p->topo)] = c;
    return 1;
}

/* Desempilha e retorna o caractere do topo */
int pilha_pop(Pilha *p, char *c)
{
    if (pilha_vazia(p))
        return 0;
    *c = p->dados[(p->topo)--];
    return 1;
}

/* Retorna o caractere do topo sem desempilhar */
int pilha_topo(const Pilha *p, char *c)
{
    if (pilha_vazia(p))
        return 0;
    *c = p->dados[p->topo];
    return 1;
}

/* Imprime o conteúdo da pilha (base → topo) */
void pilha_imprimir(const Pilha *p)
{
    int i;
    for (i = 0; i <= p->topo; i++)
        printf("%c", p->dados[i]);
    if (pilha_vazia(p))
        printf("(vazia)");
}

/* ================== Autômato com Pilha =================== */

typedef enum { Q0, Q1, Q2 } Estado;

static const char *nome_estado(Estado e)
{
    switch (e) {
    case Q0: return "q0";
    case Q1: return "q1";
    case Q2: return "q2";
    }
    return "??";
}

/* Imprime a configuração instantânea do AP */
static void imprimir_config(Estado estado, const char *entrada, int pos,
                            const Pilha *pilha)
{
    printf("  (%s, ", nome_estado(estado));
    if (entrada[pos] == '\0')
        printf("ε");
    else
        printf("%s", entrada + pos);
    printf(", ");
    pilha_imprimir(pilha);
    printf(")\n");
}

/*
 * Simula o Autômato com Pilha sobre a palavra de entrada.
 * Retorna 1 se aceita, 0 se rejeita.
 */
int ap_aceita(const char *palavra)
{
    Pilha pilha;
    Estado estado = Q0;
    int pos = 0;
    int tam = (int)strlen(palavra);
    char topo_char;

    pilha_inicializar(&pilha);
    pilha_push(&pilha, 'Z'); /* símbolo inicial da pilha */

    printf("  Configurações:\n");
    imprimir_config(estado, palavra, pos, &pilha);

    /* Rejeita palavra vazia */
    if (tam == 0)
        return 0;

    while (pos < tam) {
        char simbolo = palavra[pos];

        if (!pilha_topo(&pilha, &topo_char))
            return 0; /* pilha vazia inesperadamente */

        if (estado == Q0 && simbolo == 'a') {
            /* δ(q0, a, Z) = {(q0, AZ)} e δ(q0, a, A) = {(q0, AA)} */
            if (topo_char == 'Z' || topo_char == 'A') {
                pilha_push(&pilha, 'A');
                pos++;
                imprimir_config(estado, palavra, pos, &pilha);
                continue;
            }
            return 0;
        }

        if (estado == Q0 && simbolo == 'b') {
            /* δ(q0, b, A) = {(q1, ε)} */
            if (topo_char == 'A') {
                pilha_pop(&pilha, &topo_char);
                estado = Q1;
                pos++;
                imprimir_config(estado, palavra, pos, &pilha);
                continue;
            }
            return 0;
        }

        if (estado == Q1 && simbolo == 'b') {
            /* δ(q1, b, A) = {(q1, ε)} */
            if (topo_char == 'A') {
                pilha_pop(&pilha, &topo_char);
                pos++;
                imprimir_config(estado, palavra, pos, &pilha);
                continue;
            }
            return 0;
        }

        /* Nenhuma transição válida */
        return 0;
    }

    /* Transição-ε: δ(q1, ε, Z) = {(q2, Z)} */
    if (estado == Q1 && pilha_topo(&pilha, &topo_char) && topo_char == 'Z') {
        estado = Q2;
        imprimir_config(estado, palavra, pos, &pilha);
    }

    return estado == Q2;
}

/* ========================= Main ========================== */

int main(void)
{
    const char *testes[] = {"ab", "aabb", "aaabbb", "aab", "abb", "", "ba"};
    int n_testes = (int)(sizeof(testes) / sizeof(testes[0]));
    int i;

    printf("========================================\n");
    printf(" Autômato com Pilha (AP)\n");
    printf(" L = { a^n b^n | n >= 1 }\n");
    printf("========================================\n\n");

    printf("Definição formal:\n");
    printf("  M = ({q0,q1,q2}, {a,b}, {A,Z}, δ, q0, Z, {q2})\n\n");

    printf("Transições:\n");
    printf("  δ(q0, a, Z) = {(q0, AZ)}\n");
    printf("  δ(q0, a, A) = {(q0, AA)}\n");
    printf("  δ(q0, b, A) = {(q1, ε)}\n");
    printf("  δ(q1, b, A) = {(q1, ε)}\n");
    printf("  δ(q1, ε, Z) = {(q2, Z)}\n\n");

    printf("----------------------------------------\n");
    printf(" Testando palavras\n");
    printf("----------------------------------------\n\n");

    for (i = 0; i < n_testes; i++) {
        int resultado;

        if (strlen(testes[i]) == 0)
            printf("Palavra: ε (vazia)\n");
        else
            printf("Palavra: \"%s\"\n", testes[i]);

        resultado = ap_aceita(testes[i]);
        printf("  Resultado: %s\n\n", resultado ? "ACEITA ✓" : "REJEITA ✗");
    }

    return 0;
}
