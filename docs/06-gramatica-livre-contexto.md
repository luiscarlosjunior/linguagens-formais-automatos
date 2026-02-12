# Capítulo 6 — Gramática Livre de Contexto e Autômato com Pilha

## 6.1 Introdução e Contexto Histórico

O estudo das **gramáticas livres de contexto** (GLCs) constitui um dos capítulos mais ricos e influentes da teoria das linguagens formais. Sua história entrelaça dois campos aparentemente distintos — a linguística matemática e a ciência da computação nascente — que convergiram, de forma independente, para a mesma estrutura formal na segunda metade da década de 1950.

Em 1956, o linguista Noam **Chomsky** introduziu a hierarquia de gramáticas formais que hoje leva seu nome, visando modelar a estrutura sintática das línguas naturais. Nessa hierarquia, as gramáticas livres de contexto correspondem ao **Tipo 2**, situando-se entre as gramáticas regulares (Tipo 3) e as gramáticas sensíveis ao contexto (Tipo 1). Chomsky observou que gramáticas regulares eram insuficientes para capturar fenômenos sintáticos como o aninhamento recursivo (*center-embedding*), e que as regras da forma A → α — onde A é um único símbolo não-terminal e α é uma sequência arbitrária de terminais e não-terminais — ofereciam o grau de expressividade necessário para descrever grande parte da sintaxe linguística (Chomsky, 1956; 1959).

De forma independente e quase simultânea, **John Backus** (1959) desenvolveu uma notação formal para descrever a sintaxe da linguagem de programação ALGOL 58, posteriormente refinada por **Peter Naur** para o relatório do ALGOL 60. Essa notação — hoje conhecida como **Forma de Backus-Naur** (BNF, *Backus-Naur Form*) — é, em essência, uma representação concreta de gramáticas livres de contexto. A BNF tornou-se o padrão para a especificação de linguagens de programação e permanece ubíqua em manuais de referência, documentos de padronização (como os RFCs da Internet) e ferramentas de geração automática de parsers.

A convergência entre os trabalhos de Chomsky e de Backus-Naur revelou que a mesma classe de gramáticas era indispensável tanto para a análise da linguagem natural quanto para o projeto e a implementação de linguagens de programação. A partir da década de 1960, resultados teóricos fundamentais consolidaram o campo: os **autômatos com pilha** (*pushdown automata*, PDA), introduzidos por Oettinger (1961) e formalizados por Chomsky (1962) e Evey (1963), foram demonstrados equivalentes em poder expressivo às GLCs; algoritmos de análise sintática eficientes — como o algoritmo CYK (Cocke, Younger e Kasami, independentemente na década de 1960) e o algoritmo de Earley (1970) — permitiram a construção de compiladores e interpretadores para linguagens definidas por GLCs.

Na hierarquia de Chomsky, a posição das linguagens livres de contexto é estratégica:

| Tipo | Classe de Gramática | Autômato Reconhecedor | Exemplo |
|------|--------------------|-----------------------|---------|
| 0 | Irrestrita | Máquina de Turing | L = { ⟨M⟩ \| M para com entrada vazia } |
| 1 | Sensível ao Contexto | Autômato linearmente limitado | L = { aⁿbⁿcⁿ \| n ≥ 1 } |
| **2** | **Livre de Contexto** | **Autômato com Pilha** | **L = { aⁿbⁿ \| n ≥ 1 }** |
| 3 | Regular | Autômato Finito | L = { w ∈ {a,b}* \| w termina com ab } |

> *"Context-free grammars were introduced by Chomsky as a way to describe natural languages and were independently invented by Backus and Naur to describe programming languages."*
> — Sipser, *Introduction to the Theory of Computation* (2012)

---

## 6.2 Gramática Livre de Contexto (GLC)

### 6.2.1 Definição Formal

**Definição 6.1.** Uma **gramática livre de contexto** (GLC) é uma quádrupla:

> G = (V, Σ, P, S)

onde:

- **V** é um conjunto finito de **variáveis** (ou **símbolos não-terminais**);
- **Σ** é um conjunto finito de **símbolos terminais**, com V ∩ Σ = ∅;
- **P** é um conjunto finito de **produções** (ou **regras de produção**), onde cada produção tem a forma:

  > A → α, com A ∈ V e α ∈ (V ∪ Σ)*

- **S** ∈ V é o **símbolo inicial** (ou **variável de partida**).

A diferença crucial em relação às gramáticas regulares (Tipo 3) reside na **ausência de restrição sobre o lado direito** das produções: enquanto gramáticas regulares (à direita) exigem produções da forma A → aB ou A → a (ou A → ε), nas GLCs o lado direito α pode ser **qualquer sequência** de terminais e não-terminais, inclusive a cadeia vazia ε. A única restrição é que o **lado esquerdo** de cada produção deve ser um **único símbolo não-terminal** — é justamente essa propriedade que torna a gramática "livre de contexto": a substituição de A por α pode ocorrer independentemente do contexto em que A aparece (Hopcroft, Ullman & Motwani, 2006).

### 6.2.2 Linguagem Gerada

A **linguagem gerada** por uma GLC G é:

> L(G) = { w ∈ Σ* | S ⇒* w }

onde S ⇒* w indica que w pode ser derivada a partir de S por zero ou mais aplicações de produções.

### 6.2.3 Exemplos

**Exemplo 6.1.** Gramática G₁ que gera L = { aⁿbⁿ | n ≥ 1 }:

> G₁ = ({S}, {a, b}, P₁, S)
>
> P₁: S → aSb | ab

**Derivação de** `aaabbb`:

> S ⇒ aSb ⇒ aaSbb ⇒ aaabbb

Essa linguagem é o exemplo canônico de linguagem livre de contexto que **não** é regular — a necessidade de "lembrar" quantos a's foram lidos para emparelhar com o mesmo número de b's exige uma memória ilimitada que autômatos finitos não possuem, mas que a pilha de um autômato com pilha fornece.

---

**Exemplo 6.2.** Gramática G₂ que gera a linguagem de **parênteses balanceados**:

> G₂ = ({S}, { (, ) }, P₂, S)
>
> P₂: S → SS | (S) | ε

**Derivações de** `(())()`:

> S ⇒ SS ⇒ (S)S ⇒ ((S))S ⇒ (())S ⇒ (())(S) ⇒ (())()

Essa gramática captura a estrutura de aninhamento presente em expressões aritméticas, blocos de código e documentos XML. Note que a produção S → ε é necessária para gerar a cadeia vazia e para permitir que SS "termine" quando um dos S's se torna ε.

---

**Exemplo 6.3.** Gramática G₃ que gera a linguagem dos **palíndromos** sobre {a, b}:

> G₃ = ({S}, {a, b}, P₃, S)
>
> P₃: S → aSa | bSb | a | b | ε

**Derivação de** `abba`:

> S ⇒ aSa ⇒ abSba ⇒ abba (aplicando S → ε no último passo, obtemos abεba = abba)

Palíndromos são outro exemplo clássico de linguagem livre de contexto não-regular: a necessidade de comparar a primeira metade da cadeia com o reverso da segunda metade requer memória proporcional ao tamanho da entrada.

### 6.2.4 Derivação: À Esquerda e À Direita

**Definição 6.2.** Em uma **derivação à esquerda** (*leftmost derivation*), em cada passo substitui-se o **não-terminal mais à esquerda** da forma sentencial corrente. Notação: ⇒_lm.

**Definição 6.3.** Em uma **derivação à direita** (*rightmost derivation*), em cada passo substitui-se o **não-terminal mais à direita** da forma sentencial corrente. Notação: ⇒_rm.

**Exemplo 6.4.** Considere a gramática G₂ dos parênteses balanceados e a cadeia `(())()`:

**Derivação à esquerda:**

> S ⇒_lm SS ⇒_lm (S)S ⇒_lm ((S))S ⇒_lm (())S ⇒_lm (())(S) ⇒_lm (())()

**Derivação à direita:**

> S ⇒_rm SS ⇒_rm S(S) ⇒_rm S() ⇒_rm (S)() ⇒_rm ((S))() ⇒_rm (())()

### 6.2.5 Formas Sentenciais e Ambiguidade

**Definição 6.4.** Uma **forma sentencial** é qualquer cadeia α ∈ (V ∪ Σ)* tal que S ⇒* α. Se α contém apenas símbolos terminais (α ∈ Σ*), dizemos que α é uma **sentença** (ou **palavra**) da linguagem.

**Definição 6.5.** Uma gramática G é **ambígua** se existe alguma cadeia w ∈ L(G) que possui **duas ou mais árvores de derivação distintas** (equivalentemente, duas ou mais derivações à esquerda distintas). Uma linguagem livre de contexto é **inerentemente ambígua** se toda gramática que a gera é ambígua.

---

## 6.3 Formas Normais

As **formas normais** são representações padronizadas de gramáticas livres de contexto nas quais as produções obedecem a formatos restritos, sem perda de generalidade (toda GLC pode ser convertida para qualquer forma normal). Sua importância é dupla: (i) simplificam a construção de algoritmos de análise sintática (*parsing*) e (ii) facilitam demonstrações formais de propriedades das linguagens livres de contexto (Sudkamp, 2006; Sipser, 2012).

### 6.3.1 Forma Normal de Chomsky (FNC / CNF)

**Definição 6.6 (Forma Normal de Chomsky).** Uma GLC G = (V, Σ, P, S) está na **Forma Normal de Chomsky** se toda produção em P tem uma das seguintes formas:

1. **A → BC**, onde A, B, C ∈ V (e B, C ≠ S caso ε ∈ L(G))
2. **A → a**, onde a ∈ Σ
3. **S → ε**, permitida **somente** se ε ∈ L(G), e neste caso S não aparece no lado direito de nenhuma produção.

**Teorema 6.1.** Toda linguagem livre de contexto pode ser gerada por uma gramática na Forma Normal de Chomsky.

#### Algoritmo de Conversão para FNC

A conversão de uma GLC arbitrária para a FNC segue uma sequência bem definida de transformações (a ordem é importante):

**Passo 1 — Eliminar produções-ε.** Identifique todas as variáveis **anuláveis** (*nullable*): A é anulável se A ⇒* ε. Para cada produção que contenha variáveis anuláveis, adicione novas produções que representem todas as combinações possíveis de inclusão/exclusão dessas variáveis. Remova todas as produções da forma A → ε (exceto S → ε, se necessário, após criar um novo símbolo inicial).

**Passo 2 — Eliminar produções unitárias.** Remova produções da forma A → B (onde A, B ∈ V). Para cada par (A, B) tal que A ⇒* B via produções unitárias, adicione a P todas as produções não-unitárias de B com A no lado esquerdo.

**Passo 3 — Eliminar símbolos inúteis.** Remova variáveis **não-geradoras** (que não derivam nenhuma cadeia de terminais) e variáveis **inalcançáveis** (que não são alcançáveis a partir de S). Remova também todas as produções que envolvem esses símbolos.

**Passo 4 — Converter para o formato FNC.**
- Para cada produção A → X₁X₂...Xₙ com n ≥ 2: se algum Xᵢ é um terminal a, substitua-o por uma nova variável Cₐ e adicione a produção Cₐ → a.
- Para cada produção A → B₁B₂...Bₙ com n > 2 (todos não-terminais): introduza novas variáveis para binarizar: A → B₁D₁, D₁ → B₂D₂, ..., Dₙ₋₂ → Bₙ₋₁Bₙ.

### 6.3.2 Forma Normal de Greibach (FNG / GNF)

**Definição 6.7 (Forma Normal de Greibach).** Uma GLC G = (V, Σ, P, S) está na **Forma Normal de Greibach** se toda produção em P tem a forma:

> A → aα, onde a ∈ Σ e α ∈ V*

isto é, cada produção inicia com **exatamente um terminal**, seguido de zero ou mais não-terminais. A produção S → ε é permitida apenas se ε ∈ L(G) e S não aparece no lado direito de nenhuma produção.

**Teorema 6.2.** Toda linguagem livre de contexto pode ser gerada por uma gramática na Forma Normal de Greibach.

A FNG tem importância particular na construção de autômatos com pilha, pois uma gramática na FNG garante que, para cada símbolo lido da entrada, exatamente **uma transição** é executada (sem transições-ε), o que implica que toda derivação de uma cadeia de comprimento n requer exatamente n passos de derivação.

### 6.3.3 Importância das Formas Normais

| Forma Normal | Aplicação Principal |
|---|---|
| **Chomsky (FNC)** | Algoritmo CYK de análise sintática (complexidade O(n³)); provas por indução sobre o comprimento da derivação |
| **Greibach (FNG)** | Construção direta de autômatos com pilha; análise de complexidade de derivações |

---

## 6.4 Simplificação de Gramáticas

Antes de converter uma GLC para qualquer forma normal, é necessário (e desejável) **simplificar** a gramática, removendo construções redundantes ou problemáticas. A simplificação compreende três etapas, cuja **ordem de aplicação é crucial** para garantir a correção do resultado (Menezes, 2010; Hopcroft, Ullman & Motwani, 2006).

### 6.4.1 Remoção de Produções-ε (Variáveis Anuláveis)

**Definição 6.8.** Uma variável A ∈ V é **anulável** (*nullable*) se A ⇒* ε.

**Algoritmo:**

1. **Base:** Se A → ε ∈ P, então A é anulável.
2. **Indução:** Se A → X₁X₂...Xₙ ∈ P e todos os Xᵢ são anuláveis, então A é anulável.
3. Para cada produção A → α que contenha variáveis anuláveis, adicione a P todas as produções obtidas removendo cada subconjunto não-vazio de variáveis anuláveis em α (evitando duplicatas e produções-ε).
4. Remova todas as produções A → ε.
5. Se S é anulável (i.e., ε ∈ L(G)), crie um novo símbolo inicial S' com as produções S' → S | ε.

### 6.4.2 Remoção de Produções Unitárias

**Definição 6.9.** Uma **produção unitária** é uma produção da forma A → B, onde A, B ∈ V.

**Algoritmo:**

1. Para cada variável A, calcule o conjunto UNIT(A) = { B ∈ V | A ⇒* B usando apenas produções unitárias }.
2. Para cada B ∈ UNIT(A) e cada produção não-unitária B → α, adicione A → α a P.
3. Remova todas as produções unitárias.

### 6.4.3 Remoção de Símbolos Inúteis

**Definição 6.10.** Um símbolo X ∈ (V ∪ Σ) é **útil** se existe uma derivação S ⇒* αXβ ⇒* w, onde w ∈ Σ*. Caso contrário, X é **inútil**. Um símbolo útil deve satisfazer duas condições:

1. **Gerador:** X ⇒* w para algum w ∈ Σ* (X pode derivar uma cadeia de terminais).
2. **Alcançável:** S ⇒* αXβ para alguns α, β ∈ (V ∪ Σ)* (X é alcançável a partir de S).

**Algoritmo (ordem obrigatória):**

1. **Primeiro**, elimine símbolos **não-geradores** e todas as produções que os contêm.
2. **Depois**, elimine símbolos **inalcançáveis** e todas as produções que os contêm.

> **Atenção:** Inverter essa ordem pode levar a resultados incorretos. A eliminação de não-geradores pode tornar outros símbolos inalcançáveis, mas a eliminação prévia de inalcançáveis **não** garante que os restantes sejam geradores.

### 6.4.4 Ordem Recomendada de Simplificação

Para obter uma gramática simplificada equivalente, aplica-se a seguinte sequência (Hopcroft, Ullman & Motwani, 2006):

1. Eliminar produções-ε (e, se necessário, adicionar novo símbolo inicial)
2. Eliminar produções unitárias
3. Eliminar símbolos não-geradores
4. Eliminar símbolos inalcançáveis

### 6.4.5 Exemplo Detalhado de Simplificação

Considere a gramática G = ({S, A, B, C, D}, {a, b}, P, S) com as produções:

> S → AB | a
> A → aAb | ε
> B → bB | b
> C → aC
> D → AB | b

**Passo 1 — Eliminar produções-ε.**

Variáveis anuláveis: A (pois A → ε).

Novas produções (expandindo a presença de A anulável):
- S → AB | B | a (de S → AB, removendo A)
- A → aAb | ab (de A → aAb, removendo A no meio)
- (B, C, D não mudam, exceto D → AB | B | b)

Removemos A → ε. Resultado parcial:

> S → AB | B | a
> A → aAb | ab
> B → bB | b
> C → aC
> D → AB | B | b

**Passo 2 — Eliminar produções unitárias.**

Produções unitárias: S → B e D → B.

Para S → B: copiamos as produções não-unitárias de B → S: S → bB | b.
Para D → B: copiamos D → bB | b.

Removemos S → B e D → B. Resultado parcial:

> S → AB | bB | b | a
> A → aAb | ab
> B → bB | b
> C → aC
> D → AB | bB | b

**Passo 3 — Eliminar símbolos não-geradores.**

Geradores: S (S → a), A (A → ab), B (B → b), D (D → b). C **não** é gerador: C → aC requer C, que nunca alcança uma cadeia de terminais (recursão sem caso base terminal).

Removemos C e a produção C → aC.

**Passo 4 — Eliminar símbolos inalcançáveis.**

A partir de S, alcançamos: S, A, B (via S → AB) e os terminais a, b. D **não** é alcançável a partir de S.

Removemos D e suas produções. Gramática simplificada final:

> S → AB | bB | b | a
> A → aAb | ab
> B → bB | b

---

## 6.5 Autômato com Pilha (AP / PDA)

### 6.5.1 Motivação

Os autômatos finitos, estudados nos capítulos anteriores, possuem memória limitada a um número finito de estados. Essa limitação impede o reconhecimento de linguagens que exigem contagem ou emparelhamento ilimitado, como L = { aⁿbⁿ | n ≥ 1 }. O **autômato com pilha** (*pushdown automaton*, PDA) estende o modelo do autômato finito adicionando uma **pilha** (*stack*) — uma memória auxiliar potencialmente infinita com disciplina de acesso LIFO (*last in, first out*) — que fornece exatamente o poder computacional adicional necessário para reconhecer as linguagens livres de contexto (Hopcroft, Ullman & Motwani, 2006).

### 6.5.2 Definição Formal

**Definição 6.11.** Um **autômato com pilha** (AP) é uma 7-tupla:

> M = (Q, Σ, Γ, δ, q₀, Z₀, F)

onde:

- **Q** é um conjunto finito de **estados**;
- **Σ** é o **alfabeto de entrada** (conjunto finito);
- **Γ** é o **alfabeto da pilha** (conjunto finito);
- **δ** : Q × (Σ ∪ {ε}) × Γ → P(Q × Γ\*) é a **função de transição**, que mapeia um estado, um símbolo de entrada (ou ε) e um símbolo do topo da pilha para um conjunto finito de pares (novo estado, cadeia a empilhar);
- **q₀** ∈ Q é o **estado inicial**;
- **Z₀** ∈ Γ é o **símbolo inicial da pilha**;
- **F** ⊆ Q é o conjunto de **estados de aceitação** (ou **estados finais**).

Uma **configuração instantânea** (ou **descrição instantânea**) do AP é uma tripla (q, w, γ) ∈ Q × Σ* × Γ*, onde q é o estado corrente, w é a entrada restante e γ é o conteúdo da pilha (topo à esquerda).

### 6.5.3 Modos de Aceitação

Existem dois modos equivalentes de aceitação para autômatos com pilha:

**Aceitação por estado final:**

> L(M) = { w ∈ Σ* | (q₀, w, Z₀) ⊢* (q, ε, γ) para algum q ∈ F e algum γ ∈ Γ* }

O AP aceita w se, após consumir toda a entrada, encontra-se em um estado de aceitação (independentemente do conteúdo da pilha).

**Aceitação por pilha vazia:**

> N(M) = { w ∈ Σ* | (q₀, w, Z₀) ⊢* (q, ε, ε) para algum q ∈ Q }

O AP aceita w se, após consumir toda a entrada, a pilha está completamente vazia (independentemente do estado).

**Teorema 6.3 (Equivalência dos modos de aceitação).** Para todo AP M₁ que aceita por estado final, existe um AP M₂ que aceita por pilha vazia tal que N(M₂) = L(M₁), e vice-versa (Sipser, 2012; Hopcroft, Ullman & Motwani, 2006).

### 6.5.4 Não-Determinismo e Determinismo

O **não-determinismo** é uma característica essencial dos autômatos com pilha: diferentemente dos autômatos finitos, onde AFND e AFD reconhecem exatamente a mesma classe de linguagens, no caso dos autômatos com pilha a versão determinística é **estritamente menos poderosa** que a não-determinística.

**Definição 6.12.** Um AP é **determinístico** (APD / DPDA) se, para todo estado q ∈ Q e todo símbolo de pilha Z ∈ Γ:

1. |δ(q, a, Z)| ≤ 1 para todo a ∈ Σ, e
2. Se δ(q, ε, Z) ≠ ∅, então δ(q, a, Z) = ∅ para todo a ∈ Σ.

**Teorema 6.4.** A classe de linguagens reconhecidas por APDs é um **subconjunto próprio** das linguagens livres de contexto:

> DPDA ⊊ NPDA

A linguagem dos palíndromos L = { wwᴿ | w ∈ {a, b}* } é livre de contexto (reconhecida por um NPDA), mas **não** pode ser reconhecida por nenhum DPDA, pois o autômato precisa "adivinhar" não-deterministicamente onde começa a segunda metade da cadeia. Por outro lado, as linguagens determinísticas livres de contexto (reconhecidas por DPDAs) incluem todas as linguagens com gramáticas LR(k), que são fundamentais para a análise sintática de linguagens de programação (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 6.5.5 Exemplo Detalhado: AP para L = { aⁿbⁿ | n ≥ 1 }

Construímos o AP M = (Q, Σ, Γ, δ, q₀, Z₀, F) com:

- Q = {q₀, q₁, q₂}
- Σ = {a, b}
- Γ = {A, Z₀}
- q₀ = q₀ (estado inicial)
- Z₀ = Z₀ (símbolo inicial da pilha)
- F = {q₂}

**Função de transição δ:**

| Estado | Entrada | Topo da Pilha | Transição | Descrição |
|--------|---------|---------------|-----------|-----------|
| q₀ | a | Z₀ | (q₀, AZ₀) | Primeiro a: empilha A sobre Z₀ |
| q₀ | a | A | (q₀, AA) | a's seguintes: empilha A |
| q₀ | b | A | (q₁, ε) | Primeiro b: desempilha A, muda para q₁ |
| q₁ | b | A | (q₁, ε) | b's seguintes: desempilha A |
| q₁ | ε | Z₀ | (q₂, ε) | Pilha só com Z₀: aceita (vai para q₂) |

**Rastreamento da execução para a entrada** `aabb`:

| Passo | Estado | Entrada Restante | Pilha | Transição Aplicada |
|-------|--------|------------------|-------|---------------------|
| 0 | q₀ | aabb | Z₀ | — (configuração inicial) |
| 1 | q₀ | abb | AZ₀ | δ(q₀, a, Z₀) = (q₀, AZ₀) |
| 2 | q₀ | bb | AAZ₀ | δ(q₀, a, A) = (q₀, AA) |
| 3 | q₁ | b | AZ₀ | δ(q₀, b, A) = (q₁, ε) |
| 4 | q₁ | ε | Z₀ | δ(q₁, b, A) = (q₁, ε) |
| 5 | q₂ | ε | ε | δ(q₁, ε, Z₀) = (q₂, ε) |

A cadeia `aabb` é **aceita**: ao final do processamento, toda a entrada foi consumida e o autômato encontra-se no estado de aceitação q₂.

**Rastreamento para a entrada** `aab` **(rejeição):**

| Passo | Estado | Entrada Restante | Pilha | Transição Aplicada |
|-------|--------|------------------|-------|---------------------|
| 0 | q₀ | aab | Z₀ | — |
| 1 | q₀ | ab | AZ₀ | δ(q₀, a, Z₀) = (q₀, AZ₀) |
| 2 | q₀ | b | AAZ₀ | δ(q₀, a, A) = (q₀, AA) |
| 3 | q₁ | ε | AZ₀ | δ(q₀, b, A) = (q₁, ε) |

A cadeia `aab` é **rejeitada**: a entrada foi consumida, mas a pilha ainda contém AZ₀ e o autômato está no estado q₁ (não final), sem transição aplicável.

---

## 6.6 Equivalência entre GLC e AP

### 6.6.1 Teorema Fundamental

**Teorema 6.5.** Uma linguagem L é **livre de contexto** se e somente se existe um **autômato com pilha** que aceita L. Formalmente:

> L é gerada por alguma GLC G ⟺ L é aceita por algum AP M

Esse resultado estabelece a correspondência perfeita entre o modelo generativo (gramáticas) e o modelo reconhecedor (autômatos) para a classe das linguagens livres de contexto, análoga à correspondência entre gramáticas regulares e autômatos finitos para as linguagens regulares.

### 6.6.2 Construção: GLC → AP

Dada uma GLC G = (V, Σ, P, S), construímos um AP M que aceita L(G) por **pilha vazia**:

> M = ({q}, Σ, V ∪ Σ, δ, q, S, ∅)

O AP possui um único estado q e simula derivações à esquerda de G. A ideia central é:

1. Se o topo da pilha é um **não-terminal** A, o AP escolhe não-deterministicamente uma produção A → α e substitui A por α na pilha (sem consumir entrada).
2. Se o topo da pilha é um **terminal** a e o próximo símbolo da entrada é a, o AP desempilha a e avança na entrada (*match*).
3. A aceitação ocorre quando a pilha fica vazia (toda a derivação foi completada com sucesso).

Formalmente:
- Para cada A → α ∈ P: δ(q, ε, A) contém (q, α)
- Para cada a ∈ Σ: δ(q, a, a) = {(q, ε)}

### 6.6.3 Construção: AP → GLC

Dado um AP M = (Q, Σ, Γ, δ, q₀, Z₀, F), construímos uma GLC G que gera L(M). A construção utiliza variáveis da forma [qᵢ, A, qⱼ] que representam a possibilidade de o AP ir do estado qᵢ ao estado qⱼ, desempilhando o símbolo A (e tudo o que for empilhado durante o processo). As produções são construídas sistematicamente a partir das transições de M, garantindo que cada derivação na gramática corresponde a uma computação de aceitação no AP, e vice-versa (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

---

## 6.7 Propriedades das Linguagens Livres de Contexto

### 6.7.1 Propriedades de Fechamento

As linguagens livres de contexto possuem **propriedades de fechamento mais limitadas** que as linguagens regulares:

| Operação | Fechada? | Justificativa |
|---|---|---|
| **União** (L₁ ∪ L₂) | ✔ Sim | Se G₁ gera L₁ e G₂ gera L₂, construa G com novo S → S₁ \| S₂ |
| **Concatenação** (L₁ · L₂) | ✔ Sim | Novo S → S₁S₂ |
| **Estrela de Kleene** (L₁*) | ✔ Sim | Novo S → SS₁ \| ε |
| **Reverso** (Lᴿ) | ✔ Sim | Inverta o lado direito de cada produção |
| **Homomorfismo** h(L) | ✔ Sim | Substitua cada terminal a por h(a) nas produções |
| **Interseção** (L₁ ∩ L₂) | ✘ Não | Contraexemplo: L₁ = {aⁿbⁿcᵐ} e L₂ = {aᵐbⁿcⁿ} são LLCs, mas L₁ ∩ L₂ = {aⁿbⁿcⁿ} não é |
| **Complemento** (L̄) | ✘ Não | Decorre do não-fechamento sob interseção (via De Morgan) |

**Resultado importante:** A interseção de uma linguagem livre de contexto com uma linguagem **regular** é sempre livre de contexto:

> Se L₁ é livre de contexto e L₂ é regular, então L₁ ∩ L₂ é livre de contexto.

A demonstração utiliza a construção do **produto** entre um AP (para L₁) e um AFD (para L₂), onde o autômato resultante simula ambos simultaneamente: o componente de estados finitos rastreia o AFD enquanto o componente com pilha rastreia o AP (Hopcroft, Ullman & Motwani, 2006).

### 6.7.2 Propriedades de Decisão

| Problema | Decidível? | Algoritmo / Observação |
|---|---|---|
| **Pertinência** (w ∈ L?) | ✔ Sim | Algoritmo CYK (*Cocke-Younger-Kasami*), O(n³) com gramática na FNC |
| **Vacuidade** (L = ∅?) | ✔ Sim | Verificar se o símbolo inicial é gerador |
| **Finitude** (L é finito?) | ✔ Sim | Verificar existência de ciclos úteis na gramática |
| **Equivalência** (L₁ = L₂?) | ✘ Não | Indecidível (redução ao problema da correspondência de Post) |
| **Inclusão** (L₁ ⊆ L₂?) | ✘ Não | Indecidível |
| **Universalidade** (L = Σ*?) | ✘ Não | Indecidível |
| **Regularidade** (L é regular?) | ✘ Não | Indecidível |
| **Ambiguidade** (G é ambígua?) | ✘ Não | Indecidível |

O **algoritmo CYK** merece destaque por sua elegância e eficiência. Dado uma GLC G na Forma Normal de Chomsky e uma cadeia w = a₁a₂...aₙ, o algoritmo utiliza **programação dinâmica** para preencher uma tabela triangular T, onde T[i, j] contém o conjunto de variáveis A ∈ V tais que A ⇒* aᵢaᵢ₊₁...aⱼ. A cadeia w pertence a L(G) se e somente se S ∈ T[1, n]. O algoritmo executa em tempo O(n³) e espaço O(n²), sendo o algoritmo de análise sintática mais eficiente para GLCs arbitrárias (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 6.7.3 Lema do Bombeamento para Linguagens Livres de Contexto

**Teorema 6.6 (Lema do Bombeamento para LLCs).** Se L é uma linguagem livre de contexto, então existe uma constante p ≥ 1 (o **comprimento de bombeamento**) tal que toda cadeia s ∈ L com |s| ≥ p pode ser escrita como:

> s = uvxyz

satisfazendo as seguintes condições:

1. |vy| ≥ 1 (pelo menos uma das cadeias v, y é não-vazia)
2. |vxy| ≤ p
3. Para todo i ≥ 0: uvⁱxyⁱz ∈ L

Esse lema é a ferramenta principal para demonstrar que uma linguagem **não** é livre de contexto. A prova baseia-se na estrutura das árvores de derivação em gramáticas na Forma Normal de Chomsky: em uma árvore suficientemente alta, o Princípio da Casa dos Pombos garante a existência de uma variável repetida ao longo de um caminho, permitindo o "bombeamento" simultâneo das subcadeias v e y (Sipser, 2012).

---

## 6.8 Exemplo em C

Uma implementação em linguagem C dos conceitos discutidos neste capítulo está disponível no diretório `src/06-livre-contexto/`:

- **Simulação de Autômato com Pilha** (aceitação por estado final e por pilha vazia)

Consulte os arquivos-fonte e seus respectivos comentários para detalhes de implementação. Cada programa inclui exemplos de entrada que correspondem às gramáticas e autômatos apresentados nas seções anteriores, permitindo ao estudante verificar os resultados manualmente.

---

## Referências

BACKUS, J. W. The syntax and semantics of the proposed international algebraic language of the Zurich ACM-GAMM Conference. In: **Proceedings of the International Conference on Information Processing**, UNESCO, p. 125–131, 1959.

CHOMSKY, N. Three models for the description of language. **IRE Transactions on Information Theory**, v. 2, n. 3, p. 113–124, 1956.

CHOMSKY, N. On certain formal properties of grammars. **Information and Control**, v. 2, n. 2, p. 137–167, 1959.

CHOMSKY, N. Context-free grammars and pushdown storage. **MIT Research Laboratory of Electronics Quarterly Progress Report**, n. 65, 1962.

COCKE, J.; SCHWARTZ, J. T. **Programming Languages and Their Compilers: Preliminary Notes**. Courant Institute of Mathematical Sciences, New York University, 1970.

EARLEY, J. An efficient context-free parsing algorithm. **Communications of the ACM**, v. 13, n. 2, p. 94–102, 1970.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Elsevier, 2006.

KASAMI, T. An efficient recognition and syntax-analysis algorithm for context-free languages. **Scientific Report AFCRL-65-758**, Air Force Cambridge Research Lab, Bedford, MA, 1965.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre: Bookman, 2010.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage Learning, 2012.

SUDKAMP, T. A. **Languages and Machines: An Introduction to the Theory of Computer Science**. 3. ed. Boston: Addison-Wesley, 2006.

YOUNGER, D. H. Recognition and parsing of context-free languages in time n³. **Information and Control**, v. 10, n. 2, p. 189–208, 1967.
