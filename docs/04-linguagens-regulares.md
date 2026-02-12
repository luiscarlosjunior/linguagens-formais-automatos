# Capítulo 4 — Linguagens Regulares, Expressões Regulares e Gramática Regular

## 4.1 Introdução e Contexto Histórico

As **linguagens regulares** constituem a classe mais fundamental na hierarquia de Chomsky e representam o alicerce sobre o qual se erguem os demais níveis de complexidade da teoria da computação. Seu estudo formal remonta à década de 1950, quando o matemático Stephen Cole **Kleene** (1956) introduziu as **expressões regulares** como uma notação algébrica para descrever conjuntos de cadeias e demonstrou sua equivalência com os autômatos finitos propostos por McCulloch e Pitts (1943) e posteriormente formalizados por Rabin e Scott (1959). O resultado central de Kleene — hoje conhecido como **Teorema de Kleene** — estabelece que uma linguagem é regular se e somente se pode ser descrita por uma expressão regular, unificando assim duas perspectivas aparentemente distintas: a operacional (autômatos) e a denotacional (expressões).

Uma década mais tarde, Ken **Thompson** (1968) transpôs essa teoria para a prática ao construir o primeiro motor de expressões regulares eficiente, incorporado ao editor de texto QED e, posteriormente, ao utilitário `grep` do sistema Unix. A construção de Thompson — que converte sistematicamente uma expressão regular em um autômato finito não determinístico com transições-ε (AFND-ε) — permanece, até hoje, como a base dos motores de regex em ferramentas como `sed`, `awk`, `lex` e nas bibliotecas de linguagens de programação modernas.

Do ponto de vista da engenharia de compiladores, as linguagens regulares desempenham um papel insubstituível: a **análise léxica** (primeira fase da compilação) utiliza autômatos finitos derivados de expressões regulares para decompor o código-fonte em *tokens* — identificadores, palavras reservadas, literais numéricos, operadores e delimitadores (Aho, Lam, Sethi & Ullman, 2006). Ferramentas clássicas como `lex` e `flex` automatizam esse processo, recebendo especificações em expressões regulares e gerando código C para o autômato correspondente.

> *"Regular expressions are one of the oldest and most widely used tools in computer science — their elegance lies in the perfect correspondence between a simple algebraic notation and a minimal model of computation."*
> — Hopcroft, Ullman & Motwani, *Introduction to Automata Theory, Languages, and Computation* (2006)

---

## 4.2 Linguagens Regulares

### 4.2.1 Definição Formal

**Definição.** Uma linguagem *L* ⊆ Σ\* é **regular** se e somente se existe algum **autômato finito determinístico** (AFD) *M* = (Q, Σ, δ, q₀, F) tal que L(M) = L.

De maneira equivalente, *L* é regular se e somente se:

1. Existe um **AFD** que reconhece *L*; ou
2. Existe um **AFND** que reconhece *L*; ou
3. Existe um **AFND-ε** que reconhece *L*; ou
4. Existe uma **expressão regular** *r* tal que L(r) = *L*; ou
5. Existe uma **gramática regular** (tipo 3) *G* tal que L(G) = *L*.

A equivalência entre todas essas caracterizações é um dos resultados mais elegantes da teoria das linguagens formais e será explorada nas seções seguintes.

### 4.2.2 Propriedades de Fechamento

As linguagens regulares possuem notáveis **propriedades de fechamento**: operações aplicadas a linguagens regulares produzem, invariavelmente, linguagens regulares. Essas propriedades são fundamentais tanto para provas teóricas quanto para a construção prática de autômatos mais complexos a partir de componentes simples.

Sejam *L₁* e *L₂* linguagens regulares sobre o alfabeto Σ. Então as seguintes linguagens também são regulares:

| Operação | Definição | Fechamento |
|---|---|---|
| **União** | L₁ ∪ L₂ = { w \| w ∈ L₁ ou w ∈ L₂ } | ✔ Regular |
| **Concatenação** | L₁ · L₂ = { xy \| x ∈ L₁ e y ∈ L₂ } | ✔ Regular |
| **Estrela de Kleene** | L₁\* = { ε } ∪ L₁ ∪ L₁·L₁ ∪ L₁·L₁·L₁ ∪ … | ✔ Regular |
| **Complemento** | L̄₁ = Σ\* − L₁ | ✔ Regular |
| **Interseção** | L₁ ∩ L₂ = { w \| w ∈ L₁ e w ∈ L₂ } | ✔ Regular |
| **Diferença** | L₁ − L₂ = { w \| w ∈ L₁ e w ∉ L₂ } | ✔ Regular |
| **Reverso** | Lᴿ = { wᴿ \| w ∈ L₁ } | ✔ Regular |

#### Justificativas e Intuições

**União (L₁ ∪ L₂).** Dados AFDs *M₁* e *M₂* reconhecendo *L₁* e *L₂*, construímos um AFND que, a partir de um novo estado inicial, realiza transições-ε para os estados iniciais de *M₁* e *M₂*. Aceita se qualquer um dos ramos aceita. Alternativamente, utiliza-se a **construção do produto cartesiano**: o novo AFD tem estados Q₁ × Q₂, e o estado (p, q) é final se p ∈ F₁ **ou** q ∈ F₂.

**Concatenação (L₁ · L₂).** Conecta-se cada estado final de *M₁* ao estado inicial de *M₂* por meio de transições-ε. Os estados finais do autômato resultante são apenas os de *M₂*. O não determinismo permite "adivinhar" onde termina a parte pertencente a *L₁* e começa a parte pertencente a *L₂*.

**Estrela de Kleene (L₁\*).** Cria-se um novo estado inicial (que também é final, para aceitar ε). Adiciona-se uma transição-ε do novo estado inicial para o estado inicial de *M₁*, e transições-ε de cada estado final de *M₁* de volta ao estado inicial de *M₁*. Isso permite zero ou mais repetições.

**Complemento (L̄₁).** Dado um **AFD completo** *M₁* (sem transições indefinidas), basta inverter os estados finais e não finais: F' = Q − F. Se *M₁* aceita *w*, então *M'* rejeita, e vice-versa. Note que esta construção exige um AFD (não funciona diretamente com AFND).

**Interseção (L₁ ∩ L₂).** Pela lei de De Morgan: L₁ ∩ L₂ = (L̄₁ ∪ L̄₂)̄. Como temos fechamento sob complemento e união, o resultado segue. Alternativamente, usa-se a construção do produto cartesiano com F = F₁ × F₂ (estado final apenas quando ambos aceitam).

**Diferença (L₁ − L₂).** Temos L₁ − L₂ = L₁ ∩ L̄₂. Como ambas as operações preservam regularidade, a diferença também preserva.

**Reverso (Lᴿ).** Dado um AFD para *L*, inverte-se a direção de todas as transições, o antigo estado inicial torna-se o único estado final, e cria-se um novo estado inicial com transições-ε para todos os antigos estados finais. O autômato resultante (um AFND-ε) reconhece Lᴿ.

---

## 4.3 Expressões Regulares (ER)

### 4.3.1 Definição Recursiva (Indutiva)

As expressões regulares são definidas indutivamente sobre um alfabeto Σ:

**Base da Indução:**

1. **∅** é uma expressão regular, e L(∅) = ∅ (a linguagem vazia — nenhuma cadeia).
2. **ε** é uma expressão regular, e L(ε) = {ε} (a linguagem contendo apenas a cadeia vazia).
3. Para cada símbolo **a ∈ Σ**, **a** é uma expressão regular, e L(a) = {a}.

**Passo Indutivo:**

Se *r₁* e *r₂* são expressões regulares, então:

4. **(r₁ + r₂)** é uma expressão regular, e L(r₁ + r₂) = L(r₁) ∪ L(r₂)  — **união** (alternação).
5. **(r₁ · r₂)** é uma expressão regular, e L(r₁ · r₂) = L(r₁) · L(r₂)  — **concatenação**.
6. **(r₁\*)** é uma expressão regular, e L(r₁\*) = (L(r₁))\*  — **estrela de Kleene** (fecho).

**Nada mais é expressão regular** além do que pode ser obtido por um número finito de aplicações das regras acima.

### 4.3.2 Precedência de Operadores

Para reduzir o uso de parênteses, adota-se a seguinte convenção de precedência (da maior para a menor):

```
    *   (estrela de Kleene)   — maior precedência
    ·   (concatenação)
    +   (união / alternação)  — menor precedência
```

Assim, a expressão `a + b · c*` é interpretada como `a + (b · (c*))`, ou seja: a união de `{a}` com a concatenação de `{b}` com `{c}*`.

### 4.3.3 Exemplos de Expressões Regulares

Seja Σ = {a, b}. Apresentamos a seguir diversas expressões regulares e as linguagens que denotam:

| Expressão Regular | Linguagem Denotada | Exemplos de cadeias |
|---|---|---|
| `a*b` | { aⁿb \| n ≥ 0 } | b, ab, aab, aaab, … |
| `(a + b)*` | Σ\* (todas as cadeias sobre {a, b}) | ε, a, b, aa, ab, ba, bb, … |
| `a*b*` | { aⁿbᵐ \| n, m ≥ 0 } | ε, a, b, aa, ab, bb, aabb, … |
| `(a + b)*abb` | Cadeias que terminam em "abb" | abb, aabb, babb, ababb, … |
| `a(a + b)*b` | Cadeias que começam com a e terminam com b | ab, aab, abb, aabb, abab, … |
| `(ab)*` | { (ab)ⁿ \| n ≥ 0 } | ε, ab, abab, ababab, … |
| `a+ = a · a*` | { aⁿ \| n ≥ 1 } | a, aa, aaa, aaaa, … |
| `(a + b)(a + b)` | Todas as cadeias de comprimento 2 | aa, ab, ba, bb |
| `ε + a + b` | { ε, a, b } | ε, a, b |
| `∅*` | { ε } | ε |

**Exemplo detalhado.** Considere a expressão regular `(0 + 1)*011`:

- L((0 + 1)\*011) = { w ∈ {0, 1}\* | w termina com 011 }

Cadeias aceitas: 011, 0011, 1011, 00011, 10011, 01011, 11011, …
Cadeias rejeitadas: ε, 0, 1, 01, 010, 0110, …

### 4.3.4 Identidades Algébricas

As expressões regulares satisfazem diversas identidades úteis para simplificação:

- r + ∅ = r (∅ é identidade da união)
- r · ε = ε · r = r (ε é identidade da concatenação)
- r · ∅ = ∅ · r = ∅ (∅ é aniquilador da concatenação)
- r + r = r (idempotência da união)
- r + s = s + r (comutatividade da união)
- (r + s) + t = r + (s + t) (associatividade da união)
- (r · s) · t = r · (s · t) (associatividade da concatenação)
- r · (s + t) = r·s + r·t (distributividade à esquerda)
- (r + s) · t = r·t + s·t (distributividade à direita)
- (r\*)\* = r\* (idempotência da estrela)
- ε + r · r\* = r\* (desdobramento da estrela)
- ∅\* = ε

---

## 4.4 Equivalência entre Expressões Regulares e Autômatos Finitos

### 4.4.1 Teorema de Kleene

**Teorema (Kleene, 1956).** Uma linguagem *L* ⊆ Σ\* é **regular** se e somente se existe uma **expressão regular** *r* tal que L(r) = *L*.

O teorema é demonstrado em duas direções:

- **(⇒) ER → Autômato:** Toda expressão regular pode ser convertida em um AFND-ε equivalente (Construção de Thompson).
- **(⇐) Autômato → ER:** Todo AFD pode ser convertido em uma expressão regular equivalente (Eliminação de Estados / Lema de Arden).

### 4.4.2 ER → AFND-ε: Construção de Thompson

A **construção de Thompson** (1968) converte recursivamente uma expressão regular em um AFND-ε com exatamente **um estado inicial** e **um estado final**. Cada sub-expressão gera um fragmento de autômato com essas propriedades, e os fragmentos são compostos segundo a estrutura da expressão.

#### Caso Base 1: Expressão ∅ (linguagem vazia)

```
    ┌───────────┐
    │           │
  ─→(i)       (f)
    │           │
    └───────────┘

  Estado inicial: i
  Estado final:   f
  Transições:     nenhuma
  L = ∅
```

Não há transição entre *i* e *f*; nenhuma cadeia é aceita.

#### Caso Base 2: Expressão ε (cadeia vazia)

```
         ε
  ─→(i) ───→ (f)

  Estado inicial: i
  Estado final:   f
  Transição:      δ(i, ε) = {f}
  L = {ε}
```

#### Caso Base 3: Expressão a (símbolo do alfabeto)

```
         a
  ─→(i) ───→ (f)

  Estado inicial: i
  Estado final:   f
  Transição:      δ(i, a) = {f}
  L = {a}
```

#### Passo Indutivo 1: União r₁ + r₂

Sejam N₁ e N₂ os AFND-ε para r₁ e r₂, respectivamente, com estados iniciais i₁, i₂ e finais f₁, f₂.

```
                    ε    ┌─────────┐  ε
                  ┌────→ │   N₁    │────→┐
                  │      │ i₁ → f₁ │     │
                  │      └─────────┘     │
         ─→(i)───┤                       ├───→(f)
                  │      ┌─────────┐     │
                  │  ε   │   N₂    │  ε  │
                  └────→ │ i₂ → f₂ │────→┘
                         └─────────┘

  Novo estado inicial: i  (com transições-ε para i₁ e i₂)
  Novo estado final:   f  (f₁ e f₂ têm transições-ε para f)
  L = L(r₁) ∪ L(r₂)
```

#### Passo Indutivo 2: Concatenação r₁ · r₂

```
         ┌─────────┐  ε   ┌─────────┐
  ─→(i₁) │   N₁    │────→ │   N₂    │ (f₂)
         │    → f₁  │     │ i₂ →    │
         └─────────┘      └─────────┘

  Estado inicial: i₁
  Estado final:   f₂
  Transição adicional: δ(f₁, ε) = {i₂}
  L = L(r₁) · L(r₂)
```

O estado final de N₁ (f₁) é conectado ao estado inicial de N₂ (i₂) por uma transição-ε. O estado final de N₁ deixa de ser final; o estado final de N₂ torna-se o único estado final.

#### Passo Indutivo 3: Estrela de Kleene r₁*

```
                  ε
              ┌──────────────────────┐
              │                      │
              │    ε   ┌─────────┐ ε │
  ─→(i) ─────┼──────→ │   N₁    │───┼────→(f)
              │        │ i₁ → f₁ │   │
         ε    │        └─────────┘   │
  ─→(i) ─────┴──────────────────────┴────→(f)

  Versão simplificada:

              ε               ε
  ─→(i) ──────→ (i₁)─── N₁ ───→(f₁) ──────→ (f)
     │                          │          ↑
     │           ε              └────ε─────┘
     └──────────────────────────────────────→(f)

  Novo estado inicial: i
  Novo estado final:   f
  Transições-ε adicionais:
    • i  → i₁  (entrar no sub-autômato)
    • f₁ → f   (sair do sub-autômato)
    • f₁ → i₁  (repetir — laço)
    • i  → f   (aceitar ε — zero repetições)
  L = L(r₁)*
```

#### Propriedades da Construção de Thompson

A construção de Thompson garante:

1. Exatamente **um estado inicial** (sem transições de entrada) e **um estado final** (sem transições de saída).
2. Cada estado tem no máximo **duas transições de saída**.
3. O número de estados é **linear** no tamanho da expressão regular: no máximo 2·|r| estados.
4. O AFND-ε resultante pode ser convertido em AFD (via construção de subconjuntos) ou simulado diretamente.

### 4.4.3 AFD → ER: Método de Eliminação de Estados

Para converter um AFD em expressão regular, o **método de eliminação de estados** (também chamado de GNFA — *Generalized Nondeterministic Finite Automaton*) procede da seguinte forma:

1. **Preparação:** Crie um novo estado inicial *s* com transição-ε para o antigo estado inicial, e um novo estado final *t* com transições-ε de todos os antigos estados finais para *t*. Rotule cada transição com a expressão regular correspondente.

2. **Eliminação:** Para cada estado intermediário *q* (exceto *s* e *t*), elimine *q*:
   - Para cada par de estados (*p*, *r*) tais que existam transições p →(R₁) q, q →(R₂) q (laço), e q →(R₃) r, substitua pela transição direta p →(R₁ · R₂\* · R₃) r.
   - Se já existia uma transição p →(R₄) r, combine: p →(R₄ + R₁ · R₂\* · R₃) r.

3. **Resultado:** Quando restar apenas *s* e *t*, a expressão regular na transição s → t é a expressão que descreve a linguagem do autômato original.

### 4.4.4 Lema de Arden

Uma abordagem algébrica alternativa utiliza o **Lema de Arden**:

**Lema (Arden, 1961).** Se *A* e *B* são linguagens regulares e ε ∉ A, então a equação X = A·X + B tem solução única X = A\*·B.

Esse lema permite resolver sistemas de equações lineares derivados das transições do autômato, obtendo a expressão regular para cada estado e, em particular, para o estado inicial.

---

## 4.5 Gramática Regular (Tipo 3 na Hierarquia de Chomsky)

### 4.5.1 Definição

Uma **gramática regular** (ou gramática de tipo 3) é uma quádrupla G = (V, Σ, P, S), onde:

- **V** é um conjunto finito de **variáveis** (símbolos não terminais);
- **Σ** é um conjunto finito de **símbolos terminais** (Σ ∩ V = ∅);
- **P** é um conjunto finito de **produções** (regras);
- **S** ∈ V é o **símbolo inicial**.

As produções são restritas a uma das duas formas:

**Gramática Linear à Direita (GLD):**

Todas as produções têm a forma:

- A → aB  (onde A, B ∈ V e a ∈ Σ)
- A → a   (onde A ∈ V e a ∈ Σ)
- A → ε   (permitida apenas se A = S e S não aparece no lado direito de nenhuma produção)

**Gramática Linear à Esquerda (GLE):**

Todas as produções têm a forma:

- A → Ba  (onde A, B ∈ V e a ∈ Σ)
- A → a   (onde A ∈ V e a ∈ Σ)
- A → ε   (mesma restrição)

> **Atenção:** Uma gramática é regular somente se **todas** as suas produções seguem consistentemente a forma linear à direita **ou** à esquerda. Misturar ambas as formas resulta numa gramática linear (não necessariamente regular), que pode gerar linguagens não regulares.

**Teorema.** As gramáticas lineares à direita, as gramáticas lineares à esquerda e os autômatos finitos descrevem exatamente a mesma classe de linguagens: as **linguagens regulares** (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 4.5.2 Conversão AFD → Gramática Regular (Linear à Direita)

Dado um AFD M = (Q, Σ, δ, q₀, F), construímos a GLD G = (V, Σ, P, S):

1. **V = Q** (cada estado do AFD torna-se uma variável da gramática).
2. **S = q₀** (o estado inicial torna-se o símbolo inicial).
3. Para cada transição **δ(qᵢ, a) = qⱼ**, adicione a produção **qᵢ → a qⱼ**.
4. Se **qⱼ ∈ F** (estado final), adicione também **qᵢ → a** para cada transição δ(qᵢ, a) = qⱼ.
5. Se **q₀ ∈ F** (o estado inicial é final), adicione **S → ε** (caso ε ∈ L(M)).

### 4.5.3 Conversão Gramática Regular → AFND

Dada uma GLD G = (V, Σ, P, S), construímos um AFND M = (Q, Σ, δ, q₀, F):

1. **Q = V ∪ {qf}**, onde *qf* é um novo estado final (qf ∉ V).
2. **q₀ = S** (o símbolo inicial torna-se o estado inicial).
3. **F = {qf}** (único estado final). Se S → ε ∈ P, então F = {qf, S}.
4. Para cada produção **A → aB**, adicione a transição **δ(A, a) ∋ B**.
5. Para cada produção **A → a**, adicione a transição **δ(A, a) ∋ qf**.

### 4.5.4 Exemplo Detalhado

**Problema:** Construir uma gramática regular que gere a linguagem L = { w ∈ {a, b}\* | w contém "ab" como subcadeia }.

**Passo 1 — AFD para L:**

Identificamos três situações (estados):

- **q₀:** Estado inicial — ainda não vimos 'a' (ou acabamos de ver 'b').
- **q₁:** Acabamos de ver 'a' — esperando 'b' para completar "ab".
- **q₂:** Já encontramos "ab" — estado de aceitação (qualquer símbolo mantém aqui).

```
            a          b          a, b
  ─→(q₀) ────→ (q₁) ────→ ((q₂)) ─┐
     │ ↑         │                   │
     │ b         │ a                 └──┘
     └─┘         └─┘
```

Tabela de transições:

| Estado | a   | b   |
|--------|-----|-----|
| → q₀  | q₁  | q₀  |
| q₁     | q₁  | q₂  |
| \*q₂   | q₂  | q₂  |

**Passo 2 — Gramática Regular (linear à direita):**

Aplicando o algoritmo de conversão:

```
  q₀ → a q₁  |  b q₀
  q₁ → a q₁  |  b q₂
  q₂ → a q₂  |  b q₂  |  a  |  b
```

Note que as produções `q₂ → a` e `q₂ → b` existem porque q₂ é estado final e δ(q₂, a) = q₂, δ(q₂, b) = q₂. Além disso, como q₁ tem transição para q₂ (final) com 'b', adicionamos também:

```
  q₁ → b
```

Gramática final G = ({q₀, q₁, q₂}, {a, b}, P, q₀):

```
  q₀ → a q₁  |  b q₀
  q₁ → a q₁  |  b q₂  |  b
  q₂ → a q₂  |  b q₂  |  a  |  b
```

**Verificação — Derivação de "aab":**

```
  q₀ ⇒ a q₁ ⇒ a a q₁ ⇒ a a b   ✔  (usando q₁ → b)
```

**Verificação — Derivação de "bab":**

```
  q₀ ⇒ b q₀ ⇒ b a q₁ ⇒ b a b   ✔  (usando q₁ → b)
```

---

## 4.6 Propriedades de Decisão

Uma das grandes vantagens das linguagens regulares é que muitos problemas que são indecidíveis para classes mais gerais tornam-se **decidíveis** (e frequentemente eficientes) para linguagens regulares.

### 4.6.1 Problemas Decidíveis

| Problema | Entrada | Pergunta | Complexidade |
|---|---|---|---|
| **Pertinência** (*membership*) | AFD *M*, cadeia *w* | w ∈ L(M)? | O(\|w\|) |
| **Vacuidade** (*emptiness*) | AFD *M* | L(M) = ∅? | O(\|Q\| + \|δ\|) |
| **Finitude** (*finiteness*) | AFD *M* | L(M) é finita? | O(\|Q\| + \|δ\|) |
| **Equivalência** (*equivalence*) | AFDs M₁, M₂ | L(M₁) = L(M₂)? | O(n · log n) |
| **Inclusão** (*containment*) | AFDs M₁, M₂ | L(M₁) ⊆ L(M₂)? | Decidível |
| **Universalidade** | AFD *M* | L(M) = Σ\*? | Decidível |

**Pertinência:** Basta simular o AFD sobre *w*. Se, ao final da cadeia, o estado corrente é final, a cadeia pertence à linguagem. Tempo linear no comprimento de *w*.

**Vacuidade:** Verificamos se algum estado final é acessível a partir do estado inicial (busca em grafo — BFS ou DFS). L(M) = ∅ se e somente se nenhum estado final é alcançável.

**Finitude:** L(M) é infinita se e somente se existe um ciclo acessível a partir do estado inicial que alcança algum estado final. Detectamos ciclos por busca em grafo no subgrafo dos estados úteis (acessíveis e co-acessíveis). Alternativamente, pelo Lema do Bombeamento: se L(M) contém alguma cadeia de comprimento ≥ |Q|, então L(M) é infinita.

**Equivalência:** Construímos o **AFD mínimo** para cada autômato (minimização de Hopcroft, O(n · log n)) e verificamos se são isomorfos. Alternativamente, verificamos se L(M₁) ⊕ L(M₂) = ∅ (diferença simétrica).

**Inclusão:** L(M₁) ⊆ L(M₂) se e somente se L(M₁) ∩ L̄(M₂) = ∅. Construímos o autômato para a interseção com o complemento e verificamos vacuidade.

### 4.6.2 Observação sobre Indecidibilidade

Embora os problemas acima sejam decidíveis para linguagens regulares, é importante notar que:

- O **problema da ambiguidade** ("a gramática é ambígua?") é **indecidível** para gramáticas livres de contexto, mas para gramáticas regulares, a questão não se aplica da mesma forma, pois todo AFD define uma derivação única.
- A questão "uma dada linguagem livre de contexto é regular?" é **indecidível** — não existe algoritmo geral para decidir se uma LLC arbitrária é, na verdade, regular (Sipser, 2012).
- Para classes superiores na hierarquia de Chomsky (linguagens sensíveis ao contexto, recursivamente enumeráveis), problemas como vacuidade, equivalência e inclusão tornam-se indecidíveis, reforçando a importância prática da regularidade.

---

## 4.7 Aplicações Práticas

As linguagens regulares e suas representações (autômatos finitos, expressões regulares, gramáticas regulares) permeiam a ciência da computação e a engenharia de software:

### 4.7.1 Análise Léxica (Scanners / Lexers)

A primeira fase de um compilador — a **análise léxica** — é inteiramente baseada em linguagens regulares. O programador especifica os padrões dos tokens por meio de expressões regulares:

```
  identificador  →  [a-zA-Z_][a-zA-Z0-9_]*
  número_inteiro →  [0-9]+
  número_real    →  [0-9]+\.[0-9]+
  operador       →  \+|\-|\*|\/
```

Ferramentas como **lex**, **flex** e **ANTLR** convertem essas especificações em autômatos finitos (tipicamente AFDs) que realizam a análise léxica em tempo linear sobre o código-fonte (Aho, Lam, Sethi & Ullman, 2006).

### 4.7.2 Busca e Manipulação de Texto

Os utilitários `grep`, `sed`, `awk` e os mecanismos de busca em editores de texto utilizam expressões regulares para localizar padrões em arquivos e fluxos de texto. A sintaxe moderna (PCRE — *Perl Compatible Regular Expressions*) estende as expressões regulares clássicas com recursos como referências retroativas (*backreferences*), que, a rigor, transcendem o poder das linguagens regulares.

### 4.7.3 Validação de Entrada

Expressões regulares são amplamente utilizadas para validar formatos de dados:

- Endereços de e-mail
- Números de telefone e CPF
- URLs e endereços IP
- Datas e horários
- Códigos postais

### 4.7.4 Protocolos de Rede

Muitos protocolos de comunicação (TCP, HTTP, SMTP) definem suas máquinas de estados como autômatos finitos. A especificação do protocolo TCP, por exemplo, inclui um diagrama de estados finitos com 11 estados que governa o ciclo de vida de uma conexão.

### 4.7.5 Bioinformática

Na bioinformática, expressões regulares e autômatos finitos são empregados para buscar **padrões em sequências de DNA e proteínas**. O banco de dados PROSITE, por exemplo, utiliza expressões regulares para descrever padrões conservados em famílias de proteínas. A busca de motivos em genomas é frequentemente modelada como um problema de casamento de padrões sobre um alfabeto finito (Σ = {A, C, G, T}).

### 4.7.6 Verificação de Hardware e Software

Autômatos finitos são utilizados em **model checking** — uma técnica de verificação formal que explora exaustivamente o espaço de estados de um sistema para verificar propriedades especificadas em lógica temporal (Clarke, Grumberg & Peled, 1999).

---

## 4.8 Implementação em C

O diretório `src/04-regulares/` contém uma implementação em linguagem C que demonstra os conceitos fundamentais deste capítulo na prática. O programa `regex_basico.c` inclui:

- **Implementação de um motor básico de expressões regulares em C**, utilizando uma função recursiva de *matching* diretamente sobre a expressão.
- **Suporte às operações fundamentais** de expressões regulares: concatenação implícita, curinga (`.`) e estrela de Kleene (`*`).
- **Foco didático** na ligação entre a definição indutiva de expressões regulares e o algoritmo recursivo de reconhecimento, sem construção explícita de autômatos.

Para compilar e executar:

```bash
make regex_basico
./bin/regex_basico
```

Consulte o código-fonte e os comentários para detalhes de implementação.

---

## Referências

1. **AHO, A. V.; LAM, M. S.; SETHI, R.; ULLMAN, J. D.** *Compiladores: Princípios, Técnicas e Ferramentas*. 2. ed. São Paulo: Pearson, 2006. (Tradução da obra *Compilers: Principles, Techniques, and Tools*.)

2. **CLARKE, E. M.; GRUMBERG, O.; PELED, D. A.** *Model Checking*. Cambridge, MA: MIT Press, 1999.

3. **HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R.** *Introduction to Automata Theory, Languages, and Computation*. 3. ed. Boston: Addison-Wesley, 2006.

4. **KLEENE, S. C.** Representation of events in nerve nets and finite automata. In: SHANNON, C. E.; MCCARTHY, J. (Eds.). *Automata Studies*. Princeton: Princeton University Press, 1956. p. 3–42.

5. **MENEZES, P. B.** *Linguagens Formais e Autômatos*. 6. ed. Porto Alegre: Bookman (Série Livros Didáticos Informática UFRGS), 2011.

6. **RABIN, M. O.; SCOTT, D.** Finite automata and their decision problems. *IBM Journal of Research and Development*, v. 3, n. 2, p. 114–125, 1959.

7. **SIPSER, M.** *Introduction to the Theory of Computation*. 3. ed. Boston: Cengage Learning, 2012.

8. **THOMPSON, K.** Programming techniques: Regular expression search algorithm. *Communications of the ACM*, v. 11, n. 6, p. 419–422, 1968.

---

*Material didático elaborado para a disciplina de Linguagens Formais e Autômatos.*
