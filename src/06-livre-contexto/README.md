# Gramáticas Livres de Contexto e Autômatos com Pilha

Este diretório contém implementação de um Autômato com Pilha (Pushdown Automaton).

## 📚 Conteúdo

- **automato_pilha.c** - Autômato com Pilha que reconhece a^n b^n

## 🎯 Objetivos de Aprendizado

- Entender linguagens que vão além das regulares
- Compreender o papel da pilha na computação
- Simular autômatos com pilha

---

## Autômato com Pilha (automato_pilha.c)

### O que é um Autômato com Pilha?

Um **Autômato com Pilha (AP)** ou **Pushdown Automaton (PDA)** é uma extensão do autômato finito que possui uma **pilha** de memória auxiliar.

**Características**:
- Lê entrada símbolo por símbolo (como AFD/AFND)
- Tem acesso a uma **pilha** (LIFO - Last In, First Out)
- Pode empilhar (push) e desempilhar (pop) símbolos
- **Mais poderoso** que autômatos finitos

### Por que Precisamos de Pilha?

Autômatos finitos **NÃO conseguem** reconhecer linguagens como:
- `L = { aⁿbⁿ | n ≥ 1 }` = {ab, aabb, aaabbb, ...}
- Parênteses balanceados: (), (()), ((()))
- Palíndromos: aba, abba, abcba

**Motivo**: Precisam "contar" ou "lembrar" infinitas possibilidades.

```mermaid
graph TD
    A[Linguagens Regulares] -->|AFD/AFND| B[Reconhecíveis sem memória]
    C[Linguagens Livres<br/>de Contexto] -->|AP| D[Precisam de pilha]
    C --> E[Incluem aⁿbⁿ,<br/>parênteses balanceados]
    
    style A fill:#e1f5ff
    style C fill:#c8e6c9
```

### Definição Formal

```
M = (Q, Σ, Γ, δ, q₀, Z₀, F)

Q  = {q0, q1, q2}          Estados
Σ  = {a, b}                Alfabeto de entrada
Γ  = {A, Z}                Alfabeto da pilha
q₀ = q0                    Estado inicial
Z₀ = Z                     Símbolo inicial da pilha
F  = {q2}                  Estados de aceitação
δ  = função de transição   Q × (Σ ∪ {ε}) × Γ → P(Q × Γ*)
```

### Linguagem Reconhecida

```
L = { aⁿbⁿ | n ≥ 1 }
  = {ab, aabb, aaabbb, aaaabbbb, ...}
```

**Exemplos**:
- ✓ "ab" → ACEITA (1 a, 1 b)
- ✓ "aabb" → ACEITA (2 a's, 2 b's)
- ✓ "aaabbb" → ACEITA (3 a's, 3 b's)
- ✗ "aab" → REJEITA (2 a's, 1 b)
- ✗ "abb" → REJEITA (1 a, 2 b's)

### Diagrama de Estados e Transições

```mermaid
stateDiagram-v2
    [*] --> q0
    q0 --> q0 : a, Z/AZ<br/>a, A/AA
    q0 --> q1 : b, A/ε
    q1 --> q1 : b, A/ε
    q1 --> q2 : ε, Z/Z
    q2 --> [*]
    
    note right of q0
        Lê a's e empilha A's
    end note
    note right of q1
        Lê b's e desempilha A's
    end note
    note right of q2
        Aceitação: pilha só tem Z
    end note
```

**Notação**: `símbolo_lido, topo_pilha/escreve_na_pilha`

### Como Funciona a Estratégia

```mermaid
flowchart TD
    A[Fase 1: Lendo a's] --> B[Para cada 'a'<br/>empilha um 'A']
    B --> C[Conta os a's<br/>usando a pilha]
    C --> D[Fase 2: Lendo b's]
    D --> E[Para cada 'b'<br/>desempilha um 'A']
    E --> F{Pilha ficou<br/>só com Z?}
    F -->|Sim| G[✓ Mesma quantidade<br/>ACEITA]
    F -->|Não| H[✗ Quantidades diferentes<br/>REJEITA]
    
    style A fill:#e1f5ff
    style D fill:#fff4e1
    style G fill:#c8e6c9
    style H fill:#ffcdd2
```

### Tabela de Transições Detalhada

```
Estado  Lê  Topo   →  Novo Estado  Escreve
──────  ──  ────      ───────────  ───────
q0      a   Z     →   q0           AZ      (empilha A)
q0      a   A     →   q0           AA      (empilha A)
q0      b   A     →   q1           ε       (desempilha A)
q1      b   A     →   q1           ε       (desempilha A)
q1      ε   Z     →   q2           Z       (transição-ε)
```

### Exemplo de Execução: "aabb"

```mermaid
graph TD
    A["(q0, aabb, Z)"] -->|lê 'a'| B["(q0, abb, AZ)"]
    B -->|lê 'a'| C["(q0, bb, AAZ)"]
    C -->|lê 'b'| D["(q1, b, AZ)"]
    D -->|lê 'b'| E["(q1, ε, Z)"]
    E -->|ε-trans| F["(q2, ε, Z)"]
    
    style A fill:#e1f5ff
    style F fill:#c8e6c9
    
    G["Pilha cresce"] --> B
    G --> C
    H["Pilha diminui"] --> D
    H --> E
```

**Passo a passo**:

| Passo | Estado | Entrada Restante | Pilha | Ação |
|-------|--------|------------------|-------|------|
| 0 | q0 | aabb | Z | Inicial |
| 1 | q0 | abb | AZ | Lê 'a', empilha A |
| 2 | q0 | bb | AAZ | Lê 'a', empilha A |
| 3 | q1 | b | AZ | Lê 'b', desempilha A |
| 4 | q1 | ε | Z | Lê 'b', desempilha A |
| 5 | q2 | ε | Z | Transição-ε, **ACEITA** |

### Visualização da Pilha

```mermaid
flowchart LR
    A[Z] -->|lê 'a'| B[A<br/>Z]
    B -->|lê 'a'| C[A<br/>A<br/>Z]
    C -->|lê 'b'| D[A<br/>Z]
    D -->|lê 'b'| E[Z]
    
    F[Topo] -.-> C
    G[Base] -.-> A
    
    style A fill:#e1f5ff
    style E fill:#c8e6c9
```

### Configuração Instantânea

Uma **configuração** do AP é representada por:
```
(estado, entrada_restante, conteúdo_pilha)
```

**Exemplo**: `(q0, "abb", "AZ")`
- Estado atual: q0
- Ainda precisa ler: "abb"
- Pilha tem: A no topo, Z na base

### Transições-ε (Epsilon)

O AP pode fazer transições **sem consumir entrada**:
```
δ(q1, ε, Z) = {(q2, Z)}
```

Permite mudanças de estado baseadas apenas no estado e pilha.

```mermaid
stateDiagram-v2
    q1 --> q2 : ε, Z/Z
    
    note right of q1
        Não consome entrada
        Apenas verifica pilha
    end note
```

### Para Executar

```bash
make bin/automato_pilha
./bin/automato_pilha
```

### Exemplo de Saída

```
Autômato com Pilha (AP)
L = { aⁿbⁿ | n >= 1 }

Palavra: "aabb"
  Configurações:
  (q0, aabb, Z)
  (q0, abb, AZ)
  (q0, bb, AAZ)
  (q1, b, AZ)
  (q1, ε, Z)
  (q2, ε, Z)
  Resultado: ACEITA ✓

Palavra: "aab"
  Configurações:
  (q0, aab, Z)
  (q0, ab, AZ)
  (q0, b, AAZ)
  (q1, ε, AZ)
  Estado final: q1 (não é aceitação)
  Resultado: REJEITA ✗
```

---

## 💡 Conceitos-chave

### Pilha (Stack)
- **LIFO**: Last In, First Out (último a entrar, primeiro a sair)
- **Push**: Adiciona elemento no topo
- **Pop**: Remove elemento do topo
- **Top**: Consulta elemento do topo sem remover

### Poder Computacional
```mermaid
graph TD
    A[AFD/AFND] -->|Adiciona pilha| B[Autômato com Pilha]
    B -->|Adiciona fita<br/>bi-direcional| C[Máquina de Turing]
    
    D[Linguagens<br/>Regulares] --> A
    E[Linguagens Livres<br/>de Contexto] --> B
    F[Linguagens<br/>Recursivamente<br/>Enumeráveis] --> C
    
    style A fill:#e1f5ff
    style B fill:#fff4e1
    style C fill:#c8e6c9
```

### Determinismo vs Não-Determinismo

**AP Determinístico (APD)**:
- Para cada (estado, símbolo, topo), no máximo uma transição
- **Menos poderoso** que AP não-determinístico

**AP Não-Determinístico (APND)**:
- Pode ter múltiplas transições
- Equivalente em poder a **Gramáticas Livres de Contexto**

```
Linguagens reconhecidas por APD ⊂ Linguagens reconhecidas por APND = GLC
```

## 🔗 Relação com Gramáticas

Todo Autômato com Pilha corresponde a uma **Gramática Livre de Contexto**:

**Gramática para aⁿbⁿ**:
```
S → aSb | ab
```

**Derivação de "aabb"**:
```
S ⇒ aSb
  ⇒ aaSbb
  ⇒ aabbb
```

```mermaid
flowchart LR
    A[Gramática Livre<br/>de Contexto] <-->|Conversão| B[Autômato<br/>com Pilha]
    
    style A fill:#e1f5ff
    style B fill:#c8e6c9
```

## 📖 Aplicações Práticas

### Análise Sintática
Compiladores usam AP para verificar sintaxe:
```c
if (x > 0) {
    y = x + 1;
}
```

A pilha rastreia:
- Parênteses abertos/fechados
- Blocos aninhados
- Estruturas de controle

### Avaliação de Expressões
```
3 + (5 * 2)
```

Pilha mantém operadores e operandos.

### Validação de XML/HTML
```xml
<html>
  <body>
    <div>Conteúdo</div>
  </body>
</html>
```

Pilha rastreia tags abertas.

## 🧮 Limitações dos AP

Linguagens que **NÃO** podem ser reconhecidas por AP:
- `{ aⁿbⁿcⁿ | n ≥ 0 }` - precisa de duas pilhas
- `{ ww | w ∈ {a,b}* }` - palíndromos pares
- Linguagens sensíveis ao contexto

Para essas, precisamos de **Máquinas de Turing**.

## 🎯 Hierarquia de Chomsky

```mermaid
graph TD
    A[Tipo 3: Regulares] --> B[Tipo 2: Livres de Contexto]
    B --> C[Tipo 1: Sensíveis ao Contexto]
    C --> D[Tipo 0: Recursivamente<br/>Enumeráveis]
    
    E[AFD/AFND] -.-> A
    F[AP] -.-> B
    G[Autômato Linearmente<br/>Limitado] -.-> C
    H[Máquina de Turing] -.-> D
    
    style B fill:#c8e6c9
    style F fill:#c8e6c9
```

**AP reconhecem exatamente as Linguagens Livres de Contexto (Tipo 2)**
