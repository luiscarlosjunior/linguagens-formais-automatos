/*
 * Linguagens Formais e Autômatos
 *
 * Avaliador de Expressões Aritméticas via Árvore de Derivação
 * Demonstrates practical application of parse trees:
 * builds a parse tree from an arithmetic expression grammar
 * and evaluates it by traversing the tree.
 *
 * Grammar (simplified):
 *   E → E + T | E - T | T
 *   T → T * F | T / F | F
 *   F → ( E ) | num
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILHOS  4
#define MAX_EXPR  128

/* ==================== Nó da Árvore ======================= */

typedef struct No {
    char simbolo[16];           /* símbolo gramatical ou terminal */
    struct No *filhos[MAX_FILHOS];
    int num_filhos;
    double valor;               /* valor numérico para folhas */
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
    no->valor = 0;
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

/* ============== Impressão da Árvore ====================== */

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

/* ============== Lexer (Análise Léxica) =================== */

typedef struct {
    const char *entrada;        /* expressão de entrada */
    int pos;                    /* posição atual */
    char token;                 /* token atual: 'd' = dígito, ou o próprio char */
    int valor_token;            /* valor numérico se token == 'd' */
} Lexer;

/* Inicializa o lexer com a expressão */
void lexer_init(Lexer *lex, const char *expr)
{
    lex->entrada = expr;
    lex->pos = 0;
    lex->token = '\0';
    lex->valor_token = 0;
}

/* Avança para o próximo token */
void proximo_token(Lexer *lex)
{
    /* Pula espaços em branco */
    while (lex->entrada[lex->pos] == ' ')
        lex->pos++;

    if (lex->entrada[lex->pos] == '\0') {
        lex->token = '\0';
        return;
    }

    if (lex->entrada[lex->pos] >= '0' && lex->entrada[lex->pos] <= '9') {
        lex->token = 'd';  /* número */
        lex->valor_token = 0;
        while (lex->entrada[lex->pos] >= '0' && lex->entrada[lex->pos] <= '9') {
            lex->valor_token = lex->valor_token * 10 + (lex->entrada[lex->pos] - '0');
            lex->pos++;
        }
        return;  /* não avança pos extra */
    } else {
        lex->token = lex->entrada[lex->pos];
    }
    lex->pos++;
}

/* ========== Parser (Analisador Sintático) ================ */

/*
 * Implementação de um parser descendente recursivo.
 * Como a gramática original é recursiva à esquerda:
 *   E → E + T | E - T | T
 *   T → T * F | T / F | F
 *
 * Reescrevemos de forma iterativa dentro de cada função
 * para evitar recursão infinita, mas construímos a árvore
 * refletindo a estrutura gramatical original.
 */

/* Declarações antecipadas */
No *parse_E(Lexer *lex);
No *parse_T(Lexer *lex);
No *parse_F(Lexer *lex);

/* F → ( E ) | num */
No *parse_F(Lexer *lex)
{
    No *no;

    if (lex->token == '(') {
        /* F → ( E ) */
        no = criar_no("F");
        adicionar_filho(no, criar_no("("));
        proximo_token(lex);  /* consome '(' */

        adicionar_filho(no, parse_E(lex));

        if (lex->token == ')') {
            adicionar_filho(no, criar_no(")"));
            proximo_token(lex);  /* consome ')' */
        } else {
            fprintf(stderr, "Erro de sintaxe: ')' esperado na posição %d\n", lex->pos);
            exit(1);
        }
        return no;
    }

    if (lex->token == 'd') {
        /* F → num */
        char buf[16];
        no = criar_no("F");
        sprintf(buf, "%d", lex->valor_token);

        No *folha = criar_no(buf);
        folha->valor = lex->valor_token;
        adicionar_filho(no, folha);

        proximo_token(lex);  /* consome dígito */
        return no;
    }

    fprintf(stderr, "Erro de sintaxe na posição %d\n", lex->pos);
    exit(1);
    return NULL;
}

/* T → T * F | T / F | F  (eliminando recursão à esquerda) */
No *parse_T(Lexer *lex)
{
    No *esquerda = parse_F(lex);

    while (lex->token == '*' || lex->token == '/') {
        char op[2] = { lex->token, '\0' };
        No *no = criar_no("T");
        No *t_esq = criar_no("T");
        adicionar_filho(t_esq, esquerda);
        adicionar_filho(no, t_esq);
        adicionar_filho(no, criar_no(op));
        proximo_token(lex);  /* consome operador */
        adicionar_filho(no, parse_F(lex));
        esquerda = no;
    }

    /* Se não houve operador, T → F */
    if (strcmp(esquerda->simbolo, "F") == 0) {
        No *no = criar_no("T");
        adicionar_filho(no, esquerda);
        return no;
    }

    return esquerda;
}

/* E → E + T | E - T | T  (eliminando recursão à esquerda) */
No *parse_E(Lexer *lex)
{
    No *esquerda = parse_T(lex);

    while (lex->token == '+' || lex->token == '-') {
        char op[2] = { lex->token, '\0' };
        No *no = criar_no("E");
        No *e_esq = criar_no("E");
        adicionar_filho(e_esq, esquerda);
        adicionar_filho(no, e_esq);
        adicionar_filho(no, criar_no(op));
        proximo_token(lex);  /* consome operador */
        adicionar_filho(no, parse_T(lex));
        esquerda = no;
    }

    /* Se não houve operador, E → T */
    if (strcmp(esquerda->simbolo, "T") == 0) {
        No *no = criar_no("E");
        adicionar_filho(no, esquerda);
        return no;
    }

    return esquerda;
}

/* Constrói a árvore de derivação para uma expressão */
No *construir_arvore(const char *expr)
{
    Lexer lex;
    No *arvore;
    lexer_init(&lex, expr);
    proximo_token(&lex);
    arvore = parse_E(&lex);
    if (lex.token != '\0') {
        fprintf(stderr, "Erro de sintaxe: entrada não consumida na posição %d\n", lex.pos);
        exit(1);
    }
    return arvore;
}

/* ============== Avaliação da Árvore ====================== */

/* Avalia a árvore de derivação recursivamente */
double avaliar(No *no)
{
    if (!no)
        return 0;

    /* Folha numérica (terminal) */
    if (no->num_filhos == 0)
        return no->valor;

    /* E → T  ou  T → F  ou  F → num  (produção unitária) */
    if (no->num_filhos == 1)
        return avaliar(no->filhos[0]);

    /* F → ( E ) */
    if (strcmp(no->simbolo, "F") == 0 && no->num_filhos == 3)
        return avaliar(no->filhos[1]);

    /* E → E op T  ou  T → T op F  (três filhos: esq, op, dir) */
    if (no->num_filhos == 3) {
        double esq = avaliar(no->filhos[0]);
        double dir = avaliar(no->filhos[2]);
        char op = no->filhos[1]->simbolo[0];

        switch (op) {
            case '+': return esq + dir;
            case '-': return esq - dir;
            case '*': return esq * dir;
            case '/':
                if (dir == 0) {
                    fprintf(stderr, "Erro: divisão por zero.\n");
                    return 0;
                }
                return esq / dir;
        }
    }

    return 0;
}

/* ============== Processamento de Expressão ================ */

/* Processa uma expressão: imprime, constrói árvore, avalia */
void processar_expressao(const char *expr)
{
    double resultado;
    No *arvore;

    printf("--------------------------------------------\n");
    printf(" Expressão: \"%s\"\n", expr);
    printf("--------------------------------------------\n\n");

    arvore = construir_arvore(expr);

    printf("  Árvore de derivação:\n");
    imprimir_arvore(arvore, 0);
    printf("\n");

    resultado = avaliar(arvore);
    printf("  Avaliação: %s ⇒ %g\n\n", expr, resultado);

    liberar_arvore(arvore);
}

/* ========================= Main ========================== */

int main(void)
{
    printf("============================================\n");
    printf(" Avaliador de Expressões Aritméticas\n");
    printf(" via Árvore de Derivação\n");
    printf("============================================\n\n");

    printf("  Aplicação prática de árvores de derivação:\n");
    printf("  a árvore é construída a partir da gramática\n");
    printf("  e avaliada percorrendo-a recursivamente.\n\n");

    printf("  Gramática utilizada:\n");
    printf("    E → E + T | E - T | T\n");
    printf("    T → T * F | T / F | F\n");
    printf("    F → ( E ) | num\n\n");

    processar_expressao("3+4*2");
    processar_expressao("(3+4)*2");
    processar_expressao("9-3/3");
    processar_expressao("((2+3)*4)-1");

    return 0;
}
