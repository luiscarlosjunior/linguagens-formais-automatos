# Capítulo 2 — Alfabetos, Palavras, Linguagens, Gramáticas e Hierarquia de Linguagens

## 2.1 Introdução e Contexto Histórico

O estudo formal das linguagens constitui um dos pilares fundamentais da ciência da computação teórica. Para compreender a profundidade desse campo, é necessário retornar às suas origens históricas, que entrelaçam a linguística, a lógica matemática e a teoria da computação em uma síntese notável.

Em meados da década de 1950, o linguista e matemático **Noam Chomsky** publicou dois trabalhos seminais que transformariam permanentemente tanto a linguística quanto a ciência da computação. Em *"Three Models for the Description of Language"* (1956) e, posteriormente, em *"On Certain Formal Properties of Grammars"* (1959), Chomsky propôs uma classificação hierárquica das gramáticas formais em quatro tipos, cada um com poder gerativo distinto. Essa classificação — hoje universalmente conhecida como **Hierarquia de Chomsky** — estabeleceu uma correspondência profunda entre classes de gramáticas e classes de autômatos reconhecedores, unificando o estudo das linguagens formais sob um arcabouço matemático rigoroso.

O contexto histórico em que esses trabalhos surgiram é igualmente relevante. A ciência da computação vivia seu período formativo: Alan Turing havia formalizado o conceito de computação com suas máquinas abstratas em 1936; Alonzo Church desenvolvera o cálculo lambda; Stephen Kleene introduzira os conjuntos regulares e as expressões regulares (1956); e John Backus propusera a notação BNF (*Backus-Naur Form*) para descrever a sintaxe da linguagem FORTRAN. A confluência desses desenvolvimentos criou o terreno fértil no qual a teoria das linguagens formais floresceu.

Como observam Hopcroft, Ullman e Motwani (2006), a teoria das linguagens formais não é apenas um exercício abstrato — ela fundamenta áreas práticas essenciais como o projeto de compiladores, a verificação formal de programas, o processamento de linguagem natural e, mais recentemente, a bioinformática. Sipser (2012) reforça que os conceitos aqui apresentados constituem a base sobre a qual se constrói toda a teoria da computabilidade e da complexidade computacional.

Neste capítulo, construiremos sistematicamente os conceitos de alfabeto, palavra, linguagem e gramática formal, culminando na apresentação da Hierarquia de Chomsky e suas profundas implicações para a teoria da computação.

---

## 2.2 Alfabeto (Σ)

### 2.2.1 Definição Formal

> **Definição 2.1.** Um **alfabeto** (denotado por **Σ**) é um conjunto **finito** e **não vazio** de símbolos (também chamados de caracteres ou letras).

A exigência de finitude é essencial: embora as palavras construídas sobre um alfabeto possam ser infinitamente muitas, o conjunto de símbolos primitivos a partir dos quais elas são formadas deve ser necessariamente finito. Essa restrição reflete tanto a realidade prática dos sistemas computacionais quanto as necessidades da formalização matemática (Menezes, 2011).

### 2.2.2 Exemplos Fundamentais

| Alfabeto | Notação | Descrição |
|---|---|---|
| Alfabeto binário | Σ = {0, 1} | Base de toda a computação digital |
| Alfabeto ternário | Σ = {0, 1, 2} | Usado em algumas codificações |
| Letras latinas minúsculas | Σ = {a, b, c, …, z} | 26 símbolos |
| Alfabeto ASCII | Σ com 128 símbolos | Codificação padrão de caracteres |
| Alfabeto Unicode | Σ com 149.186+ símbolos | Codificação universal |
| Alfabeto do DNA | Σ = {A, C, G, T} | Bases nitrogenadas do ácido desoxirribonucleico |
| Alfabeto do RNA | Σ = {A, C, G, U} | Bases nitrogenadas do ácido ribonucleico |
| Alfabeto de aminoácidos | Σ com 20 símbolos | Código genético |

### 2.2.3 Convenções de Notação

Na literatura clássica (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012), as seguintes convenções são amplamente adotadas:

- **Σ** (sigma maiúsculo) denota o alfabeto.
- **a, b, c, d, …** (letras minúsculas do início do alfabeto latino) representam **símbolos** individuais de Σ.
- **w, x, y, z** (letras minúsculas do final do alfabeto latino) representam **palavras** (cadeias de símbolos).
- **A, B, C, S, …** (letras maiúsculas) representam **variáveis** (símbolos não terminais) em gramáticas.

### 2.2.4 Observações Importantes

1. Cada elemento de Σ é tratado como uma entidade **atômica** e **indivisível** — mesmo que visualmente pareça composto (por exemplo, o símbolo `if` pode ser um único elemento de um alfabeto de palavras reservadas).
2. A **cardinalidade** do alfabeto, denotada |Σ|, é sempre um inteiro positivo: |Σ| ≥ 1.
3. Dois alfabetos são iguais se, e somente se, contêm exatamente os mesmos símbolos: Σ₁ = Σ₂ ⟺ (∀a)(a ∈ Σ₁ ↔ a ∈ Σ₂).

---

## 2.3 Palavras (Cadeias / Strings)

### 2.3.1 Definição Formal

> **Definição 2.2.** Dado um alfabeto Σ, uma **palavra** (ou **cadeia**, ou **string**) sobre Σ é uma sequência **finita** de símbolos de Σ.

Formalmente, uma palavra **w** de comprimento **n** sobre Σ é uma função:

    w : {1, 2, …, n} → Σ

que associa a cada posição i (1 ≤ i ≤ n) um símbolo w(i) = aᵢ ∈ Σ. Representamos essa palavra pela justaposição de seus símbolos:

    w = a₁a₂a₃…aₙ

**Exemplo 2.1.** Seja Σ = {a, b, c}. As seguintes são palavras sobre Σ:

- `abc` (comprimento 3)
- `aabbc` (comprimento 5)
- `a` (comprimento 1)
- `ccccc` (comprimento 5)

### 2.3.2 Palavra Vazia (ε)

> **Definição 2.3.** A **palavra vazia**, denotada por **ε** (epsilon), é a única palavra de comprimento zero. Ela não contém nenhum símbolo.

A palavra vazia é um conceito central na teoria — ela atua como elemento neutro da concatenação (ver Seção 2.3.4) e desempenha papel análogo ao do zero na aritmética ou ao do conjunto vazio na teoria dos conjuntos. Observe que **ε não é um símbolo do alfabeto**; é uma construção metalinguística que denota a ausência de símbolos.

Sudkamp (2005) enfatiza que, embora ε não pertença a nenhum alfabeto, ela é uma palavra válida sobre qualquer alfabeto.

### 2.3.3 Comprimento de uma Palavra

> **Definição 2.4.** O **comprimento** (ou **tamanho**) de uma palavra **w**, denotado por **|w|**, é o número de símbolos que compõem **w** (contando repetições).

**Propriedades:**

- |ε| = 0
- Se w = a₁a₂…aₙ, então |w| = n
- Para todo símbolo a ∈ Σ: |a| = 1

**Número de ocorrências:** Denotamos por **|w|ₐ** o número de ocorrências do símbolo **a** na palavra **w**.

**Exemplo 2.2.** Seja w = `abba` sobre Σ = {a, b}:

- |w| = 4
- |w|ₐ = 2
- |w|_ᵦ = 2

### 2.3.4 Concatenação de Palavras

> **Definição 2.5.** A **concatenação** de duas palavras **u** = a₁a₂…aₘ e **v** = b₁b₂…bₙ, denotada por **uv** (ou **u · v**), é a palavra:
>
>     uv = a₁a₂…aₘb₁b₂…bₙ

A concatenação é a operação fundamental sobre palavras — ela constrói palavras maiores a partir de palavras menores por justaposição.

**Propriedades algébricas da concatenação:**

| Propriedade | Enunciado | Observação |
|---|---|---|
| **Associatividade** | (uv)w = u(vw), para todas as palavras u, v, w | Podemos escrever uvw sem ambiguidade |
| **Elemento neutro** | εw = wε = w, para toda palavra w | ε é a identidade da concatenação |
| **Comprimento** | \|uv\| = \|u\| + \|v\| | O comprimento é homomorfismo para (ℕ, +) |
| **Não comutatividade** | Em geral, uv ≠ vu | Exemplo: ab ≠ ba |

> **Observação.** O conjunto Σ* munido da operação de concatenação e do elemento neutro ε forma um **monóide livre** gerado por Σ, uma estrutura algébrica de grande importância teórica (Hopcroft, Ullman & Motwani, 2006).

### 2.3.5 Reverso (Inverso) de uma Palavra

> **Definição 2.6.** O **reverso** (ou **inverso**) de uma palavra **w** = a₁a₂…aₙ, denotado por **wᴿ**, é a palavra obtida pela leitura de **w** da direita para a esquerda:
>
>     wᴿ = aₙaₙ₋₁…a₂a₁

**Definição recursiva:**

- εᴿ = ε
- (wa)ᴿ = a(wᴿ), para toda palavra w e símbolo a ∈ Σ

**Propriedades do reverso:**

1. (wᴿ)ᴿ = w (involução)
2. |wᴿ| = |w|
3. (uv)ᴿ = vᴿuᴿ (anti-homomorfismo)

> **Definição 2.7.** Uma palavra **w** é um **palíndromo** se, e somente se, w = wᴿ.

**Exemplo 2.3.** Seja w = `abba`. Então wᴿ = `abba` = w, logo `abba` é um palíndromo.

### 2.3.6 Potência de uma Palavra

> **Definição 2.8.** A **n-ésima potência** de uma palavra **w**, denotada por **wⁿ**, é definida recursivamente:
>
> - w⁰ = ε
> - wⁿ = w · wⁿ⁻¹, para n ≥ 1

Equivalentemente, wⁿ é a concatenação de **w** consigo mesma **n** vezes.

**Exemplo 2.4.** Seja w = `ab`:

- w⁰ = ε
- w¹ = ab
- w² = abab
- w³ = ababab

**Propriedade:** |wⁿ| = n · |w|

### 2.3.7 Prefixo, Sufixo e Subpalavra

> **Definição 2.9.** Dada uma palavra w:
>
> - **x** é **prefixo** de **w** se existe y tal que w = xy.
> - **y** é **sufixo** de **w** se existe x tal que w = xy.
> - **z** é **subpalavra** (ou **fator**) de **w** se existem x, y tais que w = xzy.

Um prefixo (ou sufixo) é dito **próprio** se é diferente de ε e de w.

**Exemplo 2.5.** Seja w = `abc`:

- Prefixos: ε, a, ab, abc
- Sufixos: ε, c, bc, abc
- Subpalavras: ε, a, b, c, ab, bc, abc

---

## 2.4 Σ* e Σ⁺ (Fecho de Kleene e Fecho Positivo)

### 2.4.1 Potência de um Alfabeto

> **Definição 2.10.** A **n-ésima potência** de um alfabeto Σ, denotada **Σⁿ**, é o conjunto de todas as palavras de comprimento exatamente **n** sobre Σ:
>
>     Σ⁰ = {ε}
>     Σ¹ = Σ
>     Σⁿ = {w₁w₂ : w₁ ∈ Σⁿ⁻¹, w₂ ∈ Σ}, para n ≥ 2

**Observação:** |Σⁿ| = |Σ|ⁿ — o número de palavras de comprimento n sobre um alfabeto de k símbolos é kⁿ.

### 2.4.2 Fecho de Kleene (Σ*)

> **Definição 2.11.** O **fecho de Kleene** (ou **estrela de Kleene**) de um alfabeto Σ, denotado **Σ\***, é o conjunto de **todas** as palavras de comprimento finito sobre Σ, **incluindo a palavra vazia**:
>
>     Σ* = Σ⁰ ∪ Σ¹ ∪ Σ² ∪ Σ³ ∪ … = ⋃ᵢ₌₀^∞ Σⁱ

O nome homenageia **Stephen Cole Kleene** (1909–1994), lógico e matemático norte-americano que introduziu os conceitos de conjuntos regulares e expressões regulares em seu trabalho seminal de 1956, *"Representation of Events in Nerve Nets and Finite Automata"*.

**Propriedades fundamentais de Σ*:**

1. ε ∈ Σ*, para qualquer alfabeto Σ.
2. Σ ⊂ Σ* (todo símbolo é uma palavra de comprimento 1).
3. Σ* é **infinito enumerável** (|Σ*| = ℵ₀).
4. Σ* é **fechado sob concatenação**: se u, v ∈ Σ*, então uv ∈ Σ*.

### 2.4.3 Fecho Positivo (Σ⁺)

> **Definição 2.12.** O **fecho positivo** de um alfabeto Σ, denotado **Σ⁺**, é o conjunto de todas as palavras de comprimento **pelo menos 1** sobre Σ:
>
>     Σ⁺ = Σ¹ ∪ Σ² ∪ Σ³ ∪ … = ⋃ᵢ₌₁^∞ Σⁱ

**Relação entre Σ* e Σ⁺:**

    Σ* = Σ⁺ ∪ {ε}
    Σ⁺ = Σ* − {ε}
    Σ⁺ = Σ · Σ* = Σ* · Σ

### 2.4.4 Exemplo Detalhado

Seja Σ = {a, b}:

- Σ⁰ = {ε}
- Σ¹ = {a, b}
- Σ² = {aa, ab, ba, bb}
- Σ³ = {aaa, aab, aba, abb, baa, bab, bba, bbb}

Portanto:

    Σ* = {ε, a, b, aa, ab, ba, bb, aaa, aab, aba, abb, baa, bab, bba, bbb, …}
    Σ⁺ = {a, b, aa, ab, ba, bb, aaa, aab, aba, abb, baa, bab, bba, bbb, …}

Note que Σ* é um conjunto **infinito** — mesmo para o menor alfabeto possível (|Σ| = 1), temos |Σ*| = ℵ₀ (a cardinalidade dos números naturais).

---

## 2.5 Linguagens

### 2.5.1 Definição Formal

> **Definição 2.13.** Uma **linguagem** **L** sobre um alfabeto Σ é qualquer subconjunto de Σ*:
>
>     L ⊆ Σ*

Essa definição — aparentemente simples — é de uma generalidade extraordinária. Ela abarca desde linguagens triviais (como o conjunto vazio) até linguagens de enorme complexidade (como o conjunto de todos os programas válidos em uma linguagem de programação). Como observa Sipser (2012), a simplicidade da definição contrasta com a riqueza e a profundidade da teoria que dela emerge.

### 2.5.2 Linguagens Importantes

| Linguagem | Notação | Descrição |
|---|---|---|
| **Linguagem vazia** | ∅ | Não contém nenhuma palavra |
| **Linguagem contendo apenas ε** | {ε} | Contém apenas a palavra vazia |
| **Linguagem universal** | Σ* | Contém todas as palavras sobre Σ |

> **Atenção — Distinção crucial:** ∅ ≠ {ε}. A linguagem vazia ∅ não possui nenhum elemento; a linguagem {ε} possui exatamente um elemento (a palavra vazia). Menezes (2011) enfatiza que essa distinção, embora sutil, é fonte frequente de confusão entre estudantes.

### 2.5.3 Exemplos de Linguagens

Dado Σ = {a, b}:

1. **Linguagem finita:** L₁ = {a, ab, abb} — contém exatamente 3 palavras.
2. **Linguagem infinita:** L₂ = {aⁿbⁿ : n ≥ 0} = {ε, ab, aabb, aaabbb, …} — o conjunto de todas as palavras com n cópias de 'a' seguidas de n cópias de 'b'.
3. **Linguagem dos palíndromos:** L₃ = {w ∈ Σ* : w = wᴿ} = {ε, a, b, aa, bb, aaa, aba, bab, bbb, …}
4. **Linguagem das palavras com igual número de a's e b's:** L₄ = {w ∈ Σ* : |w|ₐ = |w|_b}

### 2.5.4 Cardinalidade

Uma observação combinatória profunda: como Σ* é infinito enumerável e toda linguagem é um subconjunto de Σ*, o conjunto de **todas** as linguagens sobre Σ é o conjunto potência 𝒫(Σ*), que é **não enumerável** (pelo teorema de Cantor, |𝒫(Σ*)| = 2^ℵ₀ = |ℝ|). Por outro lado, o conjunto de todas as gramáticas (e de todos os programas) é enumerável. Essa assimetria fundamental implica que **existem linguagens que não podem ser descritas por nenhuma gramática finita nem reconhecidas por nenhuma máquina de Turing** — um resultado central na teoria da computabilidade (Sipser, 2012).

### 2.5.5 Operações sobre Linguagens

Sejam L, L₁ e L₂ linguagens sobre Σ.

#### União

> L₁ ∪ L₂ = {w : w ∈ L₁ ou w ∈ L₂}

#### Interseção

> L₁ ∩ L₂ = {w : w ∈ L₁ e w ∈ L₂}

#### Complemento

> L̄ = Σ* − L = {w ∈ Σ* : w ∉ L}

#### Diferença

> L₁ − L₂ = {w : w ∈ L₁ e w ∉ L₂} = L₁ ∩ L̄₂

#### Concatenação de Linguagens

> L₁ · L₂ = L₁L₂ = {uv : u ∈ L₁ e v ∈ L₂}

**Exemplo 2.6.** Sejam L₁ = {a, ab} e L₂ = {b, ba}. Então:

    L₁L₂ = {ab, aba, abb, abba}

#### Potência de uma Linguagem

> - L⁰ = {ε}
> - Lⁿ = L · Lⁿ⁻¹, para n ≥ 1

#### Fecho de Kleene de uma Linguagem

> L* = ⋃ᵢ₌₀^∞ Lⁱ = L⁰ ∪ L¹ ∪ L² ∪ L³ ∪ …

#### Fecho Positivo de uma Linguagem

> L⁺ = ⋃ᵢ₌₁^∞ Lⁱ = L¹ ∪ L² ∪ L³ ∪ …

**Relação:** L* = L⁺ ∪ {ε} e L⁺ = L · L* = L* · L.

### 2.5.6 Propriedades das Operações

| Propriedade | Expressão |
|---|---|
| Associatividade da união | (L₁ ∪ L₂) ∪ L₃ = L₁ ∪ (L₂ ∪ L₃) |
| Comutatividade da união | L₁ ∪ L₂ = L₂ ∪ L₁ |
| Associatividade da concatenação | (L₁L₂)L₃ = L₁(L₂L₃) |
| Elemento neutro da concatenação | L{ε} = {ε}L = L |
| Elemento absorvente da concatenação | L∅ = ∅L = ∅ |
| Distributividade | L₁(L₂ ∪ L₃) = L₁L₂ ∪ L₁L₃ |
| Idempotência do fecho | (L*)* = L* |
| Fecho da linguagem vazia | ∅* = {ε} |
| Fecho de {ε} | {ε}* = {ε} |
| Leis de De Morgan | (L₁ ∪ L₂)̄ = L̄₁ ∩ L̄₂ e (L₁ ∩ L₂)̄ = L̄₁ ∪ L̄₂ |

---

## 2.6 Gramáticas Formais

### 2.6.1 Motivação

Uma gramática formal é um **mecanismo finito** capaz de gerar (potencialmente) um **conjunto infinito** de palavras — isto é, uma linguagem. A ideia de descrever linguagens por meio de regras de reescrita tem raízes profundas na linguística (as gramáticas das línguas naturais) e na lógica (os sistemas formais de Post e Thue). Chomsky (1956) formalizou essa ideia de maneira precisa e universal.

### 2.6.2 Definição Formal

> **Definição 2.14.** Uma **gramática formal** (ou simplesmente **gramática**) é uma quádrupla ordenada:
>
>     G = (V, Σ, P, S)
>
> onde:
>
> - **V** é um conjunto finito e não vazio de **variáveis** (ou **símbolos não terminais**);
> - **Σ** é um conjunto finito e não vazio de **símbolos terminais**, com V ∩ Σ = ∅;
> - **P** é um conjunto finito de **regras de produção** (ou **produções**);
> - **S** ∈ V é o **símbolo inicial** (ou **axioma**) da gramática.

O conjunto V ∪ Σ é frequentemente chamado de **vocabulário** da gramática. As regras de produção têm a forma geral:

    α → β

onde α ∈ (V ∪ Σ)⁺ (uma cadeia não vazia de variáveis e/ou terminais) e β ∈ (V ∪ Σ)* (uma cadeia possivelmente vazia).

### 2.6.3 Derivações

> **Definição 2.15.** Dada uma gramática G = (V, Σ, P, S), dizemos que uma cadeia **γ** é **derivada diretamente** de uma cadeia **δ**, escrevendo:
>
>     δ ⇒ γ
>
> se existem cadeias u, v ∈ (V ∪ Σ)* e uma produção (α → β) ∈ P tais que:
>
>     δ = uαv  e  γ = uβv

Informalmente: uma derivação direta é a aplicação de uma regra de produção a uma subcadeia de δ, substituindo α por β.

> **Definição 2.16.** A relação **⇒\*** (derivação em zero ou mais passos) é o fecho reflexivo-transitivo de **⇒**:
>
> - δ ⇒* δ (reflexividade: zero passos)
> - Se δ ⇒* γ e γ ⇒ η, então δ ⇒* η (transitividade)

### 2.6.4 Formas Sentenciais e Linguagem Gerada

> **Definição 2.17.** Uma **forma sentencial** de G é qualquer cadeia α ∈ (V ∪ Σ)* tal que S ⇒* α.

> **Definição 2.18.** Uma **sentença** de G é uma forma sentencial que contém apenas símbolos terminais: w ∈ Σ* tal que S ⇒* w.

> **Definição 2.19.** A **linguagem gerada** por uma gramática G, denotada **L(G)**, é o conjunto de todas as sentenças de G:
>
>     L(G) = {w ∈ Σ* : S ⇒* w}

### 2.6.5 Exemplo Completo

**Exemplo 2.7.** Considere a gramática G₁ = (V, Σ, P, S) onde:

- V = {S}
- Σ = {a, b}
- P = {S → aSb, S → ε}

**Derivação de `aabb`:**

    S ⇒ aSb ⇒ aaSbb ⇒ aaεbb = aabb

Portanto, `aabb` ∈ L(G₁). De forma geral:

    L(G₁) = {aⁿbⁿ : n ≥ 0}

Esta é a clássica linguagem das palavras com n cópias de 'a' seguidas de n cópias de 'b', frequentemente utilizada como exemplo de linguagem livre de contexto que **não** é regular (Hopcroft, Ullman & Motwani, 2006).

**Exemplo 2.8.** Considere a gramática G₂ = (V, Σ, P, S) onde:

- V = {S, A}
- Σ = {0, 1}
- P = {S → 0A, S → 1A, S → 0, S → 1, A → 0S, A → 1S}

**Derivação de `010`:**

    S ⇒ 0A ⇒ 01S ⇒ 010

A linguagem L(G₂) é o conjunto de todas as palavras binárias de comprimento ímpar:

    L(G₂) = {w ∈ {0,1}* : |w| é ímpar}

**Exemplo 2.9.** Considere a gramática G₃ = ({S, B, C}, {a, b, c}, P, S) com:

- P = {S → aSBC, S → aBC, CB → BC, aB → ab, bB → bb, bC → bc, cC → cc}

**Derivação de `aabbcc`:**

    S ⇒ aSBC ⇒ aaBCBC ⇒ aaBBCC ⇒ aabBCC ⇒ aabbCC ⇒ aabbcC ⇒ aabbcc

Essa gramática gera L(G₃) = {aⁿbⁿcⁿ : n ≥ 1}, uma linguagem sensível ao contexto que **não** é livre de contexto — resultado demonstrável pelo Lema do Bombeamento para linguagens livres de contexto (Sipser, 2012).

### 2.6.6 Equivalência de Gramáticas

> **Definição 2.20.** Duas gramáticas G₁ e G₂ são **equivalentes** se geram a mesma linguagem:
>
>     G₁ ≡ G₂ ⟺ L(G₁) = L(G₂)

Uma mesma linguagem pode ser gerada por infinitas gramáticas distintas — a gramática é o **mecanismo gerador**, não a linguagem em si.

---

## 2.7 Hierarquia de Chomsky

### 2.7.1 Visão Geral

A **Hierarquia de Chomsky** classifica as gramáticas formais em quatro tipos, numerados de 0 a 3, segundo restrições progressivamente mais severas impostas às regras de produção. Cada tipo define uma classe de gramáticas que gera uma classe correspondente de linguagens, reconhecível por uma classe correspondente de autômatos. Essa correspondência tripla — gramática ↔ linguagem ↔ autômato — é uma das estruturas mais elegantes e fundamentais de toda a ciência da computação teórica.

```
┌─────────────────────────────────────────────────────────────────┐
│                   Tipo 0 — Irrestritas                          │
│         (Recursivamente Enumeráveis / Máquinas de Turing)       │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │              Tipo 1 — Sensíveis ao Contexto               │  │
│  │           (Autômatos Linearmente Limitados)                │  │
│  │  ┌─────────────────────────────────────────────────────┐  │  │
│  │  │          Tipo 2 — Livres de Contexto                │  │  │
│  │  │           (Autômatos com Pilha)                      │  │  │
│  │  │  ┌───────────────────────────────────────────────┐  │  │  │
│  │  │  │         Tipo 3 — Regulares                    │  │  │  │
│  │  │  │         (Autômatos Finitos)                    │  │  │  │
│  │  │  └───────────────────────────────────────────────┘  │  │  │
│  │  └─────────────────────────────────────────────────────┘  │  │
│  └───────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

### 2.7.2 Tipo 3 — Gramáticas Regulares

> **Definição 2.21.** Uma gramática G = (V, Σ, P, S) é **regular** (Tipo 3) se todas as suas produções têm uma das seguintes formas:
>
> **Gramática linear à direita:**
> - A → aB (onde A, B ∈ V e a ∈ Σ)
> - A → a (onde A ∈ V e a ∈ Σ)
> - A → ε (onde A ∈ V)
>
> **Gramática linear à esquerda:**
> - A → Ba (onde A, B ∈ V e a ∈ Σ)
> - A → a (onde A ∈ V e a ∈ Σ)
> - A → ε (onde A ∈ V)

**Restrição fundamental:** O lado esquerdo de cada produção é uma única variável, e o lado direito contém **no máximo uma variável**, que aparece na posição extrema (à direita ou à esquerda).

**Linguagens reconhecidas:** **Linguagens regulares**, reconhecidas por **autômatos finitos** (determinísticos ou não determinísticos) e descritas por **expressões regulares**.

**Exemplos de linguagens regulares:**

- L = {w ∈ {a,b}* : w contém um número par de a's}
- L = {w ∈ {0,1}* : w termina em 01}
- Qualquer linguagem finita

**Exemplos de linguagens NÃO regulares:**

- L = {aⁿbⁿ : n ≥ 0} (requer contagem ilimitada)
- L = {ww : w ∈ {a,b}*} (requer memória da primeira metade)

**Propriedades de fechamento:** As linguagens regulares são fechadas sob união, interseção, complemento, concatenação, fecho de Kleene, reverso, homomorfismo e homomorfismo inverso.

### 2.7.3 Tipo 2 — Gramáticas Livres de Contexto

> **Definição 2.22.** Uma gramática G = (V, Σ, P, S) é **livre de contexto** (Tipo 2) se todas as suas produções têm a forma:
>
>     A → α
>
> onde A ∈ V (uma única variável) e α ∈ (V ∪ Σ)* (qualquer cadeia de variáveis e terminais, incluindo ε).

**Restrição fundamental:** O lado esquerdo de cada produção é **exatamente uma variável**; o lado direito é irrestrito. Isso significa que a variável A pode ser substituída por α **independentemente do contexto** em que A aparece — daí o nome "livre de contexto".

**Linguagens reconhecidas:** **Linguagens livres de contexto** (LLCs), reconhecidas por **autômatos com pilha** (pushdown automata).

**Importância prática:** As gramáticas livres de contexto são o formalismo padrão para a descrição da **sintaxe** das linguagens de programação. A notação BNF (Backus-Naur Form), amplamente utilizada em especificações de linguagens, é essencialmente uma representação alternativa de gramáticas livres de contexto (Hopcroft, Ullman & Motwani, 2006).

**Exemplo de gramática livre de contexto para expressões aritméticas:**

    G = ({E, T, F}, {+, *, (, ), id}, P, E)
    P = {
        E → E + T | T,
        T → T * F | F,
        F → (E) | id
    }

**Propriedades de fechamento:** As linguagens livres de contexto são fechadas sob união, concatenação e fecho de Kleene, mas **não** são fechadas sob interseção nem sob complemento.

### 2.7.4 Tipo 1 — Gramáticas Sensíveis ao Contexto

> **Definição 2.23.** Uma gramática G = (V, Σ, P, S) é **sensível ao contexto** (Tipo 1) se todas as suas produções têm a forma:
>
>     αAβ → αγβ
>
> onde A ∈ V, α, β ∈ (V ∪ Σ)* e γ ∈ (V ∪ Σ)⁺ (γ não pode ser vazio).

**Restrição fundamental:** A variável A é substituída por γ apenas quando está no **contexto** de α à esquerda e β à direita. Além disso, nenhuma produção pode diminuir o comprimento da cadeia (|αAβ| ≤ |αγβ|), exceto possivelmente S → ε, desde que S não apareça no lado direito de nenhuma produção.

Uma forma equivalente da restrição: para toda produção (δ → η) ∈ P, exige-se que |δ| ≤ |η|.

**Linguagens reconhecidas:** **Linguagens sensíveis ao contexto**, reconhecidas por **autômatos linearmente limitados** (máquinas de Turing com fita limitada ao tamanho da entrada).

**Exemplo:** A linguagem L = {aⁿbⁿcⁿ : n ≥ 1} é sensível ao contexto mas não é livre de contexto.

**Propriedades de fechamento:** As linguagens sensíveis ao contexto são fechadas sob união, interseção, complemento, concatenação e fecho de Kleene.

### 2.7.5 Tipo 0 — Gramáticas Irrestritas

> **Definição 2.24.** Uma gramática G = (V, Σ, P, S) é **irrestrita** (Tipo 0) se suas produções têm a forma geral:
>
>     α → β
>
> onde α ∈ (V ∪ Σ)⁺ e β ∈ (V ∪ Σ)*, sem nenhuma restrição adicional.

**Restrição:** Não há restrição — qualquer cadeia não vazia pode ser reescrita como qualquer cadeia (incluindo ε).

**Linguagens reconhecidas:** **Linguagens recursivamente enumeráveis** (r.e.), reconhecidas por **máquinas de Turing** (que podem não parar para entradas que não pertencem à linguagem).

**Observação:** Um subconjunto importante das linguagens r.e. são as **linguagens recursivas** (ou decidíveis), para as quais existe uma máquina de Turing que **sempre para**, aceitando ou rejeitando. Toda linguagem recursiva é r.e., mas nem toda linguagem r.e. é recursiva — o exemplo clássico é o problema da parada (Sipser, 2012).

### 2.7.6 Tabela Resumo da Hierarquia de Chomsky

| Tipo | Gramática | Linguagem | Autômato | Restrição nas Produções |
|---|---|---|---|---|
| **3** | Regular | Regular | Autômato Finito (AF) | A → aB, A → a, A → ε |
| **2** | Livre de Contexto | Livre de Contexto (LLC) | Autômato com Pilha (AP) | A → α (A ∈ V, α ∈ (V∪Σ)*) |
| **1** | Sensível ao Contexto | Sensível ao Contexto (LSC) | Autômato Lin. Limitado (ALL) | αAβ → αγβ (γ ≠ ε) |
| **0** | Irrestrita | Recursivamente Enumerável (RE) | Máquina de Turing (MT) | α → β (sem restrição) |

### 2.7.7 Relações de Contenção

A hierarquia é **própria** — cada classe é estritamente contida na classe superior:

    Regulares ⊂ Livres de Contexto ⊂ Sensíveis ao Contexto ⊂ Recursivamente Enumeráveis

Ou, em notação formal:

    ℒ₃ ⊂ ℒ₂ ⊂ ℒ₁ ⊂ ℒ₀

**Linguagens testemunho da separação:**

| Separação | Linguagem testemunho | Justificação |
|---|---|---|
| ℒ₃ ⊂ ℒ₂ | {aⁿbⁿ : n ≥ 0} | LLC mas não regular (Lema do Bombeamento para LRs) |
| ℒ₂ ⊂ ℒ₁ | {aⁿbⁿcⁿ : n ≥ 1} | LSC mas não LLC (Lema do Bombeamento para LLCs) |
| ℒ₁ ⊂ ℒ₀ | Complemento de linguagens r.e. não recursivas | RE mas não LSC |

Além dessas quatro classes, existem **linguagens que não pertencem a nenhum tipo** — linguagens que não são sequer recursivamente enumeráveis, como o complemento do problema da parada.

### 2.7.8 Significado Fundamental da Hierarquia

A Hierarquia de Chomsky é fundamental por múltiplas razões:

1. **Unificação:** Ela conecta três formalismos distintos — gramáticas, linguagens e autômatos — em uma estrutura coerente e elegante.

2. **Poder expressivo vs. decidibilidade:** À medida que se sobe na hierarquia, o poder expressivo das gramáticas aumenta, mas as propriedades algorítmicas deterioram-se. Essa é uma instância particular de um princípio geral: **maior poder expressivo implica menor decidibilidade**.

3. **Guia para projeto de linguagens:** A hierarquia informa decisões práticas no projeto de linguagens de programação. A maioria das linguagens de programação tem sintaxe livre de contexto (Tipo 2) e semântica que pode requerer sensibilidade ao contexto (Tipo 1) ou mais.

4. **Ponte entre áreas:** Ela conecta a linguística formal, a teoria dos autômatos, a lógica matemática e a teoria da complexidade computacional.

---

## 2.8 Problemas e Aplicações

### 2.8.1 Decidibilidade em Cada Nível

Uma das contribuições mais profundas da Hierarquia de Chomsky é a revelação de como a **decidibilidade** de problemas fundamentais varia conforme o nível:

| Problema | Tipo 3 (Regular) | Tipo 2 (LLC) | Tipo 1 (LSC) | Tipo 0 (RE) |
|---|---|---|---|---|
| Pertinência (w ∈ L?) | **Decidível** O(n) | **Decidível** O(n³) | **Decidível** | **Indecidível** (semi-decidível) |
| Vacuidade (L = ∅?) | **Decidível** | **Decidível** | **Indecidível** | **Indecidível** |
| Equivalência (L₁ = L₂?) | **Decidível** | **Indecidível** | **Indecidível** | **Indecidível** |
| Universalidade (L = Σ*?) | **Decidível** | **Indecidível** | **Indecidível** | **Indecidível** |
| Ambiguidade da gramática | N/A | **Indecidível** | **Indecidível** | **Indecidível** |

Essa degradação progressiva da decidibilidade é um dos teoremas mais impactantes da teoria da computação. Como destaca Sipser (2012), ela demonstra que **existem limites fundamentais ao que pode ser algoritmicamente determinado**, mesmo sobre objetos matemáticos aparentemente simples como linguagens formais.

### 2.8.2 Aplicações Práticas

#### Compiladores e Interpretadores

A aplicação mais direta e historicamente importante da teoria das linguagens formais é no **projeto de compiladores**:

- **Análise léxica** utiliza **autômatos finitos** e **expressões regulares** (Tipo 3) para identificar tokens (palavras reservadas, identificadores, literais numéricos).
- **Análise sintática** utiliza **gramáticas livres de contexto** (Tipo 2) e **autômatos com pilha** para verificar a estrutura gramatical do programa (parsers LL, LR, LALR).
- **Análise semântica** frequentemente requer mecanismos equivalentes a gramáticas sensíveis ao contexto (Tipo 1) ou além, para verificar regras como compatibilidade de tipos e escopo de variáveis.

#### Processamento de Linguagem Natural (PLN)

A motivação original de Chomsky era linguística, e as gramáticas formais continuam sendo ferramentas essenciais no PLN:

- Gramáticas livres de contexto probabilísticas (PCFGs) para análise sintática de sentenças.
- Gramáticas de dependência e gramáticas categoriais.
- Modelos de linguagem que, embora baseados em abordagens estatísticas e redes neurais, frequentemente incorporam estruturas gramaticais formais.

#### Bioinformática

A teoria das linguagens formais encontrou aplicações surpreendentes na bioinformática:

- **Sequências de DNA e RNA** são palavras sobre os alfabetos {A, C, G, T} e {A, C, G, U}.
- **Estruturas secundárias de RNA** apresentam pareamento de bases (como parênteses balanceados), o que é naturalmente modelado por **gramáticas livres de contexto estocásticas** (SCFGs).
- **Alinhamento de sequências** e **busca de padrões** utilizam técnicas derivadas da teoria de autômatos.

#### Verificação Formal e Model Checking

- **Lógica temporal** e **autômatos de Büchi** (extensões de autômatos finitos para palavras infinitas) são utilizados na verificação de propriedades de sistemas concorrentes.
- **Gramáticas de grafos** generalizam gramáticas de cadeias para a verificação de propriedades estruturais de programas.

#### Segurança da Informação

- **Expressões regulares** são amplamente utilizadas em sistemas de detecção de intrusão, validação de entradas e filtragem de conteúdo.
- A análise de **protocolos criptográficos** frequentemente emprega modelos baseados em autômatos.

---

## Referências

CHOMSKY, N. Three models for the description of language. *IRE Transactions on Information Theory*, v. 2, n. 3, p. 113–124, 1956.

CHOMSKY, N. On certain formal properties of grammars. *Information and Control*, v. 2, n. 2, p. 137–167, 1959.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. *Introduction to Automata Theory, Languages, and Computation*. 3. ed. Boston: Addison-Wesley, 2006.

KLEENE, S. C. Representation of events in nerve nets and finite automata. In: SHANNON, C. E.; MCCARTHY, J. (Org.). *Automata Studies*. Princeton: Princeton University Press, 1956. p. 3–42.

MENEZES, P. B. *Linguagens Formais e Autômatos*. 6. ed. Porto Alegre: Bookman (Série Livros Didáticos Informática UFRGS), 2011.

SIPSER, M. *Introduction to the Theory of Computation*. 3. ed. Boston: Cengage Learning, 2012.

SUDKAMP, T. A. *Languages and Machines: An Introduction to the Theory of Computer Science*. 3. ed. Boston: Addison-Wesley, 2005.

TURING, A. M. On computable numbers, with an application to the Entscheidungsproblem. *Proceedings of the London Mathematical Society*, v. 2, n. 42, p. 230–265, 1936.
