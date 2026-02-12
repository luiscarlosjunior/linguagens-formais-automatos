# Capítulo 8 — Gramáticas Sensíveis ao Contexto

## 8.1 Introdução e Contexto Histórico

O estudo das **gramáticas sensíveis ao contexto** (GSCs) ocupa uma posição central na hierarquia de Chomsky, correspondendo ao **Tipo 1** — situado entre as gramáticas livres de contexto (Tipo 2) e as gramáticas irrestritas (Tipo 0). Enquanto as gramáticas livres de contexto permitem a substituição de um não-terminal independentemente de seu entorno, as gramáticas sensíveis ao contexto impõem que essa substituição dependa dos símbolos que **circundam** o não-terminal — o seu *contexto*. Essa capacidade adicional confere às GSCs poder expressivo suficiente para descrever fenômenos linguísticos e computacionais que escapam ao alcance das gramáticas livres de contexto.

A formulação das gramáticas sensíveis ao contexto remonta ao trabalho seminal de **Noam Chomsky** (1959), que, ao refinar a hierarquia de gramáticas formais introduzida em 1956, estabeleceu quatro níveis de complexidade gramatical. Chomsky observou que certas construções das línguas naturais — como a concordância de longa distância, a reduplicação e dependências cruzadas (*cross-serial dependencies*) — não podiam ser capturadas por gramáticas livres de contexto, mas admitiam descrição natural por meio de regras sensíveis ao contexto. A motivação linguística original foi, portanto, a busca por um formalismo que modelasse com maior fidelidade a sintaxe das línguas humanas.

Em 1964, **Sige-Yuki Kuroda** deu uma contribuição fundamental ao demonstrar a equivalência entre as gramáticas sensíveis ao contexto e os **autômatos linearmente limitados** (*linear bounded automata*, LBA) — máquinas de Turing cuja fita de trabalho é limitada ao comprimento da entrada. Kuroda também introduziu uma forma normal para as GSCs (hoje conhecida como **Forma Normal de Kuroda**), análoga à Forma Normal de Chomsky para as GLCs, que simplifica a estrutura das produções sem perda de generalidade (Kuroda, 1964).

Do ponto de vista da complexidade computacional, as linguagens sensíveis ao contexto correspondem exatamente à classe **NSPACE(n)** — os problemas decidíveis por máquinas de Turing não-determinísticas com espaço linear. Essa correspondência confere às GSCs uma importância que transcende a teoria das linguagens formais, conectando-as à teoria da complexidade e à análise de algoritmos (Sipser, 2012).

Na hierarquia de Chomsky, a posição das linguagens sensíveis ao contexto é a seguinte:

| Tipo | Classe de Gramática | Autômato Reconhecedor | Exemplo |
|------|--------------------|-----------------------|---------|
| 0 | Irrestrita | Máquina de Turing | L = { ⟨M⟩ \| M para com entrada vazia } |
| **1** | **Sensível ao Contexto** | **Autômato Linearmente Limitado** | **L = { aⁿbⁿcⁿ \| n ≥ 1 }** |
| 2 | Livre de Contexto | Autômato com Pilha | L = { aⁿbⁿ \| n ≥ 1 } |
| 3 | Regular | Autômato Finito | L = { w ∈ {a,b}* \| w termina com ab } |

> *"The context-sensitive grammars generate exactly the languages accepted by linear bounded automata — nondeterministic Turing machines whose tape head never moves beyond the cells initially containing the input."*
> — Hopcroft, Ullman & Motwani, *Introduction to Automata Theory, Languages, and Computation* (2006)

---

## 8.2 Gramática Sensível ao Contexto (GSC)

### 8.2.1 Definição Formal

**Definição 8.1.** Uma **gramática sensível ao contexto** (GSC) é uma quádrupla:

> G = (V, Σ, P, S)

onde:

- **V** é um conjunto finito de **variáveis** (ou **símbolos não-terminais**);
- **Σ** é um conjunto finito de **símbolos terminais**, com V ∩ Σ = ∅;
- **P** é um conjunto finito de **produções** (ou **regras de produção**), onde cada produção tem a forma:

  > αAβ → αγβ, com A ∈ V, α, β ∈ (V ∪ Σ)* e γ ∈ (V ∪ Σ)⁺

- **S** ∈ V é o **símbolo inicial** (ou **variável de partida**).

A condição γ ∈ (V ∪ Σ)⁺ — isto é, |γ| ≥ 1 — garante que o não-terminal A é substituído por **pelo menos um símbolo**, nunca pela cadeia vazia. Os elementos α e β representam o **contexto** à esquerda e à direita de A, respectivamente: a substituição de A por γ só pode ocorrer quando A aparece precedido por α e seguido por β. É justamente essa dependência do contexto que distingue as GSCs das gramáticas livres de contexto, nas quais α = β = ε (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

Observe que, quando α = β = ε, a produção torna-se A → γ com |γ| ≥ 1, que é exatamente a forma de uma produção livre de contexto (sem a produção-ε). Portanto, toda gramática livre de contexto (exceto pelas produções-ε) é também uma gramática sensível ao contexto, confirmando que a classe das linguagens livres de contexto está **contida** na classe das linguagens sensíveis ao contexto.

### 8.2.2 Propriedade Não-Contrativa

Uma formulação equivalente e frequentemente utilizada na literatura define as GSCs por meio da **propriedade não-contrativa** (*non-contracting* ou *nonshortening*):

**Definição 8.2.** Uma gramática G = (V, Σ, P, S) é **não-contrativa** se toda produção α → β ∈ P satisfaz:

> |α| ≤ |β|

onde |·| denota o comprimento da cadeia. A única exceção permitida é a produção S → ε, que pode existir **somente** se S não aparece no lado direito de nenhuma produção (Menezes, 2010).

**Teorema 8.1.** A classe de linguagens geradas por gramáticas sensíveis ao contexto (na forma αAβ → αγβ) coincide com a classe de linguagens geradas por gramáticas não-contrativas, a menos da cadeia vazia ε.

A demonstração mostra que toda produção αAβ → αγβ é claramente não-contrativa (pois |αAβ| = |α| + 1 + |β| ≤ |α| + |γ| + |β| = |αγβ|), e que, inversamente, toda produção não-contrativa pode ser simulada por uma sequência de produções na forma sensível ao contexto, possivelmente com a introdução de variáveis auxiliares (Hopcroft, Ullman & Motwani, 2006; Sudkamp, 2006).

### 8.2.3 Comparação com Outras Classes de Gramáticas

| Propriedade | Regular (Tipo 3) | Livre de Contexto (Tipo 2) | Sensível ao Contexto (Tipo 1) | Irrestrita (Tipo 0) |
|---|---|---|---|---|
| Forma das produções | A → aB ou A → a | A → α (A ∈ V) | αAβ → αγβ (\|γ\| ≥ 1) | α → β (sem restrição) |
| Contexto | Nenhum | Nenhum | Exigido (α, β) | Irrelevante |
| Produções contrativas | Não (exceto S → ε) | Não (exceto S → ε na FNC) | Não (exceto S → ε) | Sim |
| Autômato equivalente | AF (finito) | AP (pilha) | ALL (fita limitada) | MT (fita ilimitada) |

### 8.2.4 Exemplos de Gramáticas Sensíveis ao Contexto

**Exemplo 8.1.** Gramática G₁ que gera L₁ = { aⁿbⁿcⁿ | n ≥ 1 }:

> G₁ = ({S, B, C, H}, {a, b, c}, P₁, S)
>
> P₁:
> 1. S → aSBC
> 2. S → aBC
> 3. CB → HB
> 4. HB → HC
> 5. HC → BC
> 6. aB → ab
> 7. bB → bb
> 8. bC → bc
> 9. cC → cc

**Derivação de** `aabbcc` **(n = 2):**

> S ⇒ aSBC (regra 1)
> ⇒ aaBCBC (regra 2)
> ⇒ aaBHBBC (regra 3, CB → HB na posição central)

Aplicamos agora as regras 4 e 5 para completar a troca do primeiro par CB:

> ⇒ aaBHCBC (regra 4, HB → HC, trocando o H com o B à direita)
> ⇒ aaBBCBC → … (continuando a permutação do segundo par CB)

Após todas as permutações dos pares CB para BC:

> ⇒ aaBBCC

Agora convertemos os não-terminais em terminais, da esquerda para a direita:

> ⇒ aabBCC (regra 6, convertendo aB em ab)
> ⇒ aabbCC (regra 7, convertendo bB em bb)
> ⇒ aabbcC (regra 8, convertendo bC em bc)
> ⇒ aabbcc (regra 9, convertendo cC em cc)

A ideia central é que as produções 3–5 realizam a **permutação** CB → BC, reordenando os símbolos B e C para que todos os B's precedam todos os C's. Essa permutação é um procedimento em três passos — CB → HB → HC → BC — que utiliza o símbolo auxiliar H como "marcador de troca". As produções 6–9 então convertem os não-terminais B e C em terminais b e c, respectivamente, mas **somente da esquerda para a direita** e no contexto correto. Esse mecanismo de permutação contextual é típico das GSCs e ilustra como o contexto é utilizado para impor restrições globais sobre a forma da cadeia.

**Verificação para n = 1** (cadeia `abc`):

> S ⇒ aBC (regra 2)
> ⇒ abC (regra 6, convertendo aB em ab)
> ⇒ abc (regra 8, convertendo bC em bc)

---

**Exemplo 8.2.** Gramática G₂ que gera L₂ = { ww | w ∈ {a, b}⁺ } (linguagem das cadeias repetidas):

Esta linguagem é sensível ao contexto, mas **não** é livre de contexto (pode-se demonstrar via Lema do Bombeamento para LLCs). A construção de uma GSC para L₂ é consideravelmente mais complexa e envolve a criação de marcadores e mecanismos de cópia que simulam, por meio de produções contextuais, a duplicação de uma cadeia arbitrária. A existência de tal gramática é garantida pela equivalência entre GSCs e autômatos linearmente limitados, dado que um ALL pode facilmente verificar se uma cadeia tem a forma ww (Sipser, 2012).

---

## 8.3 Linguagens Sensíveis ao Contexto

### 8.3.1 Definição Formal

**Definição 8.3.** Uma linguagem L é **sensível ao contexto** (ou **do Tipo 1**) se existe uma gramática sensível ao contexto G tal que:

> L(G) = L ou L(G) = L \ {ε}

A exclusão de ε é necessária porque, como visto na Definição 8.2, as GSCs na forma canônica não geram a cadeia vazia (exceto pela produção especial S → ε). Convenciona-se que a cadeia vazia pode ser adicionada ou removida sem alterar a classe da linguagem.

### 8.3.2 Exemplos Clássicos

As seguintes linguagens são sensíveis ao contexto, mas **não** são livres de contexto:

1. **L = { aⁿbⁿcⁿ | n ≥ 1 }** — o exemplo canônico, como demonstrado pelo Exemplo 8.1. A necessidade de emparelhar **três** grupos de símbolos excede o poder de uma pilha única.

2. **L = { aⁿbⁿcⁿdⁿ | n ≥ 1 }** — generalização para quatro grupos. O princípio de construção da GSC é análogo, com permutações adicionais.

3. **L = { ww | w ∈ {a, b}⁺ }** — linguagem das cadeias repetidas. A verificação de que a segunda metade é uma cópia exata da primeira requer mais que uma pilha.

4. **L = { a^(n²) | n ≥ 1 }** — linguagem das cadeias cujo comprimento é um quadrado perfeito. Um ALL pode verificar essa propriedade com espaço linear.

5. **L = { a^(2ⁿ) | n ≥ 0 }** — linguagem das cadeias cujo comprimento é uma potência de 2. Também reconhecível por ALL.

### 8.3.3 Propriedades de Fechamento

As linguagens sensíveis ao contexto possuem **propriedades de fechamento notavelmente robustas** — significativamente mais fortes que as das linguagens livres de contexto:

| Operação | Fechada? | Justificativa |
|---|---|---|
| **União** (L₁ ∪ L₂) | ✔ Sim | Se G₁ gera L₁ e G₂ gera L₂, construa G com novo S → S₁ \| S₂ (com adaptação não-contrativa) |
| **Interseção** (L₁ ∩ L₂) | ✔ Sim | Simulação simultânea de dois ALLs; resultado fundamental de Kuroda (1964) |
| **Concatenação** (L₁ · L₂) | ✔ Sim | Novo S → S₁S₂ (com variáveis renomeadas) |
| **Estrela de Kleene** (L₁*) | ✔ Sim | Construção iterativa com adaptação não-contrativa |
| **Complemento** (L̄) | ✔ Sim | Resultado profundo: Immerman–Szelepcsényi (1988); NSPACE(n) = co-NSPACE(n) |
| **Reverso** (Lᴿ) | ✔ Sim | Inversão das produções preserva a propriedade não-contrativa |
| **Homomorfismo** h(L) | ✘ Não | Homomorfismos podem gerar produções contrativas |
| **Homomorfismo inverso** h⁻¹(L) | ✔ Sim | Composição com ALL preserva limitação de espaço |

O fechamento sob **complemento** é particularmente notável. Durante décadas, a questão de saber se as linguagens sensíveis ao contexto são fechadas sob complementação permaneceu em aberto — era um dos grandes problemas da teoria da complexidade. A resposta afirmativa, provada independentemente por **Immerman** (1988) e **Szelepcsényi** (1988), é consequência do resultado mais geral de que **NSPACE(s(n)) = co-NSPACE(s(n))** para s(n) ≥ log n. Este resultado rendeu a ambos o **Prêmio Gödel** de 1995 (Sipser, 2012).

### 8.3.4 Contraste com Linguagens Livres de Contexto

| Propriedade de Fechamento | Livres de Contexto | Sensíveis ao Contexto |
|---|---|---|
| União | ✔ | ✔ |
| Interseção | ✘ | ✔ |
| Complemento | ✘ | ✔ |
| Concatenação | ✔ | ✔ |
| Estrela de Kleene | ✔ | ✔ |
| Homomorfismo | ✔ | ✘ |

O fato de as linguagens sensíveis ao contexto serem fechadas sob interseção e complemento — operações que **não** preservam as linguagens livres de contexto — reflete o poder adicional conferido pela dependência do contexto nas produções gramaticais.

---

## 8.4 Autômato Linearmente Limitado (ALL)

### 8.4.1 Definição Formal

**Definição 8.4.** Um **autômato linearmente limitado** (ALL, *Linear Bounded Automaton*, LBA) é uma máquina de Turing não-determinística:

> M = (Q, Σ, Γ, δ, q₀, q_acc, q_rej)

com a seguinte restrição adicional:

> A cabeça de leitura/escrita **nunca se move além** das células que contêm a entrada original.

Formalmente, se a entrada é w = a₁a₂…aₙ, a fita contém marcadores especiais ⊢ (início) e ⊣ (fim), e a cabeça está restrita ao intervalo [1, n]. A função de transição é:

> δ : Q × Γ → P(Q × Γ × {L, R})

onde Γ é o alfabeto de fita (que pode ser maior que Σ, permitindo que a máquina **sobrescreva** células com símbolos auxiliares), e os movimentos estão restritos à região da entrada.

A restrição de espaço é o que diferencia o ALL de uma máquina de Turing geral: enquanto a MT pode utilizar fita ilimitada, o ALL está confinado a **espaço O(n)**, onde n é o comprimento da entrada. Essa limitação corresponde, em termos de complexidade, à classe **NSPACE(n)** (Hopcroft, Ullman & Motwani, 2006).

### 8.4.2 Equivalência com GSC

**Teorema 8.2 (Kuroda, 1964).** Uma linguagem L (não contendo ε) é gerada por uma gramática sensível ao contexto se e somente se L é aceita por um autômato linearmente limitado. Formalmente:

> L é sensível ao contexto ⟺ L é aceita por algum ALL

**Esboço da demonstração (GSC → ALL):**

Dada uma GSC G = (V, Σ, P, S), construímos um ALL M que aceita L(G):

1. M recebe a entrada w de comprimento n na fita.
2. M escreve o símbolo inicial S no início da fita de trabalho (ou em uma trilha auxiliar).
3. M não-deterministicamente escolhe uma produção αAβ → αγβ ∈ P e verifica se a forma sentencial corrente contém a subcadeia αAβ.
4. Se sim, M substitui αAβ por αγβ na forma sentencial. Como |αγβ| ≥ |αAβ|, a forma sentencial não encolhe — mas a propriedade não-contrativa garante que todas as formas sentenciais intermediárias têm comprimento **≤ n** (pois partimos de S com comprimento 1 e a derivação termina em w com comprimento n).
5. M aceita se a forma sentencial se torna exatamente w; rejeita se nenhuma produção é aplicável e a forma sentencial não é w.

A propriedade não-contrativa garante que todas as formas sentenciais intermediárias têm comprimento **≤ n**, permitindo que a simulação caiba na fita limitada.

**Esboço da demonstração (ALL → GSC):**

Dado um ALL M = (Q, Σ, Γ, δ, q₀, q_acc, q_rej), construímos uma GSC G que gera L(M). A construção procede em três fases:

1. **Geração:** G gera não-deterministicamente uma cadeia w de terminais, juntamente com uma representação codificada da configuração inicial de M sobre w.
2. **Simulação:** Produções sensíveis ao contexto simulam cada passo de computação de M, modificando a representação da configuração na forma sentencial. Cada transição δ(q, a) = (q', b, D) é codificada como uma produção que altera o símbolo sob a cabeça e move o "marcador de estado" para a célula vizinha.
3. **Limpeza:** Quando a representação atinge a configuração de aceitação (estado q_acc), produções adicionais removem os símbolos auxiliares, deixando apenas a cadeia original w.

Cada produção modifica apenas o símbolo sob a cabeça e seus vizinhos (o contexto), refletindo a localidade das transições da máquina de Turing (Hopcroft, Ullman & Motwani, 2006; Sudkamp, 2006).

### 8.4.3 Diferenças entre ALL e Máquina de Turing

| Característica | Autômato Linearmente Limitado (ALL) | Máquina de Turing (MT) |
|---|---|---|
| Espaço de fita | Limitado a O(n), onde n = \|entrada\| | Ilimitado |
| Determinismo | Tipicamente não-determinístico | Pode ser det. ou não-det. |
| Poder de reconhecimento | Linguagens sensíveis ao contexto (Tipo 1) | Linguagens recursivamente enumeráveis (Tipo 0) |
| Classe de complexidade | NSPACE(n) | RE (recursivamente enumeráveis) |
| Problema da parada | **Decidível** (espaço finito ⇒ número finito de configurações) | **Indecidível** |

A limitação de espaço tem uma consequência importante: como o ALL possui um número **finito** de configurações possíveis (limitado por |Q| × n × |Γ|ⁿ, onde |Q| é o número de estados, n o comprimento da entrada e |Γ| o tamanho do alfabeto de fita), o problema da pertinência é **sempre decidível** — basta simular todas as computações possíveis e verificar se alguma aceita, com detecção de ciclos para garantir terminação.

### 8.4.4 Exemplo: ALL para L = { aⁿbⁿcⁿ | n ≥ 1 }

Construímos informalmente um ALL M para reconhecer L = { aⁿbⁿcⁿ | n ≥ 1 }:

**Algoritmo de M:**

1. Verificar que a entrada tem a forma a⁺b⁺c⁺ (rejeitar caso contrário).
2. Repetir:
   - Marcar (sobrescrever com X) o primeiro `a` não marcado.
   - Percorrer à direita até encontrar o primeiro `b` não marcado; marcá-lo (com Y).
   - Percorrer à direita até encontrar o primeiro `c` não marcado; marcá-lo (com Z).
   - Retornar ao início da fita.
3. Se todos os a's, b's e c's estão marcados: **aceitar**.
4. Se algum grupo se esgota antes dos outros: **rejeitar**.

**Rastreamento para a entrada** `aabbcc`:

| Iteração | Ação | Fita após iteração |
|---|---|---|
| 1 | Marca primeiro a→X, primeiro b→Y, primeiro c→Z | XaYbZc |
| 2 | Marca segundo a→X, segundo b→Y, segundo c→Z | XXYYZZ |
| Final | Todos os símbolos estão marcados | **Aceitar** |

**Rastreamento para a entrada** `aabcc` **(rejeição):**

| Iteração | Ação | Fita após iteração |
|---|---|---|
| 1 | Marca primeiro a→X, primeiro b→Y, primeiro c→Z | XaYbZc → XaYZc (apenas um b disponível) |
| 2 | Marca segundo a→X, busca b não marcado | XXY… — nenhum b não marcado encontrado → **Rejeitar** |

O ALL utiliza apenas a região da fita correspondente à entrada (substituindo a, b, c por X, Y, Z), sem necessidade de espaço adicional. O não-determinismo não é necessário neste exemplo particular — o ALL opera de forma determinística.

---

## 8.5 Forma Normal de Kuroda

### 8.5.1 Definição

**Definição 8.5 (Forma Normal de Kuroda).** Uma gramática sensível ao contexto G = (V, Σ, P, S) está na **Forma Normal de Kuroda** se toda produção em P tem uma das seguintes formas:

1. **A → BC** (um não-terminal produz dois não-terminais)
2. **A → a** (um não-terminal produz um terminal)
3. **AB → CD** (dois não-terminais produzem dois não-terminais)

onde A, B, C, D ∈ V e a ∈ Σ. A produção S → ε é permitida somente se ε ∈ L(G) e S não aparece no lado direito de nenhuma produção.

A Forma Normal de Kuroda é a análoga, para gramáticas sensíveis ao contexto, da Forma Normal de Chomsky para gramáticas livres de contexto. Note que as formas (1) e (2) são exatamente as formas da FNC; a forma (3) é a novidade que captura a sensibilidade ao contexto — ela permite que a substituição de um não-terminal dependa de seu vizinho.

### 8.5.2 Teorema de Equivalência

**Teorema 8.3 (Kuroda, 1964).** Toda linguagem sensível ao contexto (possivelmente excluindo ε) pode ser gerada por uma gramática na Forma Normal de Kuroda.

A demonstração é construtiva e procede em etapas análogas à conversão de uma GLC para a Forma Normal de Chomsky:

**Esboço do algoritmo de conversão:**

**Passo 1 — Terminais em produções mistas.** Para cada terminal a que aparece em uma produção com comprimento do lado direito ≥ 2, introduza uma nova variável Cₐ e adicione a produção Cₐ → a. Substitua toda ocorrência de a (em produções mistas) por Cₐ.

**Passo 2 — Binarização de produções longas.** Para cada produção α → β com |β| > 2 e todos os símbolos sendo não-terminais, introduza variáveis auxiliares para decompor a produção em uma sequência de produções binárias, cada uma com no máximo dois símbolos de cada lado.

**Passo 3 — Tratamento de produções não-contrativas gerais.** As produções restantes com |α| ≤ |β| são decompostas em sequências de produções nas formas (1), (2) ou (3), utilizando variáveis intermediárias que propagam informação do contexto.

O resultado é uma gramática equivalente na Forma Normal de Kuroda (Kuroda, 1964; Sudkamp, 2006).

### 8.5.3 Importância da Forma Normal

A Forma Normal de Kuroda simplifica diversas construções e demonstrações teóricas:

- **Provas por indução** sobre o comprimento das derivações tornam-se mais tratáveis, pois cada passo de derivação tem efeito local e bem delimitado.
- **Construção de ALLs** a partir de gramáticas é facilitada, pois as produções da Forma Normal correspondem diretamente a operações locais na fita.
- **Análise de complexidade:** a forma normal permite estimar mais precisamente o número de passos de derivação necessários para gerar uma cadeia de comprimento n.

A relação entre as formas normais das diferentes classes de gramáticas pode ser resumida:

| Classe de Gramática | Forma Normal | Tipos de Produção |
|---|---|---|
| Livre de Contexto (Tipo 2) | Chomsky (FNC) | A → BC, A → a |
| Sensível ao Contexto (Tipo 1) | Kuroda | A → BC, A → a, AB → CD |

A forma (3) — AB → CD — é a que captura a essência da sensibilidade ao contexto: o não-terminal A é substituído por C, mas **somente** quando B está à sua direita; simultaneamente, B pode ser substituído por D. Essa interação entre símbolos adjacentes é o mecanismo mínimo necessário para gerar linguagens como { aⁿbⁿcⁿ | n ≥ 1 } (Kuroda, 1964).

---

## 8.6 Propriedades de Decisão

### 8.6.1 Problema da Pertinência (Membership)

**Teorema 8.4.** O problema da pertinência para linguagens sensíveis ao contexto é **decidível**: dada uma GSC G e uma cadeia w, existe um algoritmo que determina se w ∈ L(G).

**Demonstração (esboço).** Como toda produção α → β satisfaz |α| ≤ |β|, o conjunto de formas sentenciais deriváveis de S com comprimento ≤ |w| é **finito**. Basta enumerar sistematicamente todas as derivações a partir de S, mantendo apenas formas sentenciais de comprimento ≤ |w|, e verificar se w é alcançada. Como o conjunto de formas sentenciais possíveis é finito, esse processo sempre termina.

Alternativamente, pode-se utilizar o ALL equivalente: como o espaço de configurações é finito (limitado pelo comprimento da entrada), a simulação do ALL sempre termina.

> **Atenção:** Embora o problema da pertinência seja decidível, sua complexidade é **alta**. O melhor limite superior conhecido é **PSPACE-completo** (para GSCs gerais), o que significa que, no pior caso, a quantidade de espaço necessária é polinomial no comprimento da entrada, mas o tempo pode ser exponencial. Para gramáticas fixas, o problema pertence a **NSPACE(n)**, que é contido em **DTIME(c^n)** para alguma constante c (Sipser, 2012).

### 8.6.2 Problema da Vacuidade (Emptiness)

**Teorema 8.5.** O problema da vacuidade — determinar se L(G) = ∅ para uma GSC G — é **indecidível**.

Esse resultado contrasta fortemente com o caso das gramáticas livres de contexto, para as quais a vacuidade é decidível (basta verificar se o símbolo inicial é gerador). Para as GSCs, a indecidibilidade decorre da capacidade das gramáticas sensíveis ao contexto de simular computações de máquinas de Turing limitadas, tornando a verificação de propriedades globais tão difícil quanto problemas sobre máquinas de Turing (Hopcroft, Ullman & Motwani, 2006).

### 8.6.3 Outros Problemas de Decisão

**Teorema 8.6.** Os seguintes problemas são **indecidíveis** para gramáticas sensíveis ao contexto:

1. **Finitude:** Determinar se L(G) é finito.
2. **Equivalência:** Determinar se L(G₁) = L(G₂).
3. **Inclusão:** Determinar se L(G₁) ⊆ L(G₂).
4. **Universalidade:** Determinar se L(G) = Σ*.
5. **Regularidade:** Determinar se L(G) é regular.
6. **Ambiguidade:** Determinar se G é ambígua (no sentido de que alguma cadeia possui duas derivações distintas).

Esses resultados seguem, em geral, por redução do problema da parada ou do problema da correspondência de Post. A indecidibilidade da universalidade, em particular, é uma consequência direta do Teorema de Rice aplicado às propriedades não-triviais de linguagens sensíveis ao contexto (Sipser, 2012; Sudkamp, 2006).

### 8.6.4 Tabela Comparativa de Decidibilidade

| Problema | Regular (Tipo 3) | Livre de Contexto (Tipo 2) | Sensível ao Contexto (Tipo 1) | Rec. Enumerável (Tipo 0) |
|---|---|---|---|---|
| **Pertinência** (w ∈ L?) | ✔ Decidível (O(n)) | ✔ Decidível (O(n³) — CYK) | ✔ Decidível (PSPACE) | ✘ Indecidível (em geral) |
| **Vacuidade** (L = ∅?) | ✔ Decidível | ✔ Decidível | ✘ Indecidível | ✘ Indecidível |
| **Finitude** (L é finito?) | ✔ Decidível | ✔ Decidível | ✘ Indecidível | ✘ Indecidível |
| **Equivalência** (L₁ = L₂?) | ✔ Decidível | ✘ Indecidível | ✘ Indecidível | ✘ Indecidível |
| **Inclusão** (L₁ ⊆ L₂?) | ✔ Decidível | ✘ Indecidível | ✘ Indecidível | ✘ Indecidível |
| **Universalidade** (L = Σ*?) | ✔ Decidível | ✘ Indecidível | ✘ Indecidível | ✘ Indecidível |

A tabela revela um padrão claro: à medida que se sobe na hierarquia de Chomsky, mais problemas de decisão tornam-se indecidíveis. As linguagens regulares possuem o maior número de propriedades decidíveis, enquanto as linguagens recursivamente enumeráveis têm quase todas as propriedades não-triviais indecidíveis (como consequência do Teorema de Rice).

---

## 8.7 Relação com a Hierarquia de Chomsky

### 8.7.1 Cadeia de Inclusão

A hierarquia de Chomsky estabelece uma cadeia estrita de inclusão entre as quatro classes de linguagens:

**Teorema 8.7 (Hierarquia de Chomsky).** Sejam ℒ₃, ℒ₂, ℒ₁ e ℒ₀ as classes de linguagens regulares, livres de contexto, sensíveis ao contexto e recursivamente enumeráveis, respectivamente. Então:

> **ℒ₃ ⊂ ℒ₂ ⊂ ℒ₁ ⊂ ℒ₀**

onde cada inclusão é **própria**.

Cada inclusão é **própria** — existem linguagens em cada classe que não pertencem à classe imediatamente inferior:

1. **Regular ⊊ Livre de Contexto:** A linguagem L = { aⁿbⁿ | n ≥ 1 } é livre de contexto (gerada pela gramática S → aSb | ab) mas não é regular (demonstrável pelo Lema do Bombeamento para linguagens regulares).

2. **Livre de Contexto ⊊ Sensível ao Contexto:** A linguagem L = { aⁿbⁿcⁿ | n ≥ 1 } é sensível ao contexto (conforme Exemplo 8.1) mas não é livre de contexto (demonstrável pelo Lema do Bombeamento para LLCs).

3. **Sensível ao Contexto ⊊ Recursivamente Enumerável:** Toda linguagem sensível ao contexto é decidível (pois o ALL sempre para), mas existem linguagens recursivamente enumeráveis que não são decidíveis — por exemplo, a linguagem de aceitação da máquina de Turing universal, L_u = { ⟨M, w⟩ | M aceita w }. Portanto, L_u é recursivamente enumerável mas não sensível ao contexto.

Note que existe uma classe intermediária entre as linguagens sensíveis ao contexto e as recursivamente enumeráveis: as **linguagens recursivas** (ou **decidíveis**). Toda linguagem sensível ao contexto é recursiva, mas nem toda linguagem recursiva é sensível ao contexto. A hierarquia completa é:

> **Regular ⊂ Livre de Contexto ⊂ Sensível ao Contexto ⊂ Recursiva ⊂ Recursivamente Enumerável**

### 8.7.2 Tabela Comparativa Completa

| Aspecto | Tipo 3 — Regular | Tipo 2 — Livre de Contexto | Tipo 1 — Sensível ao Contexto | Tipo 0 — Irrestrita |
|---|---|---|---|---|
| **Gramática** | A → aB, A → a | A → α | αAβ → αγβ (\|γ\| ≥ 1) | α → β (sem restrição) |
| **Autômato** | AF (finito) | AP (pilha) | ALL (fita limitada) | MT (fita ilimitada) |
| **Exemplo separador** | (a\|b)* | aⁿbⁿ | aⁿbⁿcⁿ | { ⟨M⟩ \| M para } |
| **Pertinência** | O(n) | O(n³) | PSPACE-completo | Indecidível |
| **Vacuidade** | Decidível | Decidível | Indecidível | Indecidível |
| **Fechamento ∩** | ✔ | ✘ | ✔ | ✔ |
| **Fechamento complemento** | ✔ | ✘ | ✔ | ✘ |
| **Classe de complexidade** | DSPACE(O(1)) | — | NSPACE(n) | — |

### 8.7.3 Resultados de Separação

Os resultados de separação entre os níveis da hierarquia de Chomsky são fundamentais para justificar a existência de cada nível como classe distinta:

**Teorema 8.8.** Para cada par de classes adjacentes na hierarquia de Chomsky, existe uma linguagem que pertence à classe superior mas não à inferior.

As demonstrações utilizam diferentes técnicas:

- **Regular vs. Livre de Contexto:** O Lema do Bombeamento para linguagens regulares (Capítulo 5) prova que { aⁿbⁿ | n ≥ 1 } não é regular.
- **Livre de Contexto vs. Sensível ao Contexto:** O Lema do Bombeamento para linguagens livres de contexto (Capítulo 6) prova que { aⁿbⁿcⁿ | n ≥ 1 } não é livre de contexto.
- **Sensível ao Contexto vs. Recursivamente Enumerável:** Argumentos de diagonalização ou a existência de linguagens recursivamente enumeráveis não-decidíveis (como o problema da parada) provam a separação, pois toda linguagem sensível ao contexto é decidível.

Esses resultados demonstram que cada nível de restrição gramatical corresponde a uma **perda genuína de poder expressivo**, e que a hierarquia de Chomsky não é "degenerada" — cada nível captura uma classe de linguagens estritamente distinta (Chomsky, 1959; Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 8.7.4 Questões em Aberto

Apesar de décadas de pesquisa, algumas questões fundamentais sobre as linguagens sensíveis ao contexto permanecem em aberto:

1. **LBA = DLBA?** — É desconhecido se os autômatos linearmente limitados **determinísticos** reconhecem exatamente a mesma classe de linguagens que os não-determinísticos. Em termos de complexidade, essa questão equivale a perguntar se **NSPACE(n) = DSPACE(n)**, uma instância do problema geral NSPACE vs. DSPACE que permanece sem solução.

2. **Hierarquia própria dentro das LSCs** — Embora se saiba que existe uma hierarquia infinita de classes de complexidade de espaço (pelo Teorema da Hierarquia de Espaço), a estrutura fina das sublinguagens sensíveis ao contexto ainda não é completamente compreendida.

Essas questões conectam a teoria das linguagens formais aos problemas mais profundos da teoria da complexidade computacional, demonstrando que o estudo das GSCs continua sendo uma área de pesquisa ativa e relevante (Sipser, 2012).

---

## 8.8 Exemplo em C

Uma implementação em linguagem C dos conceitos discutidos neste capítulo está disponível no diretório `src/08-sensiveis-contexto/`:

- **Verificação da linguagem** L = { aⁿbⁿcⁿ | n ≥ 1 } — simulação de um autômato linearmente limitado que reconhece a linguagem canônica sensível ao contexto

Consulte os arquivos-fonte e seus respectivos comentários para detalhes de implementação. Cada programa inclui exemplos de entrada que correspondem às gramáticas e autômatos apresentados nas seções anteriores, permitindo ao estudante verificar os resultados manualmente.

---

## Referências

CHOMSKY, N. Three models for the description of language. **IRE Transactions on Information Theory**, v. 2, n. 3, p. 113–124, 1956.

CHOMSKY, N. On certain formal properties of grammars. **Information and Control**, v. 2, n. 2, p. 137–167, 1959.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Elsevier, 2006.

IMMERMAN, N. Nondeterministic space is closed under complementation. **SIAM Journal on Computing**, v. 17, n. 5, p. 935–938, 1988.

KURODA, S.-Y. Classes of languages and linear-bounded automata. **Information and Control**, v. 7, n. 2, p. 207–223, 1964.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre: Bookman, 2010.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage Learning, 2012.

SUDKAMP, T. A. **Languages and Machines: An Introduction to the Theory of Computer Science**. 3. ed. Boston: Addison-Wesley, 2006.

SZELEPCSÉNYI, R. The method of forced enumeration for nondeterministic automata. **Acta Informatica**, v. 26, n. 3, p. 279–284, 1988.
