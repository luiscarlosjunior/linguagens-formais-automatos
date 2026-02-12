# Capítulo 5 — Minimização de Autômato, Lema do Bombeamento e Conversão de AFND para AFD

## 5.1 Introdução e Contexto Histórico

A teoria dos autômatos finitos atingiu um de seus marcos fundamentais na década de 1950, quando uma série de resultados interligados consolidou a compreensão profunda das linguagens regulares. Três pilares teóricos sustentam este capítulo: a **construção de subconjuntos** de Rabin e Scott (1959), o **Teorema de Myhill-Nerode** (1957–1958) e o **Lema do Bombeamento** (*Pumping Lemma*).

**Rabin e Scott** demonstraram, em seu artigo seminal *"Finite Automata and Their Decision Problems"* (1959), que todo autômato finito não-determinístico (AFND) possui um autômato finito determinístico (AFD) equivalente. A técnica por eles formalizada — a **construção de subconjuntos** (*subset construction*) — permanece como o algoritmo canônico para essa conversão e é apresentada em todos os textos clássicos da área (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012; Menezes, 2010).

O **Teorema de Myhill-Nerode**, desenvolvido independentemente por John Myhill (1957) e Anil Nerode (1958), estabelece uma condição necessária e suficiente para que uma linguagem seja regular, baseada em relações de equivalência de índice finito. Além de sua elegância teórica, esse teorema garante a **existência e unicidade do AFD mínimo** para qualquer linguagem regular — resultado de imensa importância prática.

O **Lema do Bombeamento** para linguagens regulares, cuja formulação moderna é atribuída a Bar-Hillel, Perles e Shamir (1961), fornece uma ferramenta indispensável para demonstrar que certas linguagens **não** são regulares. Baseado no princípio da casa dos pombos (*pigeonhole principle*), este lema explora a estrutura finita dos AFDs para derivar uma propriedade que toda linguagem regular deve satisfazer.

Esses três resultados estão intimamente relacionados: a construção de subconjuntos garante que o não-determinismo não amplia o poder expressivo dos autômatos finitos; o Teorema de Myhill-Nerode fornece o critério algébrico para regularidade e minimização; e o Lema do Bombeamento oferece o instrumento combinatório para provas de não-regularidade.

---

## 5.2 Conversão de AFND para AFD (Construção de Subconjuntos)

### 5.2.1 Fundamento Teórico

**Teorema (Rabin & Scott, 1959):** Para todo AFND M, existe um AFD M' tal que L(M) = L(M').

A ideia central é simular todas as computações possíveis do AFND simultaneamente. Cada estado do AFD resultante representa um **conjunto de estados** do AFND original — daí o nome *construção de subconjuntos* ou *construção de partes* (*powerset construction*).

### 5.2.2 Algoritmo Formal

Seja um AFND:

> M = (Q, Σ, δ, q₀, F)

onde:
- Q é o conjunto finito de estados,
- Σ é o alfabeto de entrada,
- δ : Q × Σ → P(Q) é a função de transição (retorna um conjunto de estados),
- q₀ ∈ Q é o estado inicial,
- F ⊆ Q é o conjunto de estados de aceitação.

Construímos o AFD equivalente:

> M' = (Q', Σ, δ', q₀', F')

da seguinte forma:

1. **Estados:** Q' ⊆ P(Q), ou seja, cada estado de M' é um subconjunto de Q. Na prática, construímos apenas os subconjuntos **alcançáveis** a partir do estado inicial.

2. **Estado inicial:**
   - Se M não possui ε-transições: q₀' = {q₀}
   - Se M possui ε-transições: q₀' = ε-fecho({q₀})

3. **Função de transição:** Para cada S ∈ Q' e cada a ∈ Σ:

   > δ'(S, a) = ∪_{q ∈ S} δ(q, a)

   Se M possui ε-transições, aplica-se o ε-fecho ao resultado:

   > δ'(S, a) = ε-fecho(∪_{q ∈ S} δ(q, a))

4. **Estados de aceitação:**

   > F' = { S ∈ Q' | S ∩ F ≠ ∅ }

   Um estado do AFD é de aceitação se **ao menos um** dos estados do AFND que ele representa for de aceitação.

### 5.2.3 Exemplo Detalhado

Considere o AFND M = ({q₀, q₁, q₂}, {a, b}, δ, q₀, {q₂}) com a seguinte tabela de transição:

| Estado | a         | b         |
|--------|-----------|-----------|
| q₀     | {q₀, q₁} | {q₀}     |
| q₁     | ∅         | {q₂}     |
| q₂     | ∅         | ∅         |

Este AFND aceita exatamente as cadeias sobre {a, b} que **terminam com "ab"**: o estado q₀ funciona como um "laço de espera" que, ao ler 'a', pode não-deterministicamente transitar para q₁ (apostando que este 'a' inicia o sufixo "ab"); q₁ aceita apenas 'b' e transita para o estado final q₂.

**Passo 1:** Estado inicial do AFD: q₀' = {q₀}.

**Passo 2:** Calculamos as transições a partir de {q₀}:
- δ'({q₀}, a) = δ(q₀, a) = {q₀, q₁}
- δ'({q₀}, b) = δ(q₀, b) = {q₀}

Novo estado descoberto: {q₀, q₁}.

**Passo 3:** Calculamos as transições a partir de {q₀, q₁}:
- δ'({q₀, q₁}, a) = δ(q₀, a) ∪ δ(q₁, a) = {q₀, q₁} ∪ ∅ = {q₀, q₁}
- δ'({q₀, q₁}, b) = δ(q₀, b) ∪ δ(q₁, b) = {q₀} ∪ {q₂} = {q₀, q₂}

Novo estado descoberto: {q₀, q₂}.

**Passo 4:** Calculamos as transições a partir de {q₀, q₂}:
- δ'({q₀, q₂}, a) = δ(q₀, a) ∪ δ(q₂, a) = {q₀, q₁} ∪ ∅ = {q₀, q₁}
- δ'({q₀, q₂}, b) = δ(q₀, b) ∪ δ(q₂, b) = {q₀} ∪ ∅ = {q₀}

Nenhum novo estado descoberto. Algoritmo encerra.

**Tabela de transição do AFD M':**

| Estado (Q')  | a          | b          | Aceitação? |
|--------------|------------|------------|------------|
| {q₀}        | {q₀, q₁}  | {q₀}      | Não        |
| {q₀, q₁}    | {q₀, q₁}  | {q₀, q₂}  | Não        |
| {q₀, q₂}    | {q₀, q₁}  | {q₀}      | **Sim**    |

O estado {q₀, q₂} é de aceitação porque {q₀, q₂} ∩ {q₂} = {q₂} ≠ ∅.

Renomeando para simplificar: A = {q₀}, B = {q₀, q₁}, C = {q₀, q₂}:

| Estado | a | b | Aceitação? |
|--------|---|---|------------|
| A      | B | A | Não        |
| B      | B | C | Não        |
| C      | B | A | **Sim**    |

O AFD resultante possui 3 estados, enquanto o AFND original tinha 3 estados. Neste caso, o número coincidiu, mas em geral pode ser muito diferente.

### 5.2.4 Análise de Complexidade

No pior caso, o AFD resultante pode ter **2^|Q|** estados, onde |Q| é o número de estados do AFND original. Isso porque Q' ⊆ P(Q) e o conjunto das partes de Q tem exatamente 2^|Q| elementos.

Esse limite superior é **justo** (*tight*): existem famílias de AFNDs com n estados para as quais o menor AFD equivalente requer exatamente 2ⁿ estados. Um exemplo clássico é o AFND sobre Σ = {a, b} que aceita cadeias cujo n-ésimo símbolo a partir do final é 'a'.

Na prática, entretanto, muitos dos 2^|Q| subconjuntos possíveis podem ser inalcançáveis a partir do estado inicial, e o AFD construído tende a ser significativamente menor que o limite teórico.

> **Observação (Hopcroft, Ullman & Motwani, 2006):** A construção de subconjuntos é a base de implementações práticas em compiladores e ferramentas de análise léxica, onde a conversão AFND → AFD é realizada como etapa intermediária na compilação de expressões regulares.

---

## 5.3 Remoção de Transições Vazias (ε)

### 5.3.1 AFND com ε-Transições (AFND-ε)

Um AFND-ε é uma extensão do AFND que permite transições sem consumir símbolo de entrada. Formalmente, a função de transição tem a assinatura:

> δ : Q × (Σ ∪ {ε}) → P(Q)

Embora as ε-transições aumentem a conveniência na construção de autômatos (especialmente na conversão de expressões regulares para autômatos, via construção de Thompson), elas **não aumentam o poder expressivo**: todo AFND-ε tem um AFND equivalente sem ε-transições.

### 5.3.2 ε-Fecho (ε-closure)

O **ε-fecho** de um estado q, denotado ε-fecho(q) ou ECLOSE(q), é o conjunto de todos os estados alcançáveis a partir de q utilizando **zero ou mais** ε-transições.

**Algoritmo para calcular ε-fecho(q):**

```
Entrada: estado q, função de transição δ
Saída: conjunto ε-fecho(q)

1. Inicialize pilha P ← {q} e resultado R ← {q}
2. Enquanto P não estiver vazia:
   a. Desempilhe um estado t de P
   b. Para cada estado u ∈ δ(t, ε):
      Se u ∉ R:
        Adicione u a R
        Empilhe u em P
3. Retorne R
```

Para um conjunto de estados S, define-se:

> ε-fecho(S) = ∪_{q ∈ S} ε-fecho(q)

### 5.3.3 Algoritmo de Remoção de ε-Transições

Dado um AFND-ε M = (Q, Σ, δ, q₀, F), construímos o AFND equivalente M' = (Q, Σ, δ', q₀, F') sem ε-transições:

1. **Para cada estado q ∈ Q e cada símbolo a ∈ Σ:**

   > δ'(q, a) = ε-fecho( ∪_{r ∈ ε-fecho(q)} δ(r, a) )

   Ou seja: a partir de q, primeiro considere todos os estados alcançáveis por ε-transições; depois, para cada um deles, aplique a transição por 'a'; finalmente, aplique o ε-fecho ao resultado.

2. **Estados de aceitação:**

   > F' = { q ∈ Q | ε-fecho(q) ∩ F ≠ ∅ }

   Um estado passa a ser de aceitação se, por ε-transições, pode alcançar algum estado de aceitação original.

### 5.3.4 Exemplo

Considere o AFND-ε M com Q = {q₀, q₁, q₂}, Σ = {a, b}, estado inicial q₀, F = {q₂}:

| Estado | a     | b     | ε     |
|--------|-------|-------|-------|
| q₀     | ∅     | ∅     | {q₁}  |
| q₁     | {q₁}  | ∅     | {q₂}  |
| q₂     | ∅     | {q₂}  | ∅     |

**Passo 1 — Calcular ε-fechos:**
- ε-fecho(q₀) = {q₀, q₁, q₂} (q₀ →ε q₁ →ε q₂)
- ε-fecho(q₁) = {q₁, q₂} (q₁ →ε q₂)
- ε-fecho(q₂) = {q₂}

**Passo 2 — Calcular δ':**

Para q₀:
- δ'(q₀, a) = ε-fecho(δ(q₀, a) ∪ δ(q₁, a) ∪ δ(q₂, a)) = ε-fecho(∅ ∪ {q₁} ∪ ∅) = ε-fecho({q₁}) = {q₁, q₂}
- δ'(q₀, b) = ε-fecho(δ(q₀, b) ∪ δ(q₁, b) ∪ δ(q₂, b)) = ε-fecho(∅ ∪ ∅ ∪ {q₂}) = ε-fecho({q₂}) = {q₂}

Para q₁:
- δ'(q₁, a) = ε-fecho(δ(q₁, a) ∪ δ(q₂, a)) = ε-fecho({q₁} ∪ ∅) = {q₁, q₂}
- δ'(q₁, b) = ε-fecho(δ(q₁, b) ∪ δ(q₂, b)) = ε-fecho(∅ ∪ {q₂}) = {q₂}

Para q₂:
- δ'(q₂, a) = ε-fecho(δ(q₂, a)) = ε-fecho(∅) = ∅
- δ'(q₂, b) = ε-fecho(δ(q₂, b)) = ε-fecho({q₂}) = {q₂}

**Passo 3 — Novos estados de aceitação:**

F' = { q | ε-fecho(q) ∩ {q₂} ≠ ∅ } = {q₀, q₁, q₂}

Todos os estados são de aceitação, pois todos podem alcançar q₂ por ε-transições.

**Tabela de transição do AFND M' (sem ε-transições):**

| Estado | a          | b     | Aceitação? |
|--------|------------|-------|------------|
| q₀     | {q₁, q₂}  | {q₂}  | **Sim**    |
| q₁     | {q₁, q₂}  | {q₂}  | **Sim**    |
| q₂     | ∅          | {q₂}  | **Sim**    |

Este AFND (sem ε) aceita a mesma linguagem que o AFND-ε original: L(M) = a*b*, isto é, cadeias compostas por zero ou mais a's seguidos de zero ou mais b's. Para verificar: a cadeia vazia ε é aceita (q₀ é estado de aceitação em M', pois ε-fecho(q₀) contém q₂ ∈ F); a cadeia "aab" é aceita (q₀ →a {q₁,q₂} → escolha q₁ →a {q₁,q₂} → escolha q₁ →b {q₂} ∈ F'); a cadeia "ba" não é aceita (q₀ →b {q₂} →a ∅, rejeita).

---

## 5.4 Minimização de AFD

### 5.4.1 Motivação

Linguagens regulares diferentes possuem AFDs diferentes, mas uma **mesma** linguagem regular pode ser reconhecida por infinitos AFDs distintos (basta adicionar estados redundantes ou inalcançáveis). Surge então a pergunta natural: qual é o **menor** AFD que reconhece uma dada linguagem regular?

**Teorema (Myhill, 1957; Nerode, 1958):** Para toda linguagem regular L, existe um único AFD mínimo (a menos de isomorfismo, isto é, renomeação de estados) que reconhece L. Esse AFD mínimo possui o menor número possível de estados dentre todos os AFDs que reconhecem L.

A minimização é importante tanto do ponto de vista teórico (fornece uma forma canônica para linguagens regulares) quanto prático (AFDs menores consomem menos memória e executam com a mesma eficiência).

### 5.4.2 Etapa Preliminar: Remoção de Estados Inalcançáveis

Antes de aplicar o algoritmo de minimização, devemos remover todos os estados que **não são alcançáveis** a partir do estado inicial.

**Algoritmo:**
1. Marque o estado inicial como alcançável.
2. Repetidamente, para cada estado já marcado como alcançável e para cada símbolo a ∈ Σ, marque δ(q, a) como alcançável.
3. Repita até que nenhum novo estado seja marcado.
4. Remova todos os estados não marcados e suas transições.

### 5.4.3 Algoritmo de Preenchimento de Tabela (Table-Filling / Marking Algorithm)

Este algoritmo, também chamado de **algoritmo de marcação**, determina quais pares de estados são **distinguíveis** (não-equivalentes). Estados indistinguíveis podem ser fundidos.

**Definição:** Dois estados p e q são **distinguíveis** se existe uma cadeia w ∈ Σ* tal que exatamente um dentre δ̂(p, w) e δ̂(q, w) é estado de aceitação (onde δ̂ é a função de transição estendida).

**Algoritmo:**

```
Entrada: AFD M = (Q, Σ, δ, q₀, F) sem estados inalcançáveis
Saída: Relação de equivalência sobre Q

1. Crie uma tabela triangular para todos os pares {p, q} com p ≠ q.

2. (Base) Para cada par {p, q} onde p ∈ F e q ∉ F (ou vice-versa):
   Marque {p, q} como DISTINGUÍVEL.

3. (Iteração) Repita até que nenhuma nova marcação ocorra:
   Para cada par NÃO marcado {p, q}:
     Para cada símbolo a ∈ Σ:
       Seja r = δ(p, a) e s = δ(q, a).
       Se {r, s} está marcado como DISTINGUÍVEL (e r ≠ s):
         Marque {p, q} como DISTINGUÍVEL.

4. (Resultado) Pares NÃO marcados ao final são EQUIVALENTES.
   Funda os estados equivalentes em um único estado.
```

### 5.4.4 Construção do AFD Mínimo

Após determinar as classes de equivalência [q] para cada estado q:

1. **Estados:** Q_min = { [q] | q ∈ Q } (uma classe por grupo de estados equivalentes)
2. **Estado inicial:** [q₀]
3. **Transição:** δ_min([q], a) = [δ(q, a)]
4. **Aceitação:** F_min = { [q] | q ∈ F }

### 5.4.5 Exemplo Detalhado

Considere o AFD M = ({A, B, C, D, E, F}, {0, 1}, δ, A, {C, D, E}) com:

| Estado | 0 | 1 | Aceitação? |
|--------|---|---|------------|
| A      | B | C | Não        |
| B      | A | D | Não        |
| C      | E | F | **Sim**    |
| D      | E | F | **Sim**    |
| E      | E | F | **Sim**    |
| F      | B | C | Não        |

Todos os estados são alcançáveis (pode-se verificar por busca a partir de A).

**Passo 1 — Marcação inicial (Base):**

Marcamos como distinguíveis todos os pares {aceitação, não-aceitação}:

|   | A | B | C | D | E | F |
|---|---|---|---|---|---|---|
| B | - |   |   |   |   |   |
| C | ✗ | ✗ |   |   |   |   |
| D | ✗ | ✗ | - |   |   |   |
| E | ✗ | ✗ | - | - |   |   |
| F | - | - | ✗ | ✗ | ✗ |   |

Legenda: ✗ = distinguível (marcado), - = ainda não marcado.

**Passo 2 — Iteração:**

Analisamos cada par não marcado:

**Par {A, B}:**
- Com 0: δ(A,0) = B, δ(B,0) = A → par {A, B} — não marcado → sem conclusão.
- Com 1: δ(A,1) = C, δ(B,1) = D → par {C, D} — não marcado → sem conclusão.
- {A, B} permanece não marcado.

**Par {C, D}:**
- Com 0: δ(C,0) = E, δ(D,0) = E → mesmo estado → sem conclusão.
- Com 1: δ(C,1) = F, δ(D,1) = F → mesmo estado → sem conclusão.
- {C, D} permanece não marcado.

**Par {C, E}:**
- Com 0: δ(C,0) = E, δ(E,0) = E → mesmo estado → sem conclusão.
- Com 1: δ(C,1) = F, δ(E,1) = F → mesmo estado → sem conclusão.
- {C, E} permanece não marcado.

**Par {D, E}:**
- Com 0: δ(D,0) = E, δ(E,0) = E → mesmo estado → sem conclusão.
- Com 1: δ(D,1) = F, δ(E,1) = F → mesmo estado → sem conclusão.
- {D, E} permanece não marcado.

**Par {A, F}:**
- Com 0: δ(A,0) = B, δ(F,0) = B → mesmo estado → sem conclusão.
- Com 1: δ(A,1) = C, δ(F,1) = C → mesmo estado → sem conclusão.
- {A, F} permanece não marcado.

**Par {B, F}:**
- Com 0: δ(B,0) = A, δ(F,0) = B → par {A, B} — não marcado → sem conclusão.
- Com 1: δ(B,1) = D, δ(F,1) = C → par {C, D} — não marcado → sem conclusão.
- {B, F} permanece não marcado.

Nova iteração: nenhum par adicional pode ser marcado (todos os pares não marcados conduzem a pares também não marcados). O algoritmo encerra.

**Passo 3 — Classes de equivalência:**

Os pares não marcados (equivalentes) são:
- {A, B}, {A, F}, {B, F} → A ≡ B ≡ F
- {C, D}, {C, E}, {D, E} → C ≡ D ≡ E

Classes de equivalência:
- **[A]** = {A, B, F} (não-aceitação)
- **[C]** = {C, D, E} (aceitação)

**Passo 4 — AFD Mínimo:**

| Estado | 0    | 1    | Aceitação? |
|--------|------|------|------------|
| [A]    | [A]  | [C]  | Não        |
| [C]    | [C]  | [A]  | **Sim**    |

O AFD original de 6 estados foi reduzido a apenas **2 estados**! Este AFD mínimo reconhece a linguagem das cadeias sobre {0, 1} que contêm um número ímpar de 1's.

**Verificação:** δ_min([A], 0) = [δ(A, 0)] = [B] = [A] ✓. δ_min([A], 1) = [δ(A, 1)] = [C] ✓. δ_min([C], 0) = [δ(C, 0)] = [E] = [C] ✓. δ_min([C], 1) = [δ(C, 1)] = [F] = [A] ✓.

> **Teorema:** O AFD resultante do algoritmo de minimização é o **único AFD mínimo** (a menos de isomorfismo) para a linguagem L. A prova decorre diretamente do Teorema de Myhill-Nerode (Seção 5.5).

---

## 5.5 Teorema de Myhill-Nerode

### 5.5.1 Relação de Equivalência Invariante à Direita

**Definição:** Seja L ⊆ Σ* uma linguagem. A **relação de equivalência de Myhill-Nerode** ≡_L é definida sobre Σ* por:

> x ≡_L y ⟺ para toda cadeia z ∈ Σ*, xz ∈ L se e somente se yz ∈ L

Em outras palavras, x e y são equivalentes se e somente se **nenhum sufixo** consegue distingui-los com relação à pertinência em L.

**Propriedades:**
1. ≡_L é uma relação de equivalência (reflexiva, simétrica e transitiva).
2. ≡_L é **invariante à direita** (*right-invariant*): se x ≡_L y, então para todo a ∈ Σ, xa ≡_L ya.
3. ≡_L é um **refinamento** de L: se x ≡_L y, então x ∈ L ⟺ y ∈ L.

### 5.5.2 Enunciado do Teorema

**Teorema de Myhill-Nerode:** As seguintes afirmações são equivalentes:

1. L é uma linguagem regular (reconhecida por algum AFD).
2. L é a união de algumas classes de equivalência de uma relação de equivalência invariante à direita de **índice finito** sobre Σ*.
3. A relação ≡_L tem **índice finito** (número finito de classes de equivalência).

Além disso, o **número de classes de equivalência** de ≡_L é exatamente igual ao **número de estados do AFD mínimo** que reconhece L.

### 5.5.3 Esboço da Prova

**(1 ⟹ 2):** Se L é regular, seja M = (Q, Σ, δ, q₀, F) um AFD que reconhece L. Defina a relação ≡_M por:

> x ≡_M y ⟺ δ̂(q₀, x) = δ̂(q₀, y)

Esta relação é de equivalência, invariante à direita, tem índice finito (no máximo |Q| classes), e L é a união das classes correspondentes a estados de F. Portanto, ≡_M satisfaz a condição (2).

**(2 ⟹ 3):** Se ≡ é uma relação de equivalência invariante à direita de índice finito tal que L é a união de classes de ≡, então ≡ é um **refinamento** de ≡_L (cada classe de ≡ está contida em uma classe de ≡_L). Portanto, o índice de ≡_L é no máximo o índice de ≡, que é finito.

**(3 ⟹ 1):** Se ≡_L tem índice finito, construímos o AFD M_L:
- Estados: as classes de equivalência [x]_L para x ∈ Σ*
- Estado inicial: [ε]_L
- Transição: δ([x]_L, a) = [xa]_L (bem definida pela invariância à direita)
- Aceitação: [x]_L ∈ F ⟺ x ∈ L

Este AFD reconhece L e é, de fato, o **AFD mínimo** para L, pois cada estado corresponde a exatamente uma classe de equivalência de ≡_L, e ≡_L é a relação de equivalência invariante à direita de **menor índice** que satura L (ou seja, é a mais "grossa" possível).

### 5.5.4 Consequência para a Minimização

O Teorema de Myhill-Nerode garante que:

1. O AFD mínimo para L é **único** (a menos de isomorfismo).
2. O número de estados do AFD mínimo é igual ao índice de ≡_L.
3. O algoritmo de preenchimento de tabela (Seção 5.4.3) calcula exatamente as classes de ≡_L quando aplicado a um AFD qualquer para L.

> **Referência:** Hopcroft, Ullman & Motwani (2006), Capítulo 4; Sipser (2012), Teorema 1.52; Menezes (2010), Capítulo 4.

---

## 5.6 Lema do Bombeamento (Pumping Lemma) para Linguagens Regulares

### 5.6.1 Enunciado Formal

**Lema do Bombeamento:** Seja L uma linguagem regular. Então existe um inteiro p ≥ 1 (chamado **comprimento de bombeamento** ou *pumping length*) tal que toda cadeia w ∈ L com |w| ≥ p pode ser escrita como:

> w = xyz

satisfazendo **simultaneamente** as três condições:

1. **|y| ≥ 1** (a parte "bombeável" não é vazia)
2. **|xy| ≤ p** (a parte bombeável ocorre no prefixo de comprimento p)
3. **Para todo i ≥ 0, xy^i z ∈ L** (a cadeia permanece na linguagem ao "bombear" y qualquer número de vezes, incluindo zero)

onde y^i denota a concatenação de y consigo mesma i vezes (y⁰ = ε, y¹ = y, y² = yy, etc.).

### 5.6.2 Ideia da Prova

A prova baseia-se no **princípio da casa dos pombos** (*pigeonhole principle*) aplicado aos estados de um AFD.

Seja M = (Q, Σ, δ, q₀, F) um AFD que reconhece L, e tome p = |Q| (número de estados).

Considere qualquer w = w₁w₂...wₙ ∈ L com n ≥ p. Ao processar w, o AFD visita a sequência de estados:

> s₀, s₁, s₂, ..., sₙ

onde s₀ = q₀ e sᵢ = δ(sᵢ₋₁, wᵢ) para 1 ≤ i ≤ n.

Como n ≥ p = |Q|, a sequência s₀, s₁, ..., sₚ contém **p + 1** estados. Pelo princípio da casa dos pombos, existem índices 0 ≤ j < k ≤ p tais que sⱼ = sₖ.

Defina:
- x = w₁...wⱼ (prefixo até a primeira ocorrência do estado repetido)
- y = wⱼ₊₁...wₖ (a parte correspondente ao ciclo)
- z = wₖ₊₁...wₙ (sufixo restante)

Então:
- |y| = k − j ≥ 1 (pois j < k) ✓
- |xy| = k ≤ p ✓
- Para todo i ≥ 0, xy^iz ∈ L, pois repetir o ciclo (de sⱼ a sₖ = sⱼ) qualquer número de vezes leva ao mesmo estado antes de processar z, e portanto ao mesmo estado final de aceitação ✓

### 5.6.3 Como Utilizar o Lema: Prova por Contradição

O Lema do Bombeamento é utilizado para provar que uma linguagem **não** é regular. O esquema de prova é:

1. **Suponha**, por contradição, que L é regular.
2. Pelo Lema do Bombeamento, existe p ≥ 1 (comprimento de bombeamento).
3. **Escolha** uma cadeia w ∈ L com |w| ≥ p (a escolha é do provador — deve ser estratégica!).
4. Considere **qualquer** decomposição w = xyz satisfazendo |y| ≥ 1 e |xy| ≤ p.
5. **Mostre** que existe algum i ≥ 0 tal que xy^iz ∉ L.
6. Isso contradiz o Lema do Bombeamento, logo L **não é regular**.

**Atenção ao jogo adversarial:** O provador escolhe w, mas o "adversário" (o lema) escolhe a decomposição xyz. Portanto, a prova deve funcionar para **toda** decomposição válida, não apenas para uma específica.

### 5.6.4 Exemplo 1: L = {aⁿbⁿ | n ≥ 0} não é regular

**Prova:**

1. Suponha, por contradição, que L = {aⁿbⁿ | n ≥ 0} é regular.

2. Pelo Lema do Bombeamento, existe p ≥ 1.

3. Escolha w = aᵖbᵖ. Claramente w ∈ L (pois tem p letras 'a' seguidas de p letras 'b') e |w| = 2p ≥ p.

4. Seja w = xyz uma decomposição qualquer com |y| ≥ 1 e |xy| ≤ p.

   Como |xy| ≤ p e os primeiros p caracteres de w são todos 'a', concluímos que **x e y consistem inteiramente de letras 'a'**. Podemos escrever:
   - x = aˢ para algum s ≥ 0
   - y = aᵗ para algum t ≥ 1 (pois |y| ≥ 1)
   - z = aᵖ⁻ˢ⁻ᵗbᵖ

5. Considere i = 0. Então:

   > xy⁰z = xz = aˢ · aᵖ⁻ˢ⁻ᵗbᵖ = aᵖ⁻ᵗbᵖ

   Como t ≥ 1, temos p − t < p, logo aᵖ⁻ᵗbᵖ tem **menos a's que b's**, e portanto xy⁰z ∉ L.

6. Contradição com o Lema do Bombeamento. ∎

   Logo, L = {aⁿbⁿ | n ≥ 0} **não é regular**.

### 5.6.5 Exemplo 2: L = {ww | w ∈ {a,b}*} não é regular

**Prova:**

1. Suponha, por contradição, que L = {ww | w ∈ {a,b}*} é regular.

2. Pelo Lema do Bombeamento, existe p ≥ 1.

3. Escolha w = aᵖbaᵖb. Esta cadeia está em L pois w = (aᵖb)(aᵖb), e |w| = 2p + 2 ≥ p.

4. Seja w = xyz uma decomposição qualquer com |y| ≥ 1 e |xy| ≤ p.

   Como |xy| ≤ p e os primeiros p caracteres de w = aᵖbaᵖb são todos 'a', temos que x e y consistem inteiramente de letras 'a':
   - x = aˢ para algum s ≥ 0
   - y = aᵗ para algum t ≥ 1
   - z = aᵖ⁻ˢ⁻ᵗbaᵖb

5. Considere i = 0. Então:

   > xy⁰z = xz = aˢ · aᵖ⁻ˢ⁻ᵗbaᵖb = aᵖ⁻ᵗbaᵖb

   Para que aᵖ⁻ᵗbaᵖb ∈ L, deveria existir alguma cadeia u tal que aᵖ⁻ᵗbaᵖb = uu. O comprimento total é 2p − t + 2. Para ser da forma uu, o comprimento deve ser par, logo t deve ser par. Nesse caso, |u| = p − t/2 + 1. Observemos a posição dos caracteres 'b': na cadeia aᵖ⁻ᵗbaᵖb, o primeiro 'b' aparece na posição p − t + 1 e o segundo 'b' na posição 2p − t + 2 (última posição). Se a cadeia fosse uu, o primeiro 'b' de u estaria na posição p − t + 1 e, por repetição, o 'b' correspondente na segunda cópia estaria na posição (p − t + 1) + (p − t/2 + 1) = 2p − 3t/2 + 2. Para que isso coincida com a posição do segundo 'b' (posição 2p − t + 2), precisaríamos 2p − 3t/2 + 2 = 2p − t + 2, o que implica t = 0 — contradizendo |y| ≥ 1.

   Logo, xy⁰z ∉ L.

6. Contradição com o Lema do Bombeamento. ∎

   Logo, L = {ww | w ∈ {a,b}*} **não é regular**.

### 5.6.6 Erros Comuns e Como Evitá-los

1. **Erro: Escolher a decomposição xyz.**
   O provador **não** escolhe a decomposição — apenas escolhe w. A prova deve funcionar para **toda** decomposição xyz que satisfaça as condições |y| ≥ 1 e |xy| ≤ p. Afirmar "seja y = aᵖ" quando não se justificou por que essa é a única possibilidade é um erro grave.

2. **Erro: Escolher w que não está em L.**
   A cadeia w deve pertencer a L. Escolher w ∉ L invalida toda a prova.

3. **Erro: Escolher w com |w| < p.**
   A cadeia w deve ter comprimento pelo menos p. Como p é desconhecido (apenas se sabe que existe), w deve ser definido **em termos de p**.

4. **Erro: Verificar apenas um valor de i.**
   Basta encontrar **um** valor de i para o qual xy^iz ∉ L, mas a análise deve considerar que a decomposição xyz é arbitrária (sujeita às restrições).

5. **Erro: Concluir regularidade a partir do Lema do Bombeamento.**
   O Lema do Bombeamento fornece uma condição **necessária** para regularidade, não suficiente. Existem linguagens não-regulares que satisfazem a propriedade do bombeamento. Portanto, o lema só pode ser usado para provar **não-regularidade**, nunca para provar regularidade.

### 5.6.7 Limitações do Lema do Bombeamento

O Lema do Bombeamento é uma condição **necessária mas não suficiente** para regularidade. A linguagem:

> L = { aⁱbʲcᵏ | se i = 1 então j = k }

é um exemplo clássico de linguagem **não-regular** que satisfaz a propriedade do bombeamento (ver Sipser, 2012, para detalhes). Para tais casos, ferramentas mais poderosas são necessárias, como o **Teorema de Myhill-Nerode** (que fornece condição necessária **e** suficiente) ou o **Lema do Bombeamento Generalizado** (*stronger pumping lemma*, como o Lema de Jaffe ou o Lema de Ogden para linguagens livres de contexto).

---

## 5.7 Exemplo em C

Implementações em linguagem C dos algoritmos discutidos neste capítulo estão disponíveis no diretório `src/05-minimizacao/`:

- **Conversão AFND → AFD** (construção de subconjuntos)
- **Remoção de ε-transições** (cálculo de ε-fecho)
- **Minimização de AFD** (algoritmo de preenchimento de tabela)
- **Verificação do Lema do Bombeamento** (simulação para cadeias específicas)

Consulte os arquivos-fonte e seus respectivos comentários para detalhes de implementação. Cada programa inclui exemplos de entrada que correspondem aos autômatos apresentados nas seções anteriores, permitindo ao estudante verificar os resultados manualmente.

---

## Referências

BAR-HILLEL, Y.; PERLES, M.; SHAMIR, E. On formal properties of simple phrase structure grammars. **Zeitschrift für Phonetik, Sprachwissenschaft und Kommunikationsforschung**, v. 14, p. 143–172, 1961.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Elsevier, 2006.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre: Bookman, 2010.

MYHILL, J. Finite automata and the representation of events. **WADD Technical Report**, v. 57-624, p. 112–137, 1957.

NERODE, A. Linear automaton transformations. **Proceedings of the American Mathematical Society**, v. 9, n. 4, p. 541–544, 1958.

RABIN, M. O.; SCOTT, D. Finite automata and their decision problems. **IBM Journal of Research and Development**, v. 3, n. 2, p. 114–125, 1959.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage Learning, 2012.
