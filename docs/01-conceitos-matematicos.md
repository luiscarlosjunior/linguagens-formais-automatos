# Conceitos Matemáticos para Uso em Linguagens Formais

## 1. Introdução e Contexto Histórico

O estudo das linguagens formais e dos autômatos repousa sobre alicerces matemáticos construídos ao longo de séculos. Compreender esses fundamentos não é mero exercício de erudição: é condição necessária para o domínio rigoroso da teoria da computação.

No final do século XIX, **Georg Cantor** (1845–1918) revolucionou a matemática ao formalizar a **teoria dos conjuntos**, oferecendo um arcabouço para tratar coleções de objetos de maneira precisa. Sua contribuição permitiu que se falasse, com rigor, em conjuntos finitos e infinitos — distinção que se mostra central quando diferenciamos linguagens finitas de linguagens infinitas sobre um alfabeto. Cantor introduziu ainda os conceitos de cardinalidade e de diferentes "tamanhos" de infinito, noções que reaparecem ao se demonstrar, por exemplo, a existência de linguagens não computáveis.

Contemporaneamente, **George Boole** (1815–1864) desenvolveu a **álgebra booleana**, formalizando o raciocínio lógico por meio de operações algébricas. Seu trabalho antecipou a lógica proposicional moderna e forneceu a base para os circuitos digitais e, consequentemente, para a própria computação. As operações booleanas — conjunção, disjunção e negação — permeiam toda a teoria de autômatos, desde a definição de estados de aceitação até a construção de complementos de linguagens regulares.

No século XX, **Alan Turing** (1912–1954) propôs, em 1936, o modelo abstrato que leva seu nome — a máquina de Turing — estabelecendo os limites do que é computável. Pouco depois, **Noam Chomsky** (1928–) introduziu, em 1956, a **hierarquia de Chomsky**, classificando as linguagens formais em quatro tipos segundo o poder expressivo de suas gramáticas. Ambos os trabalhos dependem fundamentalmente da teoria dos conjuntos, das relações, das funções e das técnicas de prova que este capítulo apresenta.

Como observa Sipser (2012), "a teoria da computação começa com uma pergunta: quais são as capacidades e limitações fundamentais dos computadores?". Para respondê-la, precisamos antes dominar a linguagem em que a pergunta é formulada — a matemática discreta.

---

## 2. Conjuntos

### 2.1 Definição

Um **conjunto** é uma coleção bem definida de objetos distintos, denominados **elementos** ou **membros**. Esta definição intuitiva, devida a Cantor, permanece como ponto de partida em praticamente todos os textos de referência (Hopcroft, Ullman & Motwani, 2006; Menezes, 2010).

Utilizamos letras maiúsculas para denotar conjuntos (A, B, C, …) e letras minúsculas para seus elementos (a, b, c, …). A notação fundamental é:

- **Pertinência:** x ∈ A (lê-se "x pertence a A")
- **Não pertinência:** x ∉ A (lê-se "x não pertence a A")

Um conjunto pode ser descrito por **enumeração** (ou extensão) ou por **compreensão** (ou intensão):

- Enumeração: A = {1, 2, 3, 4, 5}
- Compreensão: A = {x ∈ ℕ | 1 ≤ x ≤ 5}

### 2.2 Conjuntos Especiais

| Notação | Nome | Descrição |
|---------|------|-----------|
| ∅ ou {} | Conjunto vazio | Conjunto sem elementos |
| ℕ | Naturais | {0, 1, 2, 3, …} |
| ℤ | Inteiros | {…, −2, −1, 0, 1, 2, …} |
| U | Universo | Conjunto que contém todos os elementos em discussão |

**Observação importante para linguagens formais:** O conjunto vazio ∅ é diferente do conjunto {ε}, onde ε denota a cadeia vazia. O primeiro não contém elementos; o segundo contém exatamente um elemento — a cadeia de comprimento zero.

### 2.3 Relações entre Conjuntos

**Subconjunto:** A ⊆ B ⟺ (∀x)(x ∈ A → x ∈ B)

**Subconjunto próprio:** A ⊂ B ⟺ A ⊆ B ∧ A ≠ B

**Igualdade:** A = B ⟺ A ⊆ B ∧ B ⊆ A

**Conjunto potência (ou das partes):** O conjunto de todos os subconjuntos de A é denotado por P(A) ou 2^A. Se |A| = n, então |P(A)| = 2^n.

**Exemplo:** Se A = {0, 1}, então:

P(A) = {∅, {0}, {1}, {0, 1}}

Este conceito é essencial na construção de autômatos finitos determinísticos a partir de não determinísticos (construção de subconjuntos), em que cada estado do AFD corresponde a um elemento de P(Q), onde Q é o conjunto de estados do AFN.

### 2.4 Operações sobre Conjuntos

Sejam A e B conjuntos quaisquer e U o conjunto universo.

**União:**

A ∪ B = {x | x ∈ A ∨ x ∈ B}

**Interseção:**

A ∩ B = {x | x ∈ A ∧ x ∈ B}

**Complemento:**

Ā = A^c = {x ∈ U | x ∉ A}

**Diferença:**

A − B = A \ B = {x | x ∈ A ∧ x ∉ B}

**Diferença simétrica:**

A △ B = (A − B) ∪ (B − A) = (A ∪ B) − (A ∩ B)

**Produto cartesiano:**

A × B = {(a, b) | a ∈ A ∧ b ∈ B}

**Exemplo:** Sejam A = {a, b} e B = {0, 1}. Então:

- A ∪ B = {a, b, 0, 1}
- A ∩ B = ∅
- A × B = {(a, 0), (a, 1), (b, 0), (b, 1)}

O produto cartesiano é particularmente relevante na definição de **funções de transição** de autômatos: a função δ de um AFD é definida sobre Q × Σ, ou seja, sobre o produto cartesiano do conjunto de estados com o alfabeto de entrada.

### 2.5 Propriedades das Operações

As operações sobre conjuntos obedecem a diversas leis algébricas, análogas às da aritmética e da álgebra booleana:

**Comutatividade:**

- A ∪ B = B ∪ A
- A ∩ B = B ∩ A

**Associatividade:**

- (A ∪ B) ∪ C = A ∪ (B ∪ C)
- (A ∩ B) ∩ C = A ∩ (B ∩ C)

**Distributividade:**

- A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)
- A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)

**Leis de De Morgan:**

- (A ∪ B)^c = A^c ∩ B^c
- (A ∩ B)^c = A^c ∪ B^c

**Elementos neutros e absorventes:**

- A ∪ ∅ = A
- A ∩ U = A
- A ∪ U = U
- A ∩ ∅ = ∅

**Idempotência:**

- A ∪ A = A
- A ∩ A = A

**Complementação:**

- A ∪ A^c = U
- A ∩ A^c = ∅
- (A^c)^c = A

As Leis de De Morgan são especialmente úteis em linguagens formais. Por exemplo, ao demonstrar que a classe das linguagens regulares é fechada sob complementação, pode-se usar essas leis para derivar propriedades de fechamento sob interseção a partir do fechamento sob união e complemento.

---

## 3. Relações

### 3.1 Definição

Uma **relação binária** R de um conjunto A para um conjunto B é um subconjunto do produto cartesiano A × B:

R ⊆ A × B

Se (a, b) ∈ R, escrevemos a R b (lê-se "a está relacionado com b por R"). Quando A = B, dizemos que R é uma relação **sobre** A (ou **em** A).

**Exemplo:** Seja A = {1, 2, 3} e R a relação "menor que" sobre A:

R = {(1, 2), (1, 3), (2, 3)}

Podemos escrever 1 R 2 ou, mais naturalmente, 1 < 2.

### 3.2 Propriedades de Relações

Seja R uma relação sobre um conjunto A. Dizemos que R é:

**Reflexiva** se, para todo a ∈ A:

a R a

(Todo elemento se relaciona consigo mesmo.)

**Simétrica** se, para todos a, b ∈ A:

a R b → b R a

**Antissimétrica** se, para todos a, b ∈ A:

(a R b ∧ b R a) → a = b

**Transitiva** se, para todos a, b, c ∈ A:

(a R b ∧ b R c) → a R c

**Exemplo no contexto de autômatos:** Considere a relação de **alcançabilidade** entre estados de um autômato finito. Se a partir do estado q₁ é possível chegar a q₂ (por uma ou mais transições), e de q₂ é possível chegar a q₃, então de q₁ é possível chegar a q₃. Essa relação é, portanto, transitiva — propriedade fundamental para determinar estados acessíveis.

### 3.3 Relações de Equivalência

Uma relação R sobre A é uma **relação de equivalência** se é simultaneamente reflexiva, simétrica e transitiva.

**Definição formal:** R é uma relação de equivalência sobre A se e somente se:

1. (∀a ∈ A) a R a — reflexividade
2. (∀a, b ∈ A) a R b → b R a — simetria
3. (∀a, b, c ∈ A) (a R b ∧ b R c) → a R c — transitividade

### 3.4 Classes de Equivalência

Dada uma relação de equivalência R sobre A, a **classe de equivalência** de um elemento a ∈ A é:

[a]_R = {x ∈ A | x R a}

O conjunto de todas as classes de equivalência de A sob R forma uma **partição** de A, ou seja, uma coleção de subconjuntos não vazios, disjuntos dois a dois, cuja união é A. Este resultado é chamado **Teorema Fundamental das Relações de Equivalência**.

**Exemplo fundamental — Relação de Myhill-Nerode:** Dada uma linguagem L sobre um alfabeto Σ, define-se a relação ≡_L sobre Σ* por:

x ≡_L y ⟺ (∀z ∈ Σ*)(xz ∈ L ↔ yz ∈ L)

Esta é uma relação de equivalência. O **Teorema de Myhill-Nerode** afirma que uma linguagem é regular se e somente se ≡_L possui um número finito de classes de equivalência. Cada classe corresponde a um estado no AFD mínimo que reconhece L. Esta é uma das aplicações mais elegantes de relações de equivalência em toda a teoria da computação.

### 3.5 Ordens Parciais

Uma relação R sobre A é uma **ordem parcial** se é reflexiva, antissimétrica e transitiva. O par (A, R) é chamado **conjunto parcialmente ordenado** (ou **poset**).

**Exemplo:** A relação ⊆ (inclusão) sobre P(A) é uma ordem parcial:

1. A ⊆ A (reflexiva)
2. A ⊆ B ∧ B ⊆ A → A = B (antissimétrica)
3. A ⊆ B ∧ B ⊆ C → A ⊆ C (transitiva)

Ordens parciais aparecem, por exemplo, na hierarquia de Chomsky, em que as classes de linguagens formam uma cadeia por inclusão:

Regulares ⊂ Livres de Contexto ⊂ Sensíveis ao Contexto ⊂ Rec. Enumeráveis

---

## 4. Funções

### 4.1 Definição

Uma **função** (ou **aplicação**) f de A para B, denotada f: A → B, é uma relação especial de A para B tal que, para cada elemento a ∈ A, existe **exatamente um** elemento b ∈ B com (a, b) ∈ f. Escrevemos f(a) = b.

- A é chamado **domínio** de f.
- B é chamado **contradomínio** de f.
- O conjunto {f(a) | a ∈ A} ⊆ B é a **imagem** de f.

Formalmente:

f ⊆ A × B tal que (∀a ∈ A)(∃!b ∈ B)((a, b) ∈ f)

onde ∃! significa "existe um único".

### 4.2 Classificação de Funções

**Injetora (ou injetiva):** f é injetora se elementos distintos do domínio possuem imagens distintas:

(∀a₁, a₂ ∈ A)(f(a₁) = f(a₂) → a₁ = a₂)

**Sobrejetora (ou sobrejetiva):** f é sobrejetora se todo elemento do contradomínio é imagem de algum elemento do domínio:

(∀b ∈ B)(∃a ∈ A)(f(a) = b)

**Bijetora (ou bijetiva):** f é bijetora se é simultaneamente injetora e sobrejetora. Uma bijeção entre A e B estabelece uma correspondência um-a-um, implicando que |A| = |B|.

**Exemplo:** Seja Σ = {a, b} e considere a função comprimento |·|: Σ* → ℕ₀, definida por |w| = número de símbolos na cadeia w. Essa função é sobrejetora (para todo n ∈ ℕ₀, existe uma cadeia de comprimento n, como aⁿ), mas não é injetora (|ab| = |ba| = 2, porém ab ≠ ba).

### 4.3 Composição de Funções

Dadas f: A → B e g: B → C, a **composição** g ∘ f: A → C é definida por:

(g ∘ f)(a) = g(f(a)), para todo a ∈ A

A composição é associativa: h ∘ (g ∘ f) = (h ∘ g) ∘ f, mas em geral **não** é comutativa.

### 4.4 Funções de Transição em Autômatos

A função de transição é o coração de qualquer autômato. Em um **autômato finito determinístico** (AFD), ela é definida como:

δ: Q × Σ → Q

onde Q é o conjunto (finito) de estados e Σ é o alfabeto de entrada. Para cada par (estado atual, símbolo lido), δ retorna exatamente um próximo estado. O requisito de que δ seja uma **função total** (definida para todo par do domínio) garante o determinismo do autômato.

Em um **autômato finito não determinístico** (AFN), a "função" de transição produz um **conjunto** de possíveis próximos estados:

δ: Q × (Σ ∪ {ε}) → P(Q)

Observe que o contradomínio é P(Q), o conjunto potência de Q. Aqui, δ continua sendo uma função (cada entrada produz exatamente uma saída), mas cada saída é um conjunto de estados, possivelmente vazio.

A **função de transição estendida** δ̂: Q × Σ* → Q (para AFDs) é definida recursivamente:

- δ̂(q, ε) = q
- δ̂(q, wa) = δ(δ̂(q, w), a), para w ∈ Σ* e a ∈ Σ

Esta definição ilustra como funções e composição são empregadas para formalizar o processamento de cadeias inteiras por autômatos.

---

## 5. Lógica Proposicional e de Predicados

### 5.1 Lógica Proposicional

Uma **proposição** é uma sentença declarativa que pode ser classificada inequivocamente como verdadeira (V) ou falsa (F). Proposições são combinadas por **conectivos lógicos** para formar proposições compostas.

**Conectivos fundamentais:**

| Conectivo | Símbolo | Nome | Leitura |
|-----------|---------|------|---------|
| Negação | ¬p | NÃO | "não p" |
| Conjunção | p ∧ q | E | "p e q" |
| Disjunção | p ∨ q | OU | "p ou q" |
| Implicação | p → q | SE...ENTÃO | "se p então q" |
| Bicondicional | p ↔ q | SE E SOMENTE SE | "p se e somente se q" |

### 5.2 Tabelas-Verdade

A semântica dos conectivos é definida por **tabelas-verdade**:

**Negação:**

| p | ¬p |
|---|-----|
| V | F |
| F | V |

**Conjunção e Disjunção:**

| p | q | p ∧ q | p ∨ q |
|---|---|-------|-------|
| V | V | V | V |
| V | F | F | V |
| F | V | F | V |
| F | F | F | F |

**Implicação e Bicondicional:**

| p | q | p → q | p ↔ q |
|---|---|-------|-------|
| V | V | V | V |
| V | F | F | F |
| F | V | V | F |
| F | F | V | V |

**Observação crucial:** Na implicação p → q, quando p é falso, a implicação é verdadeira independentemente do valor de q. Este é o chamado princípio da **verdade vácua** (*vacuous truth*), que frequentemente causa estranhamento em estudantes, mas é essencial para a validade de provas universais — por exemplo, ao afirmar "para toda cadeia w, se w ∈ L₁ então w ∈ L₂", a afirmação é considerada verdadeira para cadeias que não estão em L₁.

### 5.3 Equivalências Lógicas Notáveis

- **Leis de De Morgan:** ¬(p ∧ q) ≡ ¬p ∨ ¬q e ¬(p ∨ q) ≡ ¬p ∧ ¬q
- **Contrapositiva:** (p → q) ≡ (¬q → ¬p)
- **Dupla negação:** ¬(¬p) ≡ p
- **Exportação:** ((p ∧ q) → r) ≡ (p → (q → r))
- **Implicação como disjunção:** (p → q) ≡ (¬p ∨ q)

A equivalência entre uma implicação e sua contrapositiva é a base das **provas por contrapositiva**, técnica recorrente na teoria de linguagens.

### 5.4 Lógica de Predicados (Primeira Ordem)

A lógica proposicional não é suficiente para expressar afirmações sobre elementos de um conjunto. Para tanto, empregamos **predicados** e **quantificadores**.

Um **predicado** é uma sentença com variáveis que se torna proposição quando estas recebem valores. Por exemplo, P(x): "x é um número primo" é um predicado sobre ℕ.

**Quantificadores:**

- **Universal:** (∀x ∈ A) P(x) — "para todo x em A, P(x) é verdadeiro"
- **Existencial:** (∃x ∈ A) P(x) — "existe pelo menos um x em A tal que P(x) é verdadeiro"

**Negação de quantificadores:**

- ¬(∀x) P(x) ≡ (∃x) ¬P(x)
- ¬(∃x) P(x) ≡ (∀x) ¬P(x)

**Exemplo em linguagens formais:** A definição de que uma linguagem L é decidível pode ser expressa como:

(∃M)(∀w ∈ Σ*)(w ∈ L → M aceita w) ∧ (w ∉ L → M rejeita w)

onde M é uma máquina de Turing que sempre para. A habilidade de manipular quantificadores e suas negações é indispensável para compreender (e provar) resultados de indecidibilidade.

---

## 6. Técnicas de Prova

A teoria de linguagens formais e autômatos é, em sua essência, uma teoria matemática — e, como tal, suas afirmações requerem **demonstrações**. Dominar as técnicas de prova é tão importante quanto compreender os conceitos em si.

### 6.1 Prova Direta

Na prova direta, parte-se das hipóteses e, por meio de passos lógicos válidos, chega-se à conclusão desejada.

**Estrutura:** Para provar p → q, assume-se p verdadeiro e demonstra-se que q é verdadeiro.

**Exemplo:** Provar que, se L₁ ⊆ L₂, então L₁ ∪ L₂ = L₂.

*Prova:* Precisamos mostrar que L₁ ∪ L₂ ⊆ L₂ e L₂ ⊆ L₁ ∪ L₂.

(⊇) Seja w ∈ L₂. Então w ∈ L₁ ∪ L₂ por definição de união. Logo, L₂ ⊆ L₁ ∪ L₂.

(⊆) Seja w ∈ L₁ ∪ L₂. Então w ∈ L₁ ou w ∈ L₂. Se w ∈ L₂, já temos o resultado. Se w ∈ L₁, como L₁ ⊆ L₂, segue que w ∈ L₂. Em ambos os casos, w ∈ L₂. Logo, L₁ ∪ L₂ ⊆ L₂. ∎

### 6.2 Prova por Contradição (Redução ao Absurdo)

Para provar uma afirmação P, assume-se ¬P e demonstra-se que isso leva a uma contradição.

**Estrutura:** Supor ¬P, derivar uma contradição (Q ∧ ¬Q), concluir P.

**Exemplo clássico na teoria da computação:** A prova de que a linguagem L = {aⁿbⁿ | n ≥ 0} não é regular utiliza o **Lema do Bombeamento**. Assume-se, por contradição, que L é regular e, portanto, satisfaz as condições do lema. Escolhe-se uma cadeia específica e demonstra-se que o bombeamento gera cadeias fora de L, contradizendo a hipótese.

### 6.3 Prova por Contrapositiva

Para provar p → q, prova-se a equivalente ¬q → ¬p.

**Exemplo:** Provar que, se L é uma linguagem infinita reconhecida por um AFD com n estados, então L contém uma cadeia w com |w| ≥ n. Pela contrapositiva: se L não contém nenhuma cadeia de comprimento ≥ n, então L é finita.

### 6.4 Indução Matemática

A indução é, possivelmente, a técnica de prova mais utilizada na teoria de linguagens formais.

#### Indução Simples (ou Fraca)

Para provar que uma propriedade P(n) vale para todo n ≥ n₀:

1. **Base:** Provar P(n₀).
2. **Passo indutivo:** Supor P(k) verdadeiro (hipótese de indução) e provar P(k + 1).

**Exemplo:** Provar que, para qualquer AFD, a função de transição estendida δ̂ satisfaz:

δ̂(q, xy) = δ̂(δ̂(q, x), y) para todos q ∈ Q e x, y ∈ Σ*

*Prova por indução no comprimento de y:*

*Base:* |y| = 0, ou seja, y = ε. Então δ̂(q, xε) = δ̂(q, x) = δ̂(δ̂(q, x), ε). ✓

*Passo indutivo:* Suponha que a propriedade vale para |y| = k. Seja y = y'a, com |y'| = k e a ∈ Σ. Então:

δ̂(q, xy) = δ̂(q, xy'a) = δ(δ̂(q, xy'), a)

Pela hipótese de indução, δ̂(q, xy') = δ̂(δ̂(q, x), y'). Logo:

δ̂(q, xy) = δ(δ̂(δ̂(q, x), y'), a) = δ̂(δ̂(q, x), y'a) = δ̂(δ̂(q, x), y) ∎

#### Indução Forte (ou Completa)

No passo indutivo, assume-se que P(j) vale para **todos** os j tais que n₀ ≤ j ≤ k, e prova-se P(k + 1).

A indução forte é particularmente útil em provas sobre gramáticas livres de contexto, onde uma derivação de comprimento k + 1 pode envolver subderivações de comprimento arbitrário menor que k + 1.

### 6.5 Prova Construtiva

Uma prova construtiva demonstra a existência de um objeto **construindo-o explicitamente**.

**Exemplo:** A prova de que, para todo AFN, existe um AFD equivalente é construtiva — o algoritmo de construção de subconjuntos produz explicitamente o AFD. Da mesma forma, a conversão de uma expressão regular em um AFN-ε (construção de Thompson) é uma prova construtiva de que toda linguagem descrita por uma expressão regular é reconhecida por um autômato finito.

---

## 7. Sequências, Tuplas e Cadeias

### 7.1 Tuplas

Uma **n-tupla** (ou tupla de ordem n) é uma sequência ordenada de n elementos:

(a₁, a₂, …, aₙ)

Diferentemente de conjuntos, em uma tupla a **ordem importa** e **repetições são significativas**:

- (1, 2, 3) ≠ (3, 2, 1) — a ordem importa
- (1, 1, 2) ≠ (1, 2) — a repetição é significativa

Tuplas com nomes especiais:

- 2-tupla: **par ordenado** (a, b)
- 3-tupla: **tripla** (a, b, c)
- 5-tupla: **quíntupla** (a, b, c, d, e)

**Relevância em linguagens formais:** Um autômato finito determinístico é formalmente definido como uma quíntupla:

M = (Q, Σ, δ, q₀, F)

onde Q é o conjunto de estados, Σ é o alfabeto, δ é a função de transição, q₀ é o estado inicial e F ⊆ Q é o conjunto de estados finais.

### 7.2 Sequências

Uma **sequência** é uma função cujo domínio é um subconjunto de ℕ (ou ℕ₀). Uma sequência finita (a₁, a₂, …, aₙ) corresponde a uma n-tupla. Uma sequência infinita (a₁, a₂, a₃, …) é denotada (aₙ)_{n≥1} ou simplesmente (aₙ).

### 7.3 Alfabetos e Cadeias

**Alfabeto:** Um **alfabeto** é um conjunto finito e não vazio de símbolos, convencionalmente denotado por Σ.

**Exemplos:**

- Σ = {0, 1} — alfabeto binário
- Σ = {a, b, c, …, z} — alfabeto latino minúsculo
- Σ = {0, 1, 2, …, 9, +, −, ×, ÷} — alfabeto aritmético

**Cadeia (ou palavra, ou string):** Uma **cadeia** sobre um alfabeto Σ é uma sequência finita de símbolos de Σ. A cadeia com zero símbolos é chamada **cadeia vazia** e denotada por **ε** (épsilon).

**Comprimento:** O **comprimento** de uma cadeia w, denotado |w|, é o número de símbolos (contando repetições) que a compõem.

- |abba| = 4
- |ε| = 0
- |aaa| = 3

### 7.4 Concatenação

A **concatenação** de duas cadeias w₁ e w₂, denotada w₁w₂ (ou w₁ · w₂), é a cadeia obtida justapondo-se os símbolos de w₂ após os de w₁.

**Propriedades:**

- **Associatividade:** (w₁w₂)w₃ = w₁(w₂w₃)
- **Elemento neutro:** wε = εw = w
- **Comprimento:** |w₁w₂| = |w₁| + |w₂|

A concatenação **não** é comutativa em geral: ab ≠ ba (quando a ≠ b).

**Potência de uma cadeia:** Define-se recursivamente:

- w⁰ = ε
- wⁿ = w · wⁿ⁻¹, para n ≥ 1

**Exemplo:** Se w = ab, então w³ = ababab.

Observe que (Σ*, ·, ε) forma um **monoide** — um conjunto dotado de uma operação associativa e um elemento neutro. Esta estrutura algébrica é fundamental para o estudo das linguagens formais: uma linguagem L sobre Σ é simplesmente um subconjunto de Σ*, ou seja, L ⊆ Σ*.

---

## 8. Fechamento (Closure)

### 8.1 Conceito de Fechamento

Dizemos que um conjunto S é **fechado** sob uma operação ⊕ se a aplicação de ⊕ a elementos de S sempre produz um resultado que também pertence a S:

(∀a, b ∈ S)(a ⊕ b ∈ S)

**Exemplo:** ℕ é fechado sob adição (a soma de dois naturais é um natural), mas **não** é fechado sob subtração (2 − 5 = −3 ∉ ℕ).

### 8.2 Fechamento de Classes de Linguagens

Na teoria de linguagens formais, estamos frequentemente interessados em saber se uma **classe** de linguagens é fechada sob determinadas operações. Dizer que as linguagens regulares são fechadas sob união significa que, se L₁ e L₂ são regulares, então L₁ ∪ L₂ também é regular.

As principais operações estudadas são: união, interseção, complemento, concatenação, estrela de Kleene e homomorfismo. Os resultados de fechamento diferem de classe para classe na hierarquia de Chomsky — e essas diferenças são ferramentas poderosas para demonstrar que determinadas linguagens **não** pertencem a certas classes.

### 8.3 Fecho de Kleene (Kleene Star)

O **fecho de Kleene** (ou estrela de Kleene) de um conjunto A, denotado A*, é a operação mais importante para a definição de linguagens formais. Nomeado em homenagem a **Stephen Cole Kleene** (1909–1994), que introduziu as expressões regulares em 1956, o fecho é definido como:

A* = A⁰ ∪ A¹ ∪ A² ∪ A³ ∪ …

onde as potências do conjunto são definidas recursivamente:

- A⁰ = {ε}
- Aⁿ = {xy | x ∈ Aⁿ⁻¹ ∧ y ∈ A}, para n ≥ 1

Equivalentemente:

A* = ⋃_{i=0}^{∞} Aⁱ

**Exemplo:** Seja Σ = {a, b}. Então:

- Σ⁰ = {ε}
- Σ¹ = {a, b}
- Σ² = {aa, ab, ba, bb}
- Σ³ = {aaa, aab, aba, abb, baa, bab, bba, bbb}
- Σ* = {ε, a, b, aa, ab, ba, bb, aaa, aab, …}

Σ* é o conjunto de **todas** as cadeias finitas sobre Σ, incluindo a cadeia vazia. É um conjunto infinito enumerável, mesmo quando Σ é finito.

### 8.4 Fecho Positivo (Positive Closure)

O **fecho positivo** de A, denotado A⁺, exclui a potência zero:

A⁺ = A¹ ∪ A² ∪ A³ ∪ … = ⋃_{i=1}^{∞} Aⁱ

A relação entre os dois fechos é:

- A* = A⁺ ∪ {ε}
- A⁺ = A* − {ε}, desde que ε ∉ A
- A⁺ = A · A* = A* · A

**Observação:** Se ε ∈ A, então A⁺ = A*, pois ε = εε ∈ A¹ ⊆ A⁺.

### 8.5 Linguagens como Conjuntos

Com os conceitos de alfabeto, cadeia e fecho de Kleene, podemos agora definir formalmente:

**Linguagem:** Uma **linguagem** L sobre um alfabeto Σ é qualquer subconjunto de Σ*:

L ⊆ Σ*

Exemplos:

- L₁ = ∅ — a linguagem vazia (sem nenhuma cadeia)
- L₂ = {ε} — a linguagem contendo apenas a cadeia vazia
- L₃ = {aⁿbⁿ | n ≥ 0} = {ε, ab, aabb, aaabbb, …} — uma linguagem livre de contexto
- L₄ = Σ* — a linguagem com todas as cadeias possíveis

**Operações sobre linguagens:**

Dadas linguagens L₁, L₂ ⊆ Σ*:

- **União:** L₁ ∪ L₂ = {w | w ∈ L₁ ∨ w ∈ L₂}
- **Concatenação:** L₁ · L₂ = {w₁w₂ | w₁ ∈ L₁ ∧ w₂ ∈ L₂}
- **Estrela de Kleene:** L₁* = ⋃_{i=0}^{∞} L₁ⁱ
- **Complemento:** L̄₁ = Σ* − L₁

Essas operações são os tijolos com os quais se constroem as **expressões regulares**, e os resultados de fechamento sobre elas determinam quais transformações preservam a regularidade (ou a livre-contextualidade, etc.) de uma linguagem.

---

## Referências

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. Tradução da 2ª edição. Rio de Janeiro: Elsevier, 2002. Título original: *Introduction to Automata Theory, Languages, and Computation*.

SIPSER, M. **Introdução à Teoria da Computação**. Tradução da 3ª edição. São Paulo: Cengage Learning, 2012. Título original: *Introduction to the Theory of Computation*.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6ª edição. Porto Alegre: Bookman (Série Livros Didáticos Informática UFRGS), 2010.

SUDKAMP, T. A. **Languages and Machines: An Introduction to the Theory of Computer Science**. 3rd edition. Boston: Addison-Wesley, 2006.

KLEENE, S. C. Representation of Events in Nerve Nets and Finite Automata. In: SHANNON, C. E.; McCARTHY, J. (ed.). **Automata Studies**. Princeton: Princeton University Press, 1956. p. 3–41.

CHOMSKY, N. Three Models for the Description of Language. **IRE Transactions on Information Theory**, v. 2, n. 3, p. 113–124, 1956.

CANTOR, G. Über eine Eigenschaft des Inbegriffes aller reellen algebraischen Zahlen. **Journal für die reine und angewandte Mathematik**, v. 77, p. 258–262, 1874.

BOOLE, G. **An Investigation of the Laws of Thought**. London: Walton and Maberly, 1854.
