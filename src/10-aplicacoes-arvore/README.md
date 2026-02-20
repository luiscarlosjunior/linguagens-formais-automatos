# Aplicações de Árvores de Derivação

Este diretório contém implementação de um avaliador de expressões aritméticas usando árvores de derivação.

## 📚 Conteúdo

- **avaliador_expressoes.c** - Avaliador de expressões aritméticas via árvore sintática

## 🎯 Objetivos de Aprendizado

- Aplicar árvores de derivação em problemas práticos
- Construir e avaliar árvores sintáticas
- Entender análise sintática em compiladores

---

## Avaliador de Expressões (avaliador_expressoes.c)

### O que o Código Faz?

Este programa demonstra uma aplicação prática de **árvores de derivação**: construir e avaliar expressões aritméticas.

**Processo**:
1. Expressão aritmética → Árvore sintática
2. Árvore sintática → Avaliação (resultado numérico)

```mermaid
flowchart LR
    A["Expressão<br/>'3 + 5 * 2'"] --> B[Análise<br/>Sintática]
    B --> C[Árvore de<br/>Derivação]
    C --> D[Avaliação]
    D --> E["Resultado<br/>13"]
    
    style A fill:#e1f5ff
    style C fill:#fff4e1
    style E fill:#c8e6c9
```

### Gramática Utilizada

```
E → E + T | E - T | T
T → T * F | T / F | F
F → ( E ) | num
```

**Onde**:
- `E` = Expression (Expressão)
- `T` = Term (Termo)
- `F` = Factor (Fator)
- `num` = número

**Hierarquia de Precedência**:
```
F (maior precedência: parênteses e números)
↓
T (multiplicação e divisão)
↓
E (menor precedência: adição e subtração)
```

### Exemplo: "3 + 5 * 2"

#### Árvore Sintática

```mermaid
graph TD
    E1[E] --> E2[E]
    E1 --> plus[+]
    E1 --> T1[T]
    
    E2 --> T2[T]
    T2 --> F1[F]
    F1 --> num1[3]
    
    T1 --> T3[T]
    T1 --> mult[*]
    T1 --> F2[F]
    
    T3 --> F3[F]
    F3 --> num2[5]
    
    F2 --> num3[2]
    
    style E1 fill:#e1f5ff
    style num1 fill:#c8e6c9
    style num2 fill:#c8e6c9
    style num3 fill:#c8e6c9
```

#### Avaliação da Árvore

```mermaid
flowchart TD
    A["E: 3 + 10"] --> B["E: 3"]
    A --> C["T: 10"]
    
    B --> D["T: 3"]
    D --> E["F: 3"]
    
    C --> F["T: 5"]
    C --> G["F: 2"]
    
    F --> H["F: 5"]
    
    style A fill:#c8e6c9
    style E fill:#fff4e1
    style H fill:#fff4e1
    style G fill:#fff4e1
```

**Cálculo bottom-up** (das folhas para a raiz):
1. F: 3 → valor = 3
2. T: 3 → valor = 3
3. E (esquerda): 3 → valor = 3
4. F: 5 → valor = 5
5. T: 5 → valor = 5
6. F: 2 → valor = 2
7. T: 5 * 2 → valor = 10
8. E: 3 + 10 → **valor = 13** ✓

### Por que a Precedência Está Correta?

A gramática garante que `*` é avaliado antes de `+`:

```mermaid
graph TD
    A["Nível E: +, -"] --> B["Nível T: *, /"]
    B --> C["Nível F: (, num"]
    
    D[Menor precedência] -.-> A
    E[Maior precedência] -.-> C
    
    style A fill:#ffcdd2
    style C fill:#c8e6c9
```

**5 * 2 é um único T**, então é calculado primeiro!

### Comparação: Gramática Ambígua vs Não-Ambígua

#### Gramática Ambígua (ERRADO)

```
E → E + E | E * E | num
```

**Problema**: `3 + 5 * 2` tem duas interpretações!

```mermaid
graph TD
    A1[Árvore 1: '3+5' * 2 = 16]
    A2[Árvore 2: 3 + '5*2' = 13]
    
    style A1 fill:#ffcdd2
    style A2 fill:#c8e6c9
```

#### Gramática Não-Ambígua (CORRETO)

```
E → E + T | T
T → T * F | F
F → num
```

**Solução**: Apenas uma árvore possível = **13** ✓

### Estrutura de Nó da Árvore

```c
typedef struct No {
    char simbolo[16];           // "+", "*", "3", etc.
    struct No *filhos[MAX_FILHOS];  // Filhos na árvore
    int num_filhos;             // Quantidade de filhos
    double valor;               // Valor numérico (para folhas)
} No;
```

### Algoritmo de Avaliação

```mermaid
flowchart TD
    A[avaliar nó] --> B{É folha?}
    B -->|Sim| C[Retorna valor<br/>numérico]
    B -->|Não| D[Avalia filhos<br/>recursivamente]
    D --> E{Operador?}
    E -->|+| F[Soma filhos]
    E -->|-| G[Subtrai filhos]
    E -->|*| H[Multiplica filhos]
    E -->|/| I[Divide filhos]
    
    style A fill:#e1f5ff
    style C fill:#c8e6c9
```

**Pseudocódigo**:
```
avaliar(no):
    se no é número:
        retorna valor do número
    
    senão se no é operador:
        esquerda = avaliar(filho_esquerdo)
        direita = avaliar(filho_direito)
        
        se operador é '+':
            retorna esquerda + direita
        se operador é '*':
            retorna esquerda * direita
        ...
```

### Para Executar

```bash
make bin/avaliador_expressoes
./bin/avaliador_expressoes
```

### Exemplo de Saída

```
Avaliador de Expressões Aritméticas

Expressão: 3 + 5 * 2

Árvore Sintática:
E
├── E
│   ├── T
│   │   ├── F
│   │   │   └── 3
├── +
├── T
│   ├── T
│   │   ├── F
│   │   │   └── 5
│   ├── *
│   ├── F
│   │   └── 2

Avaliando...
  F(3) = 3
  T = 3
  E(esq) = 3
  F(5) = 5
  T = 5
  F(2) = 2
  T = 5 * 2 = 10
  E = 3 + 10 = 13

Resultado: 13.0
```

---

## 💡 Aplicação em Compiladores

### Pipeline de Compilação

```mermaid
flowchart LR
    A[Código Fonte] --> B[Análise Léxica<br/>Tokens]
    B --> C[Análise Sintática<br/>Árvore]
    C --> D[Análise Semântica]
    D --> E[Geração de<br/>Código]
    E --> F[Código Objeto]
    
    style C fill:#c8e6c9
```

**Análise Sintática (Parsing)**: Construção da árvore de derivação

### Exemplo: Compilador C

```c
int x = 3 + 5 * 2;
```

**Etapas**:

1. **Léxica**: `int`, `x`, `=`, `3`, `+`, `5`, `*`, `2`, `;`

2. **Sintática**: Constrói árvore

```mermaid
graph TD
    A[Declaração] --> B[Tipo: int]
    A --> C[Variável: x]
    A --> D[Atribuição]
    D --> E[Expressão]
    E --> F[3 + '5*2']
```

3. **Semântica**: Verifica tipos, escopo

4. **Código**: Gera assembly
```asm
mov eax, 5
mul eax, 2    ; 10
add eax, 3    ; 13
mov [x], eax
```

### Tipos de Parsers

#### Top-Down (LL)
```
Começa da raiz → folhas
Exemplo: Parser recursivo descendente
```

#### Bottom-Up (LR)
```
Começa das folhas → raiz
Exemplo: Yacc, Bison
```

```mermaid
graph TD
    A[Gramática] --> B{Tipo?}
    B -->|LL| C[Top-Down<br/>Recursivo]
    B -->|LR| D[Bottom-Up<br/>Shift-Reduce]
    
    C --> E[Parser LL1]
    D --> F[Parser LALR]
    
    style A fill:#e1f5ff
```

## 🔗 Outras Aplicações

### 1. Calculadoras

Calculadoras científicas usam árvores para avaliar expressões:
```
sin(3.14 / 2) + sqrt(16)
```

### 2. Linguagens de Script

Python, JavaScript avaliam código dinamicamente:
```python
eval("3 + 5 * 2")  # Usa parsing interno
```

### 3. Bancos de Dados (SQL)

```sql
SELECT * FROM users WHERE age > 18 AND city = 'SP'
```

Parser constrói árvore para executar query.

### 4. Expressões Regulares

```regex
(a|b)*c+
```

Convertida em árvore para construir autômato.

### 5. Interpretadores

```python
# Interpretador Python
def avaliar(codigo):
    arvore = parse(codigo)
    return executar(arvore)
```

## 📖 Conceitos Avançados

### Árvore Sintática Abstrata (AST)

**Árvore de Derivação** (completa):
```
E → E + T
E → T
T → F
F → 3
```

**AST** (simplificada, sem detalhes gramaticais):
```
   +
  / \
 3   *
    / \
   5   2
```

```mermaid
graph LR
    A[Árvore de<br/>Derivação] -->|Simplifica| B[AST]
    B -->|Remove nós<br/>desnecessários| C[Mais compacta]
    
    style B fill:#c8e6c9
```

**AST é usada** na maioria dos compiladores reais!

### Otimização de Código

Compiladores otimizam a AST:

```c
int x = 3 + 5;  // Conhecido em tempo de compilação
```

**Otimização**: Substituir por `int x = 8;`

```mermaid
graph TD
    A[AST Original] --> B[3 + 5]
    A --> C[Otimizador]
    C --> D[AST Otimizada]
    D --> E[8]
    
    style D fill:#c8e6c9
```

### Análise Semântica

Verificações feitas após construir a árvore:

```c
int x = "abc";  // ERRO: tipo incompatível
y = 10;         // ERRO: variável não declarada
```

**Percorre AST** verificando:
- Tipos compatíveis
- Variáveis declaradas
- Escopo válido

## 🧮 Complexidade

| Operação | Complexidade |
|----------|-------------|
| Construir árvore | O(n) |
| Avaliar árvore | O(n) |
| Otimizar árvore | O(n) a O(n²) |

onde n = número de nós

## 🎯 Vantagens das Árvores

1. **Precedência natural**: Estrutura garante ordem correta
2. **Reutilizável**: Avaliar, imprimir, otimizar mesma árvore
3. **Extensível**: Adicionar novos operadores facilmente
4. **Debug**: Visualizar estrutura do código

## 💻 Ferramentas Reais

### Geradores de Parsers

- **Yacc/Bison** (C/C++)
- **ANTLR** (Java, C++, Python)
- **PLY** (Python)
- **Tree-sitter** (editor syntax highlighting)

Exemplo ANTLR:
```antlr
expr : expr '+' term
     | term
     ;
term : term '*' factor
     | factor
     ;
factor : '(' expr ')'
       | NUMBER
       ;
```

Gera automaticamente parser + AST!

---

**Conclusão**: Árvores de derivação são fundamentais para processamento de linguagens, desde calculadoras simples até compiladores complexos!
