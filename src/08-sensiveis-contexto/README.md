# Gramáticas Sensíveis ao Contexto

Este diretório contém implementação de um Autômato Linearmente Limitado (LBA) que reconhece linguagens sensíveis ao contexto.

## 📚 Conteúdo

- **gramatica_sensivel.c** - LBA que reconhece aⁿbⁿcⁿ

## 🎯 Objetivos de Aprendizado

- Entender linguagens sensíveis ao contexto
- Compreender Autômatos Linearmente Limitados
- Reconhecer limitações de linguagens livres de contexto

---

## Gramáticas Sensíveis ao Contexto (gramatica_sensivel.c)

### O que são Linguagens Sensíveis ao Contexto?

**Linguagens Sensíveis ao Contexto (LSC)** são mais poderosas que linguagens livres de contexto, mas menos que linguagens recursivamente enumeráveis.

**Características**:
- Regras podem depender do **contexto** ao redor
- Reconhecidas por **Autômatos Linearmente Limitados (LBA)**
- Sempre **decidíveis** (sempre param)

```mermaid
graph TD
    A[Linguagens<br/>Regulares] --> B[Linguagens Livres<br/>de Contexto]
    B --> C[Linguagens Sensíveis<br/>ao Contexto]
    C --> D[Linguagens<br/>Recursivamente<br/>Enumeráveis]
    
    E[AFD/AFND] -.-> A
    F[Autômato<br/>com Pilha] -.-> B
    G[Autômato<br/>Linearmente<br/>Limitado] -.-> C
    H[Máquina<br/>de Turing] -.-> D
    
    style C fill:#c8e6c9
    style G fill:#c8e6c9
```

### Linguagem Exemplo: aⁿbⁿcⁿ

```
L = { aⁿbⁿcⁿ | n ≥ 1 }
  = {abc, aabbcc, aaabbbccc, ...}
```

**Por que não é livre de contexto?**
- Precisa contar **três** grupos independentes
- Autômato com Pilha tem apenas **uma pilha**
- Não consegue "lembrar" de dois contadores simultaneamente

```mermaid
flowchart TD
    A["aⁿbⁿcⁿ"] --> B{Livre de<br/>Contexto?}
    B -->|Não| C[Precisa contar<br/>3 grupos]
    C --> D[AP tem apenas<br/>1 pilha]
    D --> E[❌ Impossível com AP]
    E --> F[✓ Possível com LBA]
    
    style E fill:#ffcdd2
    style F fill:#c8e6c9
```

### Gramática Sensível ao Contexto

```
S  → aSBC | aBC
CB → BC
aB → ab
bB → bb
bC → bc
cC → cc
```

**Observação**: A regra `CB → BC` depende do **contexto** (C seguido de B).

#### Derivação de "aabbcc"

```
S ⇒ aSBC
  ⇒ aaBCBC
  ⇒ aaBBCC    (aplica CB → BC)
  ⇒ aabBCC    (aplica aB → ab)
  ⇒ aabbCC    (aplica bB → bb)
  ⇒ aabbcC    (aplica bC → bc)
  ⇒ aabbcc    (aplica cC → cc)
```

### Autômato Linearmente Limitado (LBA)

Um **LBA** é uma Máquina de Turing com uma restrição:
- O cabeçote **não pode sair** dos limites da entrada
- Espaço disponível: O(n), onde n = tamanho da entrada
- **Linearmente limitado** ao tamanho da entrada

```mermaid
graph TD
    A[Máquina de Turing] --> B{Restrição?}
    B -->|Cabeçote limitado<br/>à entrada| C[Autômato<br/>Linearmente<br/>Limitado LBA]
    B -->|Sem restrições| D[Máquina de<br/>Turing completa]
    
    E[Linguagens<br/>Sensíveis ao<br/>Contexto] -.-> C
    F[Linguagens<br/>Recursivamente<br/>Enumeráveis] -.-> D
    
    style C fill:#c8e6c9
```

### Algoritmo de Marcação para aⁿbⁿcⁿ

**Estratégia**: Marcar um 'a', um 'b' e um 'c' por vez, verificando se sobraram símbolos não marcados.

```mermaid
flowchart TD
    A[Início] --> B[Busca 'a' não marcado]
    B --> C{Encontrou 'a'?}
    C -->|Sim| D[Marca 'a' como 'X']
    C -->|Não| E{Todos marcados?}
    D --> F[Busca 'b' não marcado]
    F --> G{Encontrou 'b'?}
    G -->|Sim| H[Marca 'b' como 'Y']
    G -->|Não| I[✗ REJEITA]
    H --> J[Busca 'c' não marcado]
    J --> K{Encontrou 'c'?}
    K -->|Sim| L[Marca 'c' como 'Z']
    K -->|Não| I
    L --> M[Volta ao início]
    M --> B
    E -->|Sim| N[✓ ACEITA]
    E -->|Não| I
    
    style A fill:#e1f5ff
    style N fill:#c8e6c9
    style I fill:#ffcdd2
```

### Exemplo de Execução: "aabbcc"

| Passo | Fita | Descrição |
|-------|------|-----------|
| 0 | [aabbcc] | Inicial |
| 1 | [Xabbcc] | Marca primeiro 'a' |
| 2 | [XaYbcc] | Marca primeiro 'b' |
| 3 | [XaYbZc] | Marca primeiro 'c' |
| 4 | [XaYbZc] | Volta ao início |
| 5 | [XXYbZc] | Marca segundo 'a' |
| 6 | [XXYYZc] | Marca segundo 'b' |
| 7 | [XXYYZZ] | Marca segundo 'c' |
| 8 | [XXYYZZ] | Verifica: todos marcados |
| 9 | - | **ACEITA** ✓ |

```mermaid
sequenceDiagram
    participant F as Fita
    participant L as LBA
    
    Note over F: aabbcc
    L->>F: Marca a → X
    Note over F: Xabbcc
    L->>F: Marca b → Y
    Note over F: XaYbcc
    L->>F: Marca c → Z
    Note over F: XaYbZc
    L->>F: Volta ao início
    L->>F: Marca a → X
    Note over F: XXYbZc
    L->>F: Marca b → Y
    Note over F: XXYYZc
    L->>F: Marca c → Z
    Note over F: XXYYZZ
    L->>F: Verifica completo
    Note over L: ACEITA ✓
```

### Estados do LBA

```
q0 - busca próximo 'a' não marcado
q1 - encontrou 'a', busca 'b'
q2 - encontrou 'b', busca 'c'
q3 - encontrou 'c', volta ao início
q4 - estado de aceitação
```

```mermaid
stateDiagram-v2
    [*] --> q0
    q0 --> q1 : encontra 'a'<br/>marca como 'X'
    q1 --> q2 : encontra 'b'<br/>marca como 'Y'
    q2 --> q3 : encontra 'c'<br/>marca como 'Z'
    q3 --> q0 : volta ao início
    q0 --> q4 : todos marcados
    q4 --> [*]
    
    note right of q0
        Busca 'a' não marcado
    end note
    note right of q4
        Aceitação: todos<br/>os símbolos foram<br/>marcados
    end note
```

### Para Executar

```bash
make bin/gramatica_sensivel
./bin/gramatica_sensivel
```

### Exemplo de Saída

```
Autômato Linearmente Limitado (LBA)
L = { aⁿbⁿcⁿ | n >= 1 }

Palavra: "aabbcc"
    [aabbcc]  pos=0
    [Xabbcc]  pos=1  marca 'a'
    [XaYbcc]  pos=3  marca 'b'
    [XaYbZc]  pos=5  marca 'c'
    [XaYbZc]  pos=0  volta ao início
    [XXYbZc]  pos=2  marca 'a'
    [XXYYZc]  pos=4  marca 'b'
    [XXYYZZ]  pos=6  marca 'c'
    Resultado: ACEITA ✓

Palavra: "aabcc"
    [aabcc]   pos=0
    [Xabcc]   pos=1  marca 'a'
    [XaYcc]   pos=3  marca 'b'
    [XaYcZ]   pos=5  marca 'c'
    [XaYcZ]   pos=0  volta ao início
    [XXYcZ]   pos=2  marca 'a'
    [XXYcZ]   pos=3  não encontrou 'b'
    Resultado: REJEITA ✗
```

---

## 💡 Conceitos-chave

### Linguagens Sensíveis ao Contexto
- **Regras dependem** do contexto ao redor
- **Mais poderosas** que livres de contexto
- **Sempre decidíveis** (sempre param)
- **Espaço linear** ao tamanho da entrada

### Autômato Linearmente Limitado
- Máquina de Turing **restrita**
- Cabeçote **não pode sair** dos limites da entrada
- Espaço: **O(n)** onde n = tamanho da entrada
- Reconhece exatamente as LSC

### Forma Normal de Kuroda

Regras de gramáticas sensíveis ao contexto:
```
αAβ → αγβ
```

Onde:
- A é um não-terminal
- α, β são contextos
- γ é não-vazio
- |α| + |γ| + |β| ≥ |α| + |A| + |β|

**Restrição**: Produções **não diminuem** o comprimento da forma sentencial.

## 🔗 Hierarquia de Chomsky Completa

```mermaid
graph TD
    A["Tipo 3: Regulares<br/>A → aB | a"] --> B["Tipo 2: Livres de Contexto<br/>A → γ"]
    B --> C["Tipo 1: Sensíveis ao Contexto<br/>αAβ → αγβ"]
    C --> D["Tipo 0: Recursivamente Enumeráveis<br/>α → β"]
    
    E[AFD/AFND] -.-> A
    F[AP] -.-> B
    G[LBA] -.-> C
    H[MT] -.-> D
    
    I["Σ*, +, ·"] -.-> A
    J["Parênteses,<br/>aⁿbⁿ"] -.-> B
    K["aⁿbⁿcⁿ"] -.-> C
    L["Problema da<br/>Parada"] -.-> D
    
    style C fill:#c8e6c9
    style G fill:#c8e6c9
```

## 📖 Exemplos de Linguagens

### Tipo 3 (Regulares)
- `(a|b)*`
- Números pares
- Identificadores

### Tipo 2 (Livres de Contexto)
- `{ aⁿbⁿ | n ≥ 0 }`
- Parênteses balanceados
- Expressões aritméticas

### Tipo 1 (Sensíveis ao Contexto)
- `{ aⁿbⁿcⁿ | n ≥ 1 }`
- `{ ww | w ∈ {a,b}* }` (duplicação)
- Linguagens com múltiplas dependências

### Tipo 0 (Recursivamente Enumeráveis)
- Problema da Parada
- Teorema de Gödel
- Funções parciais computáveis

## 🧮 Propriedades

| Propriedade | LSC |
|-------------|-----|
| Decidibilidade | **Sempre decidível** |
| Problema da Pertinência | **Decidível** (mas PSPACE-completo) |
| Fechamento sob União | ✓ Sim |
| Fechamento sob Concatenação | ✓ Sim |
| Fechamento sob Fecho de Kleene | ✓ Sim |
| Fechamento sob Complemento | ✓ Sim |
| Fechamento sob Interseção | ✓ Sim |

## 🔍 Por que é importante?

### Compiladores
Algumas verificações semânticas são sensíveis ao contexto:
- Declaração antes do uso
- Tipos compatíveis em atribuições
- Escopo de variáveis

### Linguagens Naturais
Muitas regras gramaticais dependem do contexto:
- Concordância nominal
- Concordância verbal
- Referências anafóricas

### Bioinformática
Padrões em DNA/RNA podem ter dependências múltiplas.

## ⚠️ Complexidade

- **Problema da Pertinência**: PSPACE-completo
- Muito mais **difícil** que linguagens livres de contexto
- Geralmente **impraticável** para aplicações reais
- Compiladores usam **aproximações** (verificação em fases)
