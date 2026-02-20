# Minimização e Conversão de Autômatos

Este diretório contém implementações de algoritmos importantes para transformar e otimizar autômatos.

## 📚 Conteúdo

- **conversao_afnd_afd.c** - Conversão de AFND para AFD (Construção de Subconjuntos)
- **minimizacao.c** - Minimização de AFD (Algoritmo de Preenchimento de Tabela)

## 🎯 Objetivos de Aprendizado

- Converter AFND em AFD equivalente
- Minimizar AFD removendo estados redundantes
- Entender equivalência de estados

---

## 1. Conversão AFND → AFD (conversao_afnd_afd.c)

### O que é a Construção de Subconjuntos?

A **Construção de Subconjuntos** (Subset Construction) é um algoritmo que converte qualquer AFND em um AFD equivalente.

**Ideia principal**: Cada estado do AFD representa um **conjunto de estados** do AFND.

```mermaid
flowchart LR
    A["AFND<br/>3 estados"] -->|Construção de<br/>Subconjuntos| B["AFD<br/>até 2³=8 estados"]
    
    style A fill:#e1f5ff
    style B fill:#c8e6c9
```

### Como Funciona

```mermaid
flowchart TD
    A[Inicia com {q₀}] --> B[Coloca na fila]
    B --> C{Fila vazia?}
    C -->|Não| D[Remove conjunto S da fila]
    D --> E[Para cada símbolo a]
    E --> F[Calcula δ'S,a' = união de δ'q,a'<br/>para todo q em S]
    F --> G{Conjunto novo?}
    G -->|Sim| H[Adiciona à fila<br/>Cria novo estado do AFD]
    G -->|Não| I[Apenas registra transição]
    H --> E
    I --> E
    E --> J{Mais símbolos?}
    J -->|Sim| E
    J -->|Não| C
    C -->|Sim| K[AFD Completo]
    
    style A fill:#e1f5ff
    style K fill:#c8e6c9
```

### Algoritmo Passo a Passo

#### 1. Estado Inicial
```
Estado inicial do AFD = {q₀} (estado inicial do AFND)
```

#### 2. Calcular Transições
Para cada conjunto S e símbolo a:
```
δ_AFD(S, a) = ⋃ δ_AFND(q, a)
              q∈S
```

#### 3. Estados de Aceitação
```
S é de aceitação no AFD ⟺ S ∩ F_AFND ≠ ∅
```

### Exemplo: AFND que reconhece cadeias contendo "ab"

#### AFND Original

```mermaid
stateDiagram-v2
    [*] --> q0
    q0 --> q0 : a,b
    q0 --> q1 : a
    q1 --> q2 : b
    q2 --> q2 : a,b
    q2 --> [*]
    
    note right of q0
        Estado inicial
    end note
    note right of q2
        Estado aceitação
    end note
```

**Transições do AFND:**
```
δ(q0, a) = {q0, q1}
δ(q0, b) = {q0}
δ(q1, a) = ∅
δ(q1, b) = {q2}
δ(q2, a) = {q2}
δ(q2, b) = {q2}
```

#### Construção do AFD

```mermaid
graph TD
    A["{q0}"] -->|a| B["{q0,q1}"]
    A -->|b| A
    B -->|a| B
    B -->|b| C["{q0,q2}"]
    C -->|a| D["{q0,q1,q2}"]
    C -->|b| C
    D -->|a| D
    D -->|b| C
    
    style A fill:#e1f5ff
    style C fill:#c8e6c9
    style D fill:#c8e6c9
```

**Estados do AFD resultante:**
1. {q0} - inicial (não aceita)
2. {q0, q1} - não aceita
3. {q0, q2} - **aceita** (contém q2)
4. {q0, q1, q2} - **aceita** (contém q2)

### Complexidade

- **Pior caso**: O AFD pode ter 2^n estados (n = estados do AFND)
- **Prática**: Geralmente muito menor que 2^n
- **Tempo**: O(2^n × |Σ|) no pior caso

```mermaid
graph LR
    A[AFND: n estados] --> B[AFD: até 2ⁿ estados]
    
    C["n=3 → até 8 estados<br/>n=5 → até 32 estados<br/>n=10 → até 1024 estados"]
    
    style A fill:#e1f5ff
    style B fill:#fff4e1
```

### Para Executar

```bash
make bin/conversao_afnd_afd
./bin/conversao_afnd_afd
```

---

## 2. Minimização de AFD (minimizacao.c)

### O que é Minimização?

**Minimização** é o processo de reduzir um AFD ao menor número possível de estados, mantendo a linguagem reconhecida.

**Objetivo**: Encontrar o **AFD mínimo** - aquele com o menor número de estados possível.

### Estados Equivalentes

Dois estados p e q são **equivalentes** se:
- Para toda palavra w, δ(p, w) aceita ⟺ δ(q, w) aceita
- Comportam-se da mesma forma para qualquer entrada futura

```mermaid
graph TD
    A[Estados p e q] --> B{Para toda palavra w}
    B --> C{δ'p,w' e δ'q,w'<br/>ambos aceitam<br/>ou ambos rejeitam?}
    C -->|Sim| D[p e q são<br/>EQUIVALENTES]
    C -->|Não| E[p e q são<br/>DISTINGUÍVEIS]
    
    style D fill:#c8e6c9
    style E fill:#ffcdd2
```

### Algoritmo de Preenchimento de Tabela

#### Passo 1: Remover Estados Inalcançáveis

```mermaid
flowchart LR
    A[Estado Inicial] --> B[BFS/DFS]
    B --> C[Marca estados<br/>alcançáveis]
    C --> D[Remove não<br/>alcançáveis]
    
    style A fill:#e1f5ff
    style D fill:#c8e6c9
```

#### Passo 2: Marcar Pares Trivialmente Distinguíveis

Estados onde um aceita e outro rejeita são **obviamente distinguíveis**.

```
Se p ∈ F e q ∉ F, então (p,q) é distinguível
```

```mermaid
graph TD
    A["Estado p<br/>(aceitação)"] -.distinguível.- B["Estado q<br/>(não-aceitação)"]
    
    style A fill:#c8e6c9
    style B fill:#ffcdd2
```

#### Passo 3: Propagar Distinguibilidade

Se δ(p,a) e δ(q,a) são distinguíveis, então p e q também são.

```mermaid
flowchart TD
    A["Para cada par (p,q)<br/>não marcado"] --> B["Para cada símbolo a"]
    B --> C["r = δ(p,a)<br/>s = δ(q,a)"]
    C --> D{(r,s) já está<br/>marcado?}
    D -->|Sim| E["Marca (p,q)<br/>como distinguível"]
    D -->|Não| F[Continua]
    E --> G{Alguma<br/>nova marcação?}
    F --> G
    G -->|Sim| A
    G -->|Não| H[Fim: pares não marcados<br/>são equivalentes]
    
    style A fill:#e1f5ff
    style H fill:#c8e6c9
```

#### Passo 4: Fundir Estados Equivalentes

Pares que **não foram marcados** são equivalentes e podem ser fundidos.

```mermaid
flowchart LR
    A[Estados Equivalentes] --> B[Fundir em um<br/>único estado]
    B --> C[AFD Mínimo]
    
    style C fill:#c8e6c9
```

### Exemplo Completo

**AFD Original** (6 estados):

```mermaid
stateDiagram-v2
    [*] --> q0
    q0 --> q1 : 0
    q0 --> q3 : 1
    q1 --> q0 : 0
    q1 --> q2 : 1
    q2 --> q1 : 0
    q2 --> q4 : 1
    q3 --> q0 : 0
    q3 --> q4 : 1
    q4 --> q3 : 0
    q4 --> q5 : 1
    q5 --> q4 : 0
    q5 --> q0 : 1
    q0 --> [*]
```

Reconhece: cadeias binárias com número **par** de 0's.

**Análise de Equivalência:**
- q0 ≡ q0 (trivial)
- q1 ≡ q3 (mesmo comportamento)
- q2 ≡ q4 (mesmo comportamento)
- q5 é único

**AFD Minimizado** (2 estados):

```mermaid
stateDiagram-v2
    [*] --> Par
    Par --> Ímpar : 0
    Par --> Par : 1
    Ímpar --> Par : 0
    Ímpar --> Ímpar : 1
    Par --> [*]
    
    note right of Par
        Número par de 0's
        (aceita)
    end note
    note right of Ímpar
        Número ímpar de 0's
        (rejeita)
    end note
```

Redução: **6 estados → 2 estados**

### Matriz de Distinguibilidade

Tabela triangular para marcar pares distinguíveis:

```
     q0  q1  q2  q3  q4
q1   [ ]
q2   [X] [ ]
q3   [ ] [≡] [X]
q4   [X] [X] [≡] [X]
q5   [X] [X] [X] [X] [X]
```

- `[X]` = distinguível
- `[≡]` = equivalente (não marcado)
- `[ ]` = ainda não determinado

### Para Executar

```bash
make bin/minimizacao
./bin/minimizacao
```

---

## 🔗 Relacionamento entre os Algoritmos

```mermaid
flowchart TD
    A[AFND] -->|Construção de<br/>Subconjuntos| B[AFD]
    B -->|Pode ter estados<br/>redundantes| C[AFD Não-Mínimo]
    C -->|Minimização| D[AFD Mínimo]
    
    E["• Expressão Regular<br/>• Gramática Regular"] --> A
    
    style A fill:#e1f5ff
    style D fill:#c8e6c9
```

## 💡 Conceitos-chave

### Construção de Subconjuntos
- **Converte** AFND em AFD
- Estados do AFD = **conjuntos** de estados do AFND
- AFD resultante pode ser **grande** (até 2^n estados)
- **Sempre** produz um AFD equivalente

### Minimização
- **Otimiza** AFD removendo redundância
- Baseado em **equivalência** de estados
- AFD mínimo é **único** (a menos de renomeação)
- **Não muda** a linguagem reconhecida

## 🧮 Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| AFND → AFD | O(2^n × \|Σ\|) | O(2^n) |
| Minimização | O(n² × \|Σ\|) | O(n²) |

onde n = número de estados do AFND

## 📖 Aplicações Práticas

- **Compiladores**: Minimizar tabelas de analisadores léxicos
- **Processamento de texto**: Otimizar motores de regex
- **Verificação formal**: Comparar autômatos (minimização canônica)
- **Hardware**: Reduzir circuitos de controle

## 🔍 Por que Minimizar?

1. **Eficiência**: Menos estados = menos memória, processamento mais rápido
2. **Comparação**: AFDs mínimos são únicos (isomorfos)
3. **Clareza**: Mais fácil de entender e analisar
4. **Custo**: Em hardware, cada estado tem um custo físico

## 🎯 Teorema de Myhill-Nerode

**Teorema**: Para toda linguagem regular L, existe um único (a menos de isomorfismo) AFD mínimo que reconhece L.

**Corolário**: Dois AFDs minimizados que reconhecem a mesma linguagem são isomorfos.

Isso permite **testar equivalência** de autômatos:
1. Minimizar ambos
2. Comparar estruturas
3. Se isomorfos → linguagens iguais
