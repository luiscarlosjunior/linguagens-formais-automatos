# Capítulo 3 — Autômato Finito Determinístico e Não Determinístico

## 3.1 Introdução e Contexto Histórico

O estudo dos autômatos finitos remonta às primeiras tentativas de formalizar o
comportamento de sistemas com memória limitada. Em 1943, Warren McCulloch e
Walter Pitts propuseram um modelo matemático para redes neurais artificiais,
demonstrando que redes de neurônios idealizados — com comportamento binário de
ativação — eram capazes de computar funções lógicas arbitrárias (McCulloch &
Pitts, 1943). Esse modelo, embora voltado à neurofisiologia, continha em sua
essência a noção de estados finitos e transições determinísticas que viria a
fundamentar a teoria dos autômatos.

Em 1956, Stephen Cole Kleene estabeleceu uma conexão profunda entre os modelos
de McCulloch-Pitts e as linguagens formais ao demonstrar que a classe de eventos
(linguagens) representáveis por autômatos finitos coincidia exatamente com a
classe de linguagens descritas por expressões regulares (Kleene, 1956). Esse
resultado, conhecido como **Teorema de Kleene**, é um dos pilares da teoria da
computação e será explorado em detalhes no Capítulo 4.

O marco definitivo na formalização dos autômatos finitos veio com o trabalho
seminal de Michael O. Rabin e Dana Scott, publicado em 1959, intitulado *"Finite
Automata and Their Decision Problems"*. Nesse artigo, Rabin e Scott introduziram
formalmente os conceitos de autômato finito determinístico (AFD) e autômato
finito não determinístico (AFND), demonstraram a equivalência de poder
computacional entre ambos e estabeleceram diversas propriedades de decidibilidade
para as linguagens regulares (Rabin & Scott, 1959). Esse trabalho rendeu aos
autores o **Prêmio Turing de 1976**, o mais prestigioso reconhecimento da
ciência da computação.

Os autômatos finitos constituem o modelo mais simples de computação na
**Hierarquia de Chomsky**: reconhecem exatamente as linguagens regulares (Tipo 3)
e possuem memória estritamente finita, representada pelo conjunto de estados.
Apesar de sua simplicidade teórica, os autômatos finitos possuem aplicações
práticas extensas — de analisadores léxicos em compiladores a controladores de
protocolos de comunicação, passando por sistemas de busca textual e verificação
de hardware (Hopcroft, Ullman & Motwani, 2002; Sipser, 2012).

Como observa Menezes (2008), a importância pedagógica dos autômatos finitos
reside no fato de que eles introduzem, de forma acessível, conceitos centrais
que reaparecerão em modelos mais poderosos: estados, transições, aceitação,
determinismo versus não determinismo e equivalência entre modelos.

---

## 3.2 Autômato Finito Determinístico (AFD)

### 3.2.1 Definição Formal

Um **Autômato Finito Determinístico** (AFD) é uma 5-tupla:

```
M = (Q, Σ, δ, q₀, F)
```

onde:

| Componente | Descrição |
|---|---|
| **Q** | Conjunto finito e não vazio de **estados** |
| **Σ** | **Alfabeto** de entrada (conjunto finito de símbolos) |
| **δ** | **Função de transição**: δ : Q × Σ → Q |
| **q₀** | **Estado inicial**, com q₀ ∈ Q |
| **F** | Conjunto de **estados de aceitação** (ou finais), com F ⊆ Q |

A propriedade fundamental que torna o autômato *determinístico* é a natureza da
função de transição δ: para **cada** par (estado, símbolo) existe **exatamente
uma** transição definida. Não há ambiguidade — dado o estado atual e o símbolo
lido, o próximo estado é univocamente determinado.

### 3.2.2 Função de Transição Estendida

A função de transição δ opera sobre um único símbolo. Para processar cadeias
inteiras, define-se a **função de transição estendida** δ̂ : Q × Σ* → Q,
recursivamente:

1. **Base:** δ̂(q, ε) = q, para todo q ∈ Q
2. **Passo:** δ̂(q, wa) = δ(δ̂(q, w), a), para todo q ∈ Q, w ∈ Σ*, a ∈ Σ

Intuitivamente, δ̂(q, w) é o estado alcançado após processar toda a cadeia w a
partir do estado q.

### 3.2.3 Linguagem Aceita por um AFD

A **linguagem reconhecida** (ou aceita) por um AFD M é definida como:

```
L(M) = { w ∈ Σ* | δ̂(q₀, w) ∈ F }
```

Isto é, L(M) é o conjunto de todas as cadeias sobre Σ que, partindo do estado
inicial q₀, levam o autômato a um estado de aceitação.

Uma cadeia w é **rejeitada** se δ̂(q₀, w) ∉ F.

### 3.2.4 Exemplo Detalhado: Cadeias Binárias Terminadas em "01"

Desejamos construir um AFD que aceite exatamente as cadeias binárias (sobre
Σ = {0, 1}) que terminam com a subcadeia "01".

**Definição da 5-tupla:**

```
M = (Q, Σ, δ, q₀, F)
```

- **Q** = {q₀, q₁, q₂}
- **Σ** = {0, 1}
- **q₀** = q₀ (estado inicial)
- **F** = {q₂}

Significado dos estados:

- **q₀** — Estado inicial; nenhum progresso em direção ao sufixo "01". O último
  símbolo lido não foi '0' (ou nenhum símbolo foi lido).
- **q₁** — O último símbolo lido foi '0'. Estamos "a meio caminho" de
  reconhecer "01".
- **q₂** — O sufixo "01" acabou de ser completado. Estado de aceitação.

**Função de transição δ:**

| Estado | Entrada 0 | Entrada 1 |
|--------|-----------|-----------|
| q₀     | q₁        | q₀        |
| q₁     | q₁        | q₂        |
| q₂     | q₁        | q₀        |

**Diagrama de estados:**

```
              0          1          0
        ┌───────── q₀ ─────────┐    │
        │      ↗   ↑           │    │
        ▼     1    │ 1         ▼    │
       q₁ ────────────────▶ ((q₂)) │
        ↑                      │    │
        │          0           │    │
        └──────────────────────┘    │
        │                           │
        └───────────────────────────┘
              0 (laço em q₁)
```

Representação textual mais precisa:

```
    ──▶ (q₀) ──0──▶ (q₁) ──1──▶ ((q₂))
          │  ◀──1──  │  ◀──0──   │
          └──1──┐    └──0──┐     │
               ↓         ↓      │
              q₀        q₁      │
                                 │
          q₂ ──0──▶ q₁           │
          q₂ ──1──▶ q₀           │
```

Para melhor clareza, as transições são:

- q₀ com '0' → q₁ (começou a ver o padrão "0...")
- q₀ com '1' → q₀ (nenhum progresso)
- q₁ com '0' → q₁ (outro '0'; ainda aguardando '1')
- q₁ com '1' → q₂ (completou "01"! aceita)
- q₂ com '0' → q₁ (novo '0' pode iniciar outro "01")
- q₂ com '1' → q₀ (perdeu o progresso)

**Rastreamento da execução:**

*Entrada: w = "1001"*

| Passo | Estado Atual | Símbolo Lido | Próximo Estado |
|-------|-------------|-------------|----------------|
| 1     | q₀          | 1           | q₀             |
| 2     | q₀          | 0           | q₁             |
| 3     | q₁          | 0           | q₁             |
| 4     | q₁          | 1           | q₂             |

Estado final: q₂ ∈ F → **aceita** ✓

*Entrada: w = "0100"*

| Passo | Estado Atual | Símbolo Lido | Próximo Estado |
|-------|-------------|-------------|----------------|
| 1     | q₀          | 0           | q₁             |
| 2     | q₁          | 1           | q₂             |
| 3     | q₂          | 0           | q₁             |
| 4     | q₁          | 0           | q₁             |

Estado final: q₁ ∉ F → **rejeita** ✗

*Entrada: w = "01"*

| Passo | Estado Atual | Símbolo Lido | Próximo Estado |
|-------|-------------|-------------|----------------|
| 1     | q₀          | 0           | q₁             |
| 2     | q₁          | 1           | q₂             |

Estado final: q₂ ∈ F → **aceita** ✓

*Entrada: w = ε (cadeia vazia)*

O autômato permanece em q₀. Como q₀ ∉ F → **rejeita** ✗

---

## 3.3 Autômato Finito Não Determinístico (AFND)

### 3.3.1 Definição Formal

Um **Autômato Finito Não Determinístico** (AFND) é uma 5-tupla:

```
M = (Q, Σ, δ, q₀, F)
```

onde:

| Componente | Descrição |
|---|---|
| **Q** | Conjunto finito e não vazio de estados |
| **Σ** | Alfabeto de entrada |
| **δ** | **Função de transição**: δ : Q × Σ → **P(Q)** |
| **q₀** | Estado inicial, com q₀ ∈ Q |
| **F** | Conjunto de estados de aceitação, com F ⊆ Q |

A diferença essencial em relação ao AFD reside na função de transição: δ mapeia
cada par (estado, símbolo) para um **subconjunto** de Q (elemento do conjunto
das partes P(Q)), e não para um único estado. Isso significa que:

- Para um dado par (q, a), pode haver **zero, uma ou múltiplas** transições
  possíveis.
- Se δ(q, a) = ∅, não existe transição para o símbolo a no estado q — aquele
  ramo da computação simplesmente "morre".
- Se |δ(q, a)| > 1, a computação se "ramifica" em múltiplos caminhos paralelos.

### 3.3.2 Semântica do Não Determinismo

O não determinismo pode ser compreendido por meio de três metáforas
equivalentes, conforme discutido por Sipser (2012):

1. **Paralelismo:** o autômato explora simultaneamente todos os caminhos de
   computação possíveis. Quando um símbolo oferece múltiplas transições, todas
   são seguidas em paralelo.

2. **Adivinhação:** o autômato sempre "adivinha" a transição correta. Se existe
   algum caminho que leva à aceitação, ele será encontrado.

3. **Árvore de computação:** cada ponto de não determinismo gera ramificações
   na árvore. A cadeia é aceita se **pelo menos um** ramo atinge um estado de
   aceitação.

**Critério de aceitação:** uma cadeia w é aceita por um AFND M se **existe pelo
menos um** caminho de computação partindo de q₀ que, após consumir toda a cadeia
w, termina em um estado q ∈ F. Uma cadeia é rejeitada somente se **todos** os
caminhos possíveis levam a estados não finais ou "morrem" (transições
indefinidas).

Formalmente, a **função de transição estendida** δ̂ : Q × Σ* → P(Q) é definida
como:

1. **Base:** δ̂(q, ε) = {q}
2. **Passo:** δ̂(q, wa) = ⋃ { δ(p, a) | p ∈ δ̂(q, w) }

E a linguagem aceita é:

```
L(M) = { w ∈ Σ* | δ̂(q₀, w) ∩ F ≠ ∅ }
```

### 3.3.3 Exemplo Detalhado: Cadeias Contendo "01" como Subcadeia

Construiremos um AFND que aceita cadeias binárias que contêm "01" como
subcadeia em qualquer posição. Este exemplo ilustra como o não determinismo
simplifica significativamente o projeto do autômato.

**Definição da 5-tupla:**

```
M = (Q, Σ, δ, q₀, F)
```

- **Q** = {q₀, q₁, q₂}
- **Σ** = {0, 1}
- **q₀** = q₀
- **F** = {q₂}

Significado dos estados:

- **q₀** — Ainda não começamos a rastrear "01". O autômato "adivinha" quando
  o padrão começa.
- **q₁** — Lemos o '0' que pode ser o início de "01".
- **q₂** — O padrão "01" foi encontrado. Estado de aceitação.

**Função de transição δ:**

| Estado | Entrada 0   | Entrada 1 |
|--------|-------------|-----------|
| q₀     | {q₀, q₁}   | {q₀}     |
| q₁     | ∅           | {q₂}     |
| q₂     | {q₂}       | {q₂}     |

**Diagrama de estados:**

```
                    0, 1
                   ┌───┐
                   │   ▼
         ──▶ (q₀) ──0──▶ (q₁) ──1──▶ ((q₂))
               │                        │   ▲
               └──1──┐                  └───┘
                     ▼                  0, 1
                    q₀
```

Observe a elegância do não determinismo: no estado q₀, ao ler '0', o autômato
pode **simultaneamente** permanecer em q₀ (apostando que o padrão ainda não
começou) e ir para q₁ (apostando que este '0' é o início de "01"). Não
precisamos decidir — o não determinismo explora ambas as possibilidades.

**Comparação com o projeto determinístico:**

Um AFD equivalente necessitaria rastrear explicitamente se o padrão "01" já foi
visto, resultando em uma lógica de transições mais complexa. No AFND, a
"adivinhação" de quando o padrão começa torna o projeto natural e direto.

**Rastreamento da execução (w = "101"):**

A computação se desenvolve como uma árvore:

```
                      q₀        (lê '1')
                      │
                     {q₀}       (lê '0')
                    ╱    ╲
                  q₀      q₁    (lê '1')
                  │        │
                 {q₀}    {q₂}
```

Conjunto de estados após processar "101": {q₀, q₂}

Como q₂ ∈ F e {q₀, q₂} ∩ F = {q₂} ≠ ∅ → **aceita** ✓

**Rastreamento (w = "10"):**

```
                      q₀        (lê '1')
                      │
                     {q₀}       (lê '0')
                    ╱    ╲
                  q₀      q₁
```

Conjunto final: {q₀, q₁}. Como {q₀, q₁} ∩ F = ∅ → **rejeita** ✗

---

## 3.4 AFND com Transições Vazias (ε-AFND)

### 3.4.1 Definição Formal

Uma extensão natural do AFND permite **transições espontâneas** — transições que
ocorrem sem consumir nenhum símbolo da entrada. Tais transições são chamadas de
**ε-transições** (ou transições vazias).

Um **ε-AFND** é uma 5-tupla:

```
M = (Q, Σ, δ, q₀, F)
```

onde a função de transição possui o domínio expandido:

```
δ : Q × (Σ ∪ {ε}) → P(Q)
```

Para cada estado q ∈ Q, δ(q, ε) indica o conjunto de estados alcançáveis a
partir de q **sem ler nenhum símbolo** da fita de entrada.

### 3.4.2 Fecho-ε (ε-closure)

O conceito central para o tratamento de ε-transições é o **fecho-ε** (ou
ε-closure), definido para um estado q ∈ Q como:

```
FECHO-ε(q) = { p ∈ Q | p é alcançável a partir de q
               usando zero ou mais ε-transições }
```

Note que q ∈ FECHO-ε(q) sempre (zero ε-transições).

Para um conjunto de estados S ⊆ Q:

```
FECHO-ε(S) = ⋃ { FECHO-ε(q) | q ∈ S }
```

O fecho-ε pode ser calculado por busca em largura ou profundidade no grafo de
ε-transições.

### 3.4.3 Função de Transição Estendida

A função de transição estendida δ̂ : Q × Σ* → P(Q) para um ε-AFND é definida
recursivamente:

1. **Base:** δ̂(q, ε) = FECHO-ε(q)
2. **Passo:** δ̂(q, wa) = FECHO-ε( ⋃ { δ(p, a) | p ∈ δ̂(q, w) } )

E a linguagem aceita:

```
L(M) = { w ∈ Σ* | δ̂(q₀, w) ∩ F ≠ ∅ }
```

### 3.4.4 Exemplo: Aceitar Cadeias de "a"s ou "b"s (Mas Não Misturadas)

Considere a linguagem L = { aⁿ | n ≥ 0 } ∪ { bⁿ | n ≥ 0 } sobre Σ = {a, b}.

**ε-AFND:**

- **Q** = {q₀, q₁, q₂}
- **Σ** = {a, b}
- **q₀** = q₀
- **F** = {q₁, q₂}

**Função de transição:**

| Estado | a     | b     | ε         |
|--------|-------|-------|-----------|
| q₀     | ∅     | ∅     | {q₁, q₂} |
| q₁     | {q₁}  | ∅     | ∅         |
| q₂     | ∅     | {q₂}  | ∅         |

**Diagrama:**

```
                        a
                      ┌───┐
                      │   ▼
         ──▶ (q₀) ──ε──▶ ((q₁))
               │
               └──ε──▶ ((q₂))
                        │   ▲
                        └───┘
                          b
```

O estado q₀ usa ε-transições para "escolher" não deterministicamente se
processará apenas 'a's (via q₁) ou apenas 'b's (via q₂). Essa escolha ocorre
antes mesmo de ler qualquer símbolo.

**Cálculo do FECHO-ε:**

- FECHO-ε(q₀) = {q₀, q₁, q₂}
- FECHO-ε(q₁) = {q₁}
- FECHO-ε(q₂) = {q₂}

**Rastreamento (w = "aab"):**

- δ̂(q₀, ε) = FECHO-ε(q₀) = {q₀, q₁, q₂}
- Lê 'a': para cada p ∈ {q₀, q₁, q₂}, calcule δ(p, a):
  - δ(q₀, a) = ∅, δ(q₁, a) = {q₁}, δ(q₂, a) = ∅
  - União: {q₁}. FECHO-ε({q₁}) = {q₁}
- Lê 'a': δ(q₁, a) = {q₁}. FECHO-ε = {q₁}
- Lê 'b': δ(q₁, b) = ∅.

Conjunto final: ∅. Como ∅ ∩ F = ∅ → **rejeita** ✗ (correto: "aab" mistura 'a' e 'b')

**Rastreamento (w = "bb"):**

- δ̂(q₀, ε) = {q₀, q₁, q₂}
- Lê 'b': δ(q₀, b) = ∅, δ(q₁, b) = ∅, δ(q₂, b) = {q₂}
  - FECHO-ε({q₂}) = {q₂}
- Lê 'b': δ(q₂, b) = {q₂}. FECHO-ε = {q₂}

Conjunto final: {q₂}. Como {q₂} ∩ F = {q₂} ≠ ∅ → **aceita** ✓

---

## 3.5 Equivalência entre AFD e AFND

### 3.5.1 O Teorema Fundamental

Um dos resultados mais importantes da teoria dos autômatos, demonstrado
originalmente por Rabin e Scott (1959), é a **equivalência de poder
computacional** entre AFDs e AFNDs:

> **Teorema (Rabin & Scott, 1959):** Para todo AFND N, existe um AFD D tal que
> L(D) = L(N). Reciprocamente, para todo AFD D, existe um AFND N tal que
> L(N) = L(D).

A segunda direção é trivial: todo AFD é, por definição, um caso especial de
AFND em que |δ(q, a)| = 1 para todo q ∈ Q e a ∈ Σ. Basta reescrever cada
transição δ(q, a) = p como δ(q, a) = {p}.

### 3.5.2 Intuição da Construção de Subconjuntos

A direção não trivial — converter um AFND em AFD — utiliza a **construção de
subconjuntos** (ou *subset construction*). A ideia intuitiva é:

1. Os estados do AFD equivalente são **subconjuntos** de estados do AFND
   original. Cada estado do AFD representa o conjunto de todos os estados em que
   o AFND poderia estar após processar a entrada até aquele ponto.

2. O estado inicial do AFD é {q₀} (ou FECHO-ε({q₀}) no caso de ε-AFND).

3. A transição do AFD é calculada aplicando a transição do AFND a cada estado
   do subconjunto e fazendo a união dos resultados.

4. Um estado do AFD é de aceitação se o subconjunto contém pelo menos um estado
   de aceitação do AFND.

Como o AFND tem |Q| = n estados, o AFD resultante pode ter até **2ⁿ** estados
(um para cada subconjunto de Q). Na prática, muitos desses estados podem ser
inalcançáveis, e o AFD efetivo costuma ser muito menor.

> A apresentação formal e detalhada do algoritmo de construção de subconjuntos,
> com exemplos completos e prova de correção, será desenvolvida no
> **Capítulo 5 — Propriedades das Linguagens Regulares**.

### 3.5.3 Equivalência com ε-AFND

O resultado de equivalência estende-se naturalmente aos ε-AFNDs:

```
AFD  ⊆  AFND  ⊆  ε-AFND
```

No sentido de que todo AFD é um AFND (trivialmente) e todo AFND é um ε-AFND
(com δ(q, ε) = ∅ para todo q). Porém, no sentido inverso, para todo ε-AFND
existe um AFD equivalente. Portanto, as três classes reconhecem exatamente o
mesmo conjunto de linguagens: as **linguagens regulares**.

---

## 3.6 Representações de Autômatos Finitos

### 3.6.1 Tabela de Transição

A tabela de transição é a representação mais direta e compacta. Para um AFD,
cada célula contém exatamente um estado. Para um AFND, cada célula contém um
conjunto de estados (possivelmente vazio).

**Convenções:**

- O estado inicial é indicado por uma seta → ou pelo símbolo ▶
- Estados de aceitação são indicados por asterisco (*) ou duplo círculo

Exemplo (AFD da Seção 3.2.4):

```
           │   0   │   1
    ───────┼───────┼──────
    → q₀   │  q₁   │  q₀
      q₁   │  q₁   │  q₂
    * q₂   │  q₁   │  q₀
```

### 3.6.2 Diagrama de Estados

O **diagrama de estados** (ou diagrama de transição) é uma representação gráfica
na forma de um **grafo dirigido**:

- **Nós** representam estados. São desenhados como círculos.
- **Arestas dirigidas** (setas) representam transições, rotuladas com o símbolo
  de entrada correspondente.
- O **estado inicial** é identificado por uma seta sem origem apontando para ele.
- **Estados de aceitação** são desenhados com **duplo círculo**.

**Como construir um diagrama a partir de uma tabela:**

1. Desenhe um nó (círculo) para cada estado q ∈ Q.
2. Para cada entrada δ(q, a) = p na tabela, desenhe uma seta de q para p
   rotulada com a.
3. Se múltiplos símbolos causam a mesma transição (ex: δ(q, 0) = δ(q, 1) = p),
   combine-os em uma única seta com rótulo "0, 1".
4. Marque q₀ com a seta de entrada e os estados em F com duplo círculo.

**Como ler um diagrama:**

1. Comece no estado indicado pela seta de entrada (estado inicial).
2. Para cada símbolo da cadeia de entrada (da esquerda para a direita), siga a
   seta correspondente ao símbolo.
3. Após consumir toda a cadeia, verifique se o estado atual é de aceitação
   (duplo círculo).
   - Se sim: a cadeia é **aceita**.
   - Se não: a cadeia é **rejeitada**.

### 3.6.3 Descrição Formal (5-tupla)

A representação como 5-tupla M = (Q, Σ, δ, q₀, F) é a mais precisa e adequada
para provas matemáticas. As demais representações (tabela e diagrama) são
derivadas dela e usadas por conveniência de comunicação.

---

## 3.7 Problemas Clássicos

### 3.7.1 Cadeias com Número Par de 0s

**Linguagem:** L = { w ∈ {0, 1}* | w contém um número par de 0s }

Nota: zero é par, portanto ε ∈ L.

**AFD:**

- Q = {q₀, q₁}
- Σ = {0, 1}
- q₀ = q₀ (par de 0s vistos — inclui zero)
- F = {q₀}

**Tabela de transição:**

```
           │   0   │   1
    ───────┼───────┼──────
    →* q₀  │  q₁   │  q₀
       q₁  │  q₀   │  q₁
```

**Diagrama:**

```
              1             1
           ┌───┐         ┌───┐
           │   ▼         │   ▼
    ──▶ ((q₀)) ──0──▶  (q₁)
              ◀──0───
```

Lógica: q₀ significa "número par de 0s até agora" e q₁ significa "número ímpar".
Cada '0' alterna entre esses dois estados. Os '1' não afetam a contagem.

### 3.7.2 Representação Binária Divisível por 3

**Linguagem:** L = { w ∈ {0, 1}* | w, interpretada como número binário, é
divisível por 3 }

**Insight:** se o número representado até agora é n e lemos o dígito d, o novo
número é 2n + d. Portanto, o resto na divisão por 3 se atualiza como
(2n + d) mod 3.

**AFD:**

- Q = {q₀, q₁, q₂} — representando restos 0, 1, 2 (mod 3)
- Σ = {0, 1}
- q₀ = q₀ (resto 0)
- F = {q₀}

**Tabela de transição:**

```
           │    0    │    1
    ───────┼─────────┼─────────
    →* q₀  │   q₀    │   q₁
       q₁  │   q₂    │   q₀
       q₂  │   q₁    │   q₂
```

Verificação das transições (estado qᵢ representa resto i):

- δ(q₀, 0): (2·0 + 0) mod 3 = 0 → q₀
- δ(q₀, 1): (2·0 + 1) mod 3 = 1 → q₁
- δ(q₁, 0): (2·1 + 0) mod 3 = 2 → q₂
- δ(q₁, 1): (2·1 + 1) mod 3 = 0 → q₀
- δ(q₂, 0): (2·2 + 0) mod 3 = 1 → q₁
- δ(q₂, 1): (2·2 + 1) mod 3 = 2 → q₂

**Teste: w = "110" (decimal 6):**

q₀ →¹ q₁ →¹ q₀ →⁰ q₀ ∈ F → **aceita** ✓ (6 mod 3 = 0)

**Teste: w = "101" (decimal 5):**

q₀ →¹ q₁ →⁰ q₂ →¹ q₂ ∉ F → **rejeita** ✗ (5 mod 3 = 2)

### 3.7.3 Casamento de Padrões (Pattern Matching)

Autômatos finitos são a base teórica dos algoritmos de casamento de padrões
em texto. Dado um padrão P (cadeia fixa), construímos um AFD que aceita toda
cadeia que contém P como subcadeia. Esta é essencialmente a técnica utilizada
pelo utilitário `grep` e por analisadores léxicos em compiladores.

**Exercício proposto:** Construa um AFD sobre Σ = {a, b} que aceite todas as
cadeias contendo "aba" como subcadeia. Sugestão: utilize 4 estados que rastreiem
o progresso no casamento do padrão, de forma análoga ao algoritmo de
Knuth-Morris-Pratt (KMP).

**Exercício proposto:** Construa um AFND sobre Σ = {0, 1} que aceite cadeias
cujo terceiro símbolo a partir do final é '1'. Compare a complexidade com a de
um AFD equivalente. (Dica: o AFND requer apenas 4 estados, enquanto o AFD
mínimo requer 8.)

---

## 3.8 Exemplo em C

Os conceitos apresentados neste capítulo são ilustrados por implementações em
linguagem C disponíveis no diretório `src/03-automatos/`:

- **`afd.c`** — Implementação de um Autômato Finito Determinístico. O programa
  define a estrutura de dados para representar a 5-tupla (Q, Σ, δ, q₀, F),
  implementa a função de transição estendida δ̂ e verifica se cadeias fornecidas
  como entrada pertencem à linguagem reconhecida. O exemplo implementa o AFD
  para cadeias binárias terminadas em "01" (Seção 3.2.4).

- **`afnd.c`** — Implementação de um Autômato Finito Não Determinístico. O
  programa representa a função de transição como mapeamento para conjuntos de
  estados (utilizando bitmasks ou listas), implementa a exploração de todos os
  caminhos de computação possíveis e determina a aceitação conforme o critério
  existencial. O exemplo implementa o AFND para cadeias contendo "01" como
  subcadeia (Seção 3.3.3).

Essas implementações permitem ao estudante observar concretamente o
comportamento computacional de cada modelo e experimentar com diferentes
entradas.

---

## Referências

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de
Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Campus/Elsevier,
2002.

KLEENE, S. C. Representation of Events in Nerve Nets and Finite Automata. In:
SHANNON, C. E.; McCARTHY, J. (Eds.). **Automata Studies**. Princeton: Princeton
University Press, 1956. p. 3–42.

McCULLOCH, W. S.; PITTS, W. A Logical Calculus of the Ideas Immanent in Nervous
Activity. **Bulletin of Mathematical Biophysics**, v. 5, p. 115–133, 1943.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre:
Bookman, 2008.

RABIN, M. O.; SCOTT, D. Finite Automata and Their Decision Problems. **IBM
Journal of Research and Development**, v. 3, n. 2, p. 114–125, 1959.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage
Learning, 2012.
