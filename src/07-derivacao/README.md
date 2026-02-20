# Árvore de Derivação e Ambiguidade

Este diretório contém implementação de árvores de derivação para gramáticas livres de contexto.

## 📚 Conteúdo

- **arvore_derivacao.c** - Construção e visualização de árvores de derivação

## 🎯 Objetivos de Aprendizado

- Compreender derivações em gramáticas
- Visualizar árvores de derivação
- Entender o conceito de ambiguidade

---

## Árvore de Derivação (arvore_derivacao.c)

### O que é uma Árvore de Derivação?

Uma **Árvore de Derivação** (Parse Tree) é uma representação visual de como uma palavra é gerada a partir de uma gramática livre de contexto.

**Componentes**:
- **Raiz**: Símbolo inicial da gramática (S)
- **Nós internos**: Variáveis (não-terminais)
- **Folhas**: Símbolos terminais
- **Filhos**: Lado direito de uma regra de produção

```mermaid
graph TD
    A[Gramática] --> B[Derivação]
    B --> C[Árvore de Derivação]
    C --> D[Palavra Gerada]
    
    style A fill:#e1f5ff
    style C fill:#fff4e1
    style D fill:#c8e6c9
```

### Gramática Exemplo

```
S → aSb | ab
```

**Linguagem gerada**: L = { aⁿbⁿ | n ≥ 1 } = {ab, aabb, aaabbb, ...}

**Regras**:
1. `S → aSb` - Recursão: adiciona 'a' à esquerda e 'b' à direita
2. `S → ab` - Caso base: produção terminal

### Árvore de Derivação para "aabb"

```mermaid
graph TD
    S1[S] --> a1[a]
    S1 --> S2[S]
    S1 --> b1[b]
    S2 --> a2[a]
    S2 --> b2[b]
    
    style S1 fill:#e1f5ff
    style S2 fill:#e1f5ff
    style a1 fill:#c8e6c9
    style a2 fill:#c8e6c9
    style b1 fill:#c8e6c9
    style b2 fill:#c8e6c9
```

**Leitura das folhas** (da esquerda para a direita): a, a, b, b = "aabb" ✓

### Derivação Passo a Passo

**Derivação à esquerda** (leftmost derivation):

```
S ⇒ aSb         (aplica S → aSb)
  ⇒ aaSbb       (aplica S → aSb no S da esquerda)
  ⇒ aabbb       (aplica S → ab)
```

Resultado: **"aabb"**

```mermaid
flowchart TD
    A[S] --> B["aSb<br/>(aplica 1ª regra)"]
    B --> C["aaSbb<br/>(aplica 1ª regra em S)"]
    C --> D["aabb<br/>(aplica 2ª regra em S)"]
    
    style A fill:#e1f5ff
    style D fill:#c8e6c9
```

### Árvore de Derivação para "aaabbb"

```mermaid
graph TD
    S1[S] --> a1[a]
    S1 --> S2[S]
    S1 --> b1[b]
    S2 --> a2[a]
    S2 --> S3[S]
    S2 --> b2[b]
    S3 --> a3[a]
    S3 --> b3[b]
    
    style S1 fill:#e1f5ff
    style S2 fill:#e1f5ff
    style S3 fill:#e1f5ff
```

**Fronteira** (yield): a, a, a, b, b, b = "aaabbb" ✓

### Estrutura de Nó da Árvore

```c
typedef struct No {
    char simbolo[16];           // Símbolo (terminal ou não-terminal)
    struct No *filhos[MAX_FILHOS];  // Ponteiros para filhos
    int num_filhos;             // Quantidade de filhos
} No;
```

```mermaid
classDiagram
    class No {
        +char simbolo
        +No* filhos[]
        +int num_filhos
        +adicionar_filho()
    }
    No --> No : tem filhos
```

### Como Construir a Árvore

```mermaid
flowchart TD
    A[Criar nó raiz S] --> B{Aplicar qual regra?}
    B -->|S → aSb| C[Criar filhos:<br/>a, S, b]
    B -->|S → ab| D[Criar filhos:<br/>a, b]
    C --> E{S filho precisa<br/>expandir?}
    E -->|Sim| B
    E -->|Não| F[Árvore completa]
    D --> F
    
    style A fill:#e1f5ff
    style F fill:#c8e6c9
```

### Impressão da Árvore

O código imprime a árvore com indentação visual:

```
S
├── a
├── S
│   ├── a
│   ├── b
├── b
```

### Fronteira (Yield) da Árvore

A **fronteira** é a concatenação das folhas da esquerda para a direita.

```mermaid
graph LR
    A[Árvore de<br/>Derivação] --> B[Percorrer folhas<br/>esquerda → direita]
    B --> C[Palavra Gerada]
    
    style C fill:#c8e6c9
```

**Algoritmo**:
1. Se nó é folha (terminal), imprime símbolo
2. Senão, percorre filhos recursivamente da esquerda para direita

### Para Executar

```bash
make bin/arvore_derivacao
./bin/arvore_derivacao
```

### Exemplo de Saída

```
Árvore de Derivação para "aabb"
═══════════════════════════════

S
├── a
├── S
│   ├── a
│   ├── b
├── b

Derivação: aabb

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Árvore de Derivação para "aaabbb"
══════════════════════════════════

S
├── a
├── S
│   ├── a
│   ├── S
│   │   ├── a
│   │   ├── b
│   ├── b
├── b

Derivação: aaabbb
```

---

## 🔄 Tipos de Derivação

### Derivação à Esquerda (Leftmost)

Sempre expande o **não-terminal mais à esquerda** primeiro.

```
S ⇒ aSb ⇒ aaSbb ⇒ aabb
     ^       ^        ^
```

### Derivação à Direita (Rightmost)

Sempre expande o **não-terminal mais à direita** primeiro.

```
S ⇒ aSb ⇒ aaSbb ⇒ aabb
         ^    ^      ^
```

**Importante**: Derivações diferentes podem produzir a **mesma árvore**.

```mermaid
graph TD
    A[Derivação à Esquerda] --> C[Mesma Árvore]
    B[Derivação à Direita] --> C
    C --> D[Mesma Palavra]
    
    style C fill:#fff4e1
    style D fill:#c8e6c9
```

---

## ⚠️ Ambiguidade

### O que é Ambiguidade?

Uma gramática é **ambígua** se existe uma palavra que pode ser gerada por **duas ou mais árvores de derivação diferentes**.

### Exemplo: Gramática Ambígua

```
E → E + E | E * E | (E) | id
```

Para a expressão `id + id * id`:

#### Árvore 1: (id + id) * id

```mermaid
graph TD
    E1[E] --> E2[E]
    E1 --> mult[*]
    E1 --> E3[E]
    E2 --> E4[E]
    E2 --> plus[+]
    E2 --> E5[E]
    E4 --> id1[id]
    E5 --> id2[id]
    E3 --> id3[id]
    
    style E1 fill:#ffcdd2
```

Resultado: (id + id) * id = **precedência errada!**

#### Árvore 2: id + (id * id)

```mermaid
graph TD
    E1[E] --> E2[E]
    E1 --> plus[+]
    E1 --> E3[E]
    E2 --> id1[id]
    E3 --> E4[E]
    E3 --> mult[*]
    E3 --> E5[E]
    E4 --> id2[id]
    E5 --> id3[id]
    
    style E1 fill:#c8e6c9
```

Resultado: id + (id * id) = **precedência correta!**

### Problema da Ambiguidade

```mermaid
flowchart TD
    A[Expressão Ambígua] --> B[Múltiplas Árvores]
    B --> C[Múltiplos Significados]
    C --> D[⚠️ Comportamento<br/>Indefinido]
    
    style D fill:#ffcdd2
```

**Em compiladores**: Ambiguidade leva a resultados imprevisíveis!

### Soluções para Ambiguidade

#### 1. Reescrever a Gramática

Adicionar níveis de precedência:

```
E  → E + T | T
T  → T * F | F
F  → (E) | id
```

Agora `*` tem maior precedência que `+`.

```mermaid
graph TD
    E[E] --> E2[E]
    E --> plus[+]
    E --> T[T]
    E2 --> T2[T]
    T --> T3[T]
    T --> mult[*]
    T --> F[F]
    T2 --> F2[F]
    T3 --> F3[F]
    F2 --> id1[id]
    F3 --> id2[id]
    F --> id3[id]
    
    style E fill:#c8e6c9
```

**Única árvore possível** → Não-ambígua!

#### 2. Adicionar Regras de Precedência

Manter gramática ambígua, mas adicionar regras externas:
- `*` tem precedência sobre `+`
- Associatividade à esquerda

```mermaid
flowchart LR
    A[Gramática Ambígua] --> B[+ Regras de<br/>Precedência]
    B --> C[Parser Determinístico]
    
    style C fill:#c8e6c9
```

### Teste de Ambiguidade

**Não existe** algoritmo geral para determinar se uma gramática é ambígua!

**Na prática**:
- Procurar exemplos de palavras com múltiplas derivações
- Usar ferramentas de análise sintática (Bison, ANTLR)
- Testar casos problemáticos (operadores, recursão)

---

## 💡 Conceitos-chave

### Árvore de Derivação
- **Representa** como uma palavra é gerada
- **Raiz**: Símbolo inicial
- **Folhas**: Palavra gerada (terminais)
- **Estrutura**: Mostra aplicação das regras

### Derivação
- **Sequência de substituições** de variáveis
- **À esquerda**: Expande sempre a variável mais à esquerda
- **À direita**: Expande sempre a variável mais à direita
- **Derivações diferentes** podem dar mesma árvore

### Ambiguidade
- **Múltiplas árvores** para mesma palavra
- **Problema** em compiladores e interpretadores
- **Solução**: Reescrever gramática ou adicionar regras

## 🔗 Aplicações Práticas

### Compiladores
```
Código Fonte → Árvore Sintática → Código Intermediário
```

A árvore de derivação é a base para:
- **Análise sintática**
- **Verificação de tipos**
- **Geração de código**

### Linguagens de Programação

```c
if (x > 0) {
    y = x + 1;
}
```

Parser cria árvore:
```
if
├── condição: x > 0
└── bloco
    └── atribuição: y = x + 1
```

### Processamento de Linguagem Natural

```
"O gato bebeu o leite"
```

Árvore sintática:
```
Sentença
├── Sujeito: O gato
└── Predicado
    ├── Verbo: bebeu
    └── Objeto: o leite
```

## 📖 Relação com Outras Estruturas

```mermaid
graph TD
    A[Gramática Livre<br/>de Contexto] --> B[Árvore de<br/>Derivação]
    B --> C[Árvore Sintática<br/>Abstrata AST]
    C --> D[Código<br/>Intermediário]
    D --> E[Código de<br/>Máquina]
    
    style A fill:#e1f5ff
    style B fill:#fff4e1
    style C fill:#fff4e1
    style E fill:#c8e6c9
```

**AST (Abstract Syntax Tree)**: Versão simplificada da árvore de derivação, removendo detalhes sintáticos desnecessários.

## 🎯 Importância

- **Fundamento** da análise sintática
- **Visualização** de estruturas gramaticais
- **Detecção** de ambiguidade
- **Base** para otimizações em compiladores
