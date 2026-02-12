# Capítulo 7 — Árvore de Derivação e Ambiguidade

## 7.1 Introdução e Contexto Histórico

A noção de **árvore de derivação** (também chamada **árvore sintática** ou *parse tree*) é uma das contribuições conceituais mais duradouras da teoria das linguagens formais à ciência da computação. Enquanto uma derivação é uma sequência linear de passos que transforma o símbolo inicial em uma cadeia de terminais, a árvore de derivação captura a **estrutura hierárquica** subjacente a essa transformação — revelando como as partes de uma sentença se relacionam entre si de forma aninhada e recursiva.

A importância dessa representação tornou-se evidente já nos primeiros esforços de construção de **compiladores** na década de 1960. Quando **John Backus** e seus colaboradores projetaram o compilador FORTRAN (1957) e, posteriormente, quando a sintaxe de ALGOL 60 foi formalizada com a **Forma de Backus-Naur** (BNF), ficou claro que a análise sintática de programas era, em essência, a construção de uma árvore de derivação a partir do código-fonte. A árvore não apenas verifica se o programa pertence à linguagem, mas fornece a estrutura necessária para a **geração de código** e a **análise semântica** (Aho, Lam, Sethi & Ullman, 2007).

Entretanto, a passagem de uma gramática para uma árvore de derivação nem sempre é unívoca. O fenômeno da **ambiguidade** — a existência de duas ou mais árvores de derivação distintas para a mesma cadeia — emergiu como um problema central tanto na teoria quanto na prática. Na teoria, a ambiguidade levou a questões profundas sobre a **decidibilidade**: saber se uma gramática livre de contexto é ambígua é, em geral, um problema **indecidível** (Hopcroft, Ullman & Motwani, 2006). Na prática, gramáticas ambíguas produzem interpretações semânticas múltiplas, o que é inaceitável para linguagens de programação — um compilador deve atribuir um **único significado** a cada programa válido.

Historicamente, o problema da ambiguidade influenciou decisivamente o **projeto de linguagens de programação**. O célebre problema do *dangling else* (else pendente), identificado já na especificação de ALGOL 60, motivou décadas de pesquisa em técnicas de desambiguação. A solução canônica — associar cada `else` ao `if` mais próximo que ainda não possui `else` — tornou-se uma convenção quase universal, adotada em C, Java, Python e inúmeras outras linguagens. Da mesma forma, as regras de **precedência** e **associatividade** de operadores, hoje presentes em toda especificação de linguagem, são essencialmente mecanismos de eliminação de ambiguidade gramatical.

> *"A grammar that produces more than one parse tree for some sentence is said to be ambiguous. For certain types of parsers, it is desirable that the grammar be made unambiguous."*
> — Aho, Lam, Sethi & Ullman, *Compilers: Principles, Techniques, and Tools* (2007)

Este capítulo estende os conceitos de gramáticas livres de contexto apresentados no Capítulo 6, concentrando-se na representação estrutural das derivações e no tratamento rigoroso da ambiguidade. Seguimos de perto as abordagens de **Hopcroft, Ullman & Motwani** (2006), **Sipser** (2012), **Menezes** (2010), **Sudkamp** (2006) e o clássico *Dragon Book* de **Aho, Lam, Sethi & Ullman** (2007).

---

## 7.2 Árvore de Derivação (Parse Tree)

### 7.2.1 Definição Formal

**Definição 7.1.** Seja G = (V, Σ, P, S) uma gramática livre de contexto. Uma **árvore de derivação** (ou **árvore sintática concreta**, *parse tree*) para G é uma árvore ordenada e rotulada que satisfaz as seguintes condições:

1. A **raiz** é rotulada com o símbolo inicial S.
2. Cada **nó interno** (não-folha) é rotulado com um símbolo não-terminal A ∈ V.
3. Cada **folha** é rotulada com um símbolo terminal a ∈ Σ ou com ε.
4. Se um nó interno é rotulado com A e seus filhos, da esquerda para a direita, são rotulados com X₁, X₂, …, Xₖ, então existe uma produção:

   > A → X₁X₂…Xₖ ∈ P

5. Se um nó interno é rotulado com A e seu único filho é rotulado com ε, então A → ε ∈ P, e esse nó ε é o **único filho** de A.

Essas condições garantem que toda árvore de derivação corresponde a uma aplicação válida das produções de G, preservando a estrutura hierárquica das substituições (Hopcroft, Ullman & Motwani, 2006).

### 7.2.2 Fronteira (Yield) da Árvore

**Definição 7.2.** A **fronteira** (ou **resultado**, *yield*) de uma árvore de derivação é a cadeia obtida pela **concatenação dos rótulos das folhas**, lidas da esquerda para a direita.

Se T é uma árvore de derivação com raiz S e fronteira w, dizemos que T é uma **árvore de derivação para w** (a partir de G). A cadeia w pertence a L(G) se e somente se existe uma árvore de derivação para w em G.

> **Teorema 7.1.** Para toda gramática livre de contexto G = (V, Σ, P, S) e toda cadeia w ∈ Σ*, vale:
>
> w ∈ L(G) ⟺ existe uma árvore de derivação em G com raiz S e fronteira w.

Este teorema estabelece a equivalência entre a noção sequencial de derivação (S ⇒* w) e a noção estrutural de árvore de derivação (Sipser, 2012).

### 7.2.3 Correspondência entre Árvores e Derivações

Um resultado fundamental relaciona árvores de derivação, derivações à esquerda e derivações à direita:

> **Teorema 7.2.** Para uma gramática livre de contexto G e uma cadeia w ∈ L(G), existe uma **bijeção** entre:
>
> (a) Árvores de derivação para w em G;
> (b) Derivações mais à esquerda de w em G;
> (c) Derivações mais à direita de w em G.

Em outras palavras, cada árvore de derivação determina **exatamente uma** derivação mais à esquerda e **exatamente uma** derivação mais à direita — e vice-versa. Derivações que diferem apenas na ordem de expansão de não-terminais independentes correspondem à **mesma** árvore (Hopcroft, Ullman & Motwani, 2006; Sudkamp, 2006).

### 7.2.4 Exemplo: Gramática S → aSb | ab

Considere a gramática G₁ = ({S}, {a, b}, P₁, S) com produções:

> P₁: S → aSb | ab

**Derivação de** `aabb`:

> S ⇒ aSb ⇒ aabb (aplicando S → ab)

**Árvore de derivação para** `aabb`:

```
        S
       /|\
      / | \
     a  S  b
       / \
      a   b
```

Lendo as folhas da esquerda para a direita: a, a, b, b → fronteira = `aabb` ✓

Note que a estrutura da árvore revela o **aninhamento** inerente à linguagem L = { aⁿbⁿ | n ≥ 1 }: cada par a…b forma um nível da árvore, refletindo a correspondência biunívoca entre os a's e os b's.

**Derivação de** `aaabbb`:

> S ⇒ aSb ⇒ aaSbb ⇒ aaabbb

```
          S
         /|\
        / | \
       a  S  b
         /|\
        / | \
       a  S  b
          |
         / \
        a   b
```

Fronteira: a, a, a, b, b, b → `aaabbb` ✓

### 7.2.5 Exemplo: Gramática de Expressões Aritméticas

Considere a gramática G₂ = ({E}, {id, +, *, (, )}, P₂, E) com produções:

> P₂: E → E+E | E*E | (E) | id

**Árvore de derivação para** `id+id*id` **(com * tendo maior precedência):**

```
           E
          /|\
         / | \
        E  +  E
        |    /|\
       id   / | \
           E  *  E
           |     |
          id    id
```

Fronteira: id, +, id, *, id → `id+id*id` ✓

Nesta árvore, a subexpressão `id*id` é agrupada primeiro (como subárvore direita do +), refletindo a convenção usual de que a multiplicação tem **maior precedência** que a adição. Porém, como veremos na Seção 7.4, esta gramática é **ambígua** — existe outra árvore de derivação para a mesma cadeia, com agrupamento diferente.

---

## 7.3 Derivação Mais à Esquerda e Mais à Direita

### 7.3.1 Derivação Mais à Esquerda (Leftmost Derivation)

**Definição 7.3.** Uma derivação S ⇒ α₁ ⇒ α₂ ⇒ … ⇒ w é uma **derivação mais à esquerda** (*leftmost derivation*) se, em cada passo αᵢ ⇒ αᵢ₊₁, o não-terminal substituído é o **mais à esquerda** na forma sentencial αᵢ. Notação: ⇒_lm.

Na derivação mais à esquerda, a escolha de qual não-terminal expandir é **determinística** (sempre o mais à esquerda); a única liberdade reside em **qual produção** aplicar. Essa propriedade torna as derivações à esquerda particularmente adequadas para **parsers top-down** (como parsers LL), que leem a entrada da esquerda para a direita e constroem a árvore da raiz para as folhas (Aho, Lam, Sethi & Ullman, 2007).

### 7.3.2 Derivação Mais à Direita (Rightmost Derivation)

**Definição 7.4.** Uma derivação S ⇒ α₁ ⇒ α₂ ⇒ … ⇒ w é uma **derivação mais à direita** (*rightmost derivation*) se, em cada passo, o não-terminal substituído é o **mais à direita** na forma sentencial corrente. Notação: ⇒_rm.

Derivações à direita são a base dos **parsers bottom-up** (como parsers LR), que constroem a árvore das folhas para a raiz. Em um parser LR, a sequência de reduções corresponde ao **reverso** de uma derivação mais à direita (Aho, Lam, Sethi & Ullman, 2007).

### 7.3.3 Exemplo Comparativo

Considere a gramática G₂ (expressões aritméticas) e a cadeia `id+id*id`. Utilizemos a árvore da Seção 7.2.5 (onde * agrupa antes de +).

**Derivação mais à esquerda:**

> E ⇒_lm E+E ⇒_lm id+E ⇒_lm id+E\*E ⇒_lm id+id\*E ⇒_lm id+id\*id

**Derivação mais à direita:**

> E ⇒_rm E+E ⇒_rm E+E\*E ⇒_rm E+E\*id ⇒_rm E+id\*id ⇒_rm id+id\*id

Ambas as derivações correspondem à **mesma árvore** de derivação — aquela em que `id*id` é subárvore de `E+E`. A árvore é a mesma; apenas a **ordem de expansão** dos não-terminais difere.

### 7.3.4 Unicidade em Gramáticas Não-Ambíguas

> **Teorema 7.3.** Se G é uma gramática **não-ambígua**, então para cada w ∈ L(G) existe:
>
> - **exatamente uma** derivação mais à esquerda,
> - **exatamente uma** árvore de derivação, e
> - **exatamente uma** derivação mais à direita.

Este teorema é consequência direta da bijeção estabelecida no Teorema 7.2. A não-ambiguidade garante que a correspondência árvore ↔ derivação à esquerda ↔ derivação à direita é uma função (e não uma relação multivalorada).

---

## 7.4 Ambiguidade

### 7.4.1 Definição Formal

**Definição 7.5.** Uma gramática livre de contexto G é **ambígua** se existe pelo menos uma cadeia w ∈ L(G) que possui **duas ou mais árvores de derivação distintas**.

Equivalentemente (pelo Teorema 7.2), G é ambígua se e somente se existe w ∈ L(G) com **duas ou mais derivações mais à esquerda distintas** (ou, equivalentemente, duas ou mais derivações mais à direita distintas).

Uma gramática que não é ambígua é chamada **não-ambígua** (ou **unívoca**). Note que a ambiguidade é uma propriedade da **gramática**, não da linguagem — uma mesma linguagem pode ser gerada tanto por gramáticas ambíguas quanto por gramáticas não-ambíguas (salvo no caso de linguagens inerentemente ambíguas, tratadas na Seção 7.6).

> *"We say that a context-free grammar G is ambiguous if there is some string in L(G) that has more than one parse tree."*
> — Hopcroft, Ullman & Motwani, *Introduction to Automata Theory, Languages, and Computation* (2006)

### 7.4.2 Exemplo Clássico: Expressões Aritméticas

Considere novamente a gramática G₂:

> E → E+E | E\*E | (E) | id

e a cadeia `id+id*id`. Esta cadeia admite **duas árvores de derivação distintas**:

**Árvore 1 — multiplicação agrupa primeiro (precedência convencional):**

```
           E
          /|\
         / | \
        E  +  E
        |    /|\
       id   / | \
           E  *  E
           |     |
          id    id
```

Interpretação: id + (id * id)

**Derivação mais à esquerda correspondente:**

> E ⇒_lm E+E ⇒_lm id+E ⇒_lm id+E\*E ⇒_lm id+id\*E ⇒_lm id+id\*id

---

**Árvore 2 — adição agrupa primeiro (precedência invertida):**

```
           E
          /|\
         / | \
        E  *  E
       /|\    |
      / | \  id
     E  +  E
     |     |
    id    id
```

Interpretação: (id + id) * id

**Derivação mais à esquerda correspondente:**

> E ⇒_lm E\*E ⇒_lm E+E\*E ⇒_lm id+E\*E ⇒_lm id+id\*E ⇒_lm id+id\*id

As duas árvores são **estruturalmente distintas** e induzem **interpretações semânticas diferentes**. Se id = 2, a Árvore 1 produz 2 + (2 × 2) = 6, enquanto a Árvore 2 produz (2 + 2) × 2 = 8. Portanto, G₂ é **ambígua**.

### 7.4.3 Exemplo Clássico: O Problema do Dangling Else

O **problema do else pendente** (*dangling else*) é talvez o exemplo mais famoso de ambiguidade em linguagens de programação. Considere a gramática simplificada:

> S → **if** E **then** S **else** S | **if** E **then** S | a
>
> E → b

e a cadeia:

> **if** b **then** **if** b **then** a **else** a

Esta cadeia possui **duas árvores de derivação distintas**:

**Árvore 1 — else associado ao if mais interno (convenção padrão):**

```
              S
              |
    if E then S
       |      |
       b   if E then S else S
              |      |      |
              b      a      a
```

Interpretação: if b then (if b then a else a)

**Árvore 2 — else associado ao if mais externo:**

```
                S
                |
    if E then S else S
       |      |      |
       b   if E then S   a
              |      |
              b      a
```

Interpretação: if b then (if b then a) else a

Na Árvore 1, o `else a` pertence ao segundo `if`; na Árvore 2, pertence ao primeiro `if`. A maioria das linguagens de programação adota a convenção da Árvore 1 (o `else` é associado ao `if` **mais próximo**), mas a gramática acima permite ambas as interpretações — portanto, é **ambígua** (Aho, Lam, Sethi & Ullman, 2007).

### 7.4.4 Impacto nos Compiladores

A ambiguidade gramatical tem consequências diretas para a construção de compiladores:

1. **Análise sintática não-determinística:** um parser para uma gramática ambígua pode encontrar múltiplas árvores de derivação, sem critério intrínseco para escolher entre elas.

2. **Interpretação semântica múltipla:** como a árvore de derivação guia a avaliação semântica (cálculo de expressões, resolução de referências, geração de código intermediário), árvores distintas produzem **significados distintos** para o mesmo programa.

3. **Eficiência:** algoritmos de parsing gerais (como CYK e Earley) podem lidar com gramáticas ambíguas, mas com custo O(n³). Parsers determinísticos eficientes (LL, LR) requerem gramáticas não-ambíguas (e, geralmente, com restrições adicionais).

Por essas razões, a eliminação de ambiguidade é uma etapa essencial no projeto de linguagens de programação e na construção de compiladores (Menezes, 2010).

---

## 7.5 Eliminação de Ambiguidade

### 7.5.1 Considerações Gerais

Não existe um **algoritmo geral** para eliminar ambiguidade de uma gramática livre de contexto — de fato, o problema de determinar se uma GLC é ambígua é **indecidível** (Hopcroft, Ullman & Motwani, 2006). Contudo, para muitos casos práticos, especialmente aqueles que surgem no projeto de linguagens de programação, existem **técnicas sistemáticas** de desambiguação.

A ideia central é **reestruturar a gramática** de modo que a estrutura sintática desejada seja imposta pelas próprias regras gramaticais, eliminando as derivações indesejadas.

### 7.5.2 Técnica 1: Imposição de Precedência de Operadores

Para a gramática ambígua de expressões aritméticas:

> E → E+E | E\*E | (E) | id

a ambiguidade surge porque a gramática não distingue entre os diferentes **níveis de precedência** dos operadores. A solução clássica é introduzir **não-terminais adicionais**, um para cada nível de precedência:

> E → E + T | T
>
> T → T \* F | F
>
> F → ( E ) | id

onde:

- **E** (expressão) trata da **adição** (menor precedência);
- **T** (termo) trata da **multiplicação** (maior precedência);
- **F** (fator) trata de **átomos** e **parênteses** (maior precedência).

Esta gramática é **não-ambígua** e gera a mesma linguagem que G₂.

**Princípio:** operadores de **menor precedência** aparecem nas regras dos não-terminais de **nível mais alto** (mais próximos do símbolo inicial); operadores de **maior precedência** aparecem em níveis mais baixos. Os parênteses permitem "reiniciar" a precedência, voltando ao nível mais alto via a produção F → (E).

### 7.5.3 Técnica 2: Imposição de Associatividade

Além da precedência, a **associatividade** dos operadores também precisa ser definida:

- **Associatividade à esquerda** (a - b - c = (a - b) - c): use regras **recursivas à esquerda**:
  > E → E + T | T

- **Associatividade à direita** (a ^ b ^ c = a ^ (b ^ c)): use regras **recursivas à direita**:
  > E → T ^ E | T

Na gramática não-ambígua E → E+T | T, a regra E → E+T é **recursiva à esquerda**, o que força `id+id+id` a ser agrupado como `(id+id)+id` — exatamente a associatividade à esquerda desejada.

### 7.5.4 Técnica 3: Resolução do Dangling Else

Para a gramática do dangling else, a estratégia é dividir os comandos (*statements*) em duas categorias:

- **Comandos casados** (*matched*): todo `if` possui um `else` correspondente.
- **Comandos não-casados** (*unmatched*): algum `if` não possui `else`.

A gramática não-ambígua resultante é:

> S → M | U
>
> M → **if** E **then** M **else** M | a
>
> U → **if** E **then** S | **if** E **then** M **else** U

Esta gramática garante que o `else` é sempre associado ao `if` **não-casado mais próximo** (*nearest unmatched if*), eliminando a ambiguidade (Aho, Lam, Sethi & Ullman, 2007).

### 7.5.5 Derivação Única para id+id*id

Considere a gramática não-ambígua:

> E → E + T | T
>
> T → T \* F | F
>
> F → ( E ) | id

**Derivação mais à esquerda de** `id+id*id`:

> E ⇒_lm E+T ⇒_lm T+T ⇒_lm F+T ⇒_lm id+T ⇒_lm id+T\*F ⇒_lm id+F\*F ⇒_lm id+id\*F ⇒_lm id+id\*id

**Árvore de derivação (única):**

```
              E
             /|\
            / | \
           E  +  T
           |    /|\
           T   / | \
           |  T  *  F
           F  |     |
           |  F    id
          id  |
              id
```

Fronteira: id, +, id, *, id → `id+id*id` ✓

Observe que nesta árvore:
- A subexpressão `id*id` é agrupada como subárvore de T (nível de multiplicação);
- A adição opera sobre E e T, garantindo que + tem **menor precedência** que \*;
- A recursão à esquerda em E → E+T e T → T\*F garante **associatividade à esquerda**.

Esta é a **única** árvore de derivação possível para `id+id*id` nesta gramática — a ambiguidade foi eliminada.

---

## 7.6 Linguagens Inerentemente Ambíguas

### 7.6.1 Definição

**Definição 7.6.** Uma linguagem livre de contexto L é **inerentemente ambígua** se **toda** gramática livre de contexto G tal que L(G) = L é ambígua.

Em outras palavras, a ambiguidade não é um defeito da gramática que poderia ser corrigido por uma reformulação — é uma propriedade **intrínseca** da linguagem. Nenhuma reescrita das regras de produção pode eliminá-la.

### 7.6.2 Exemplo Clássico

O exemplo clássico de linguagem inerentemente ambígua é:

> L = L₁ ∪ L₂

onde:

> L₁ = { aⁿbⁿcᵐdᵐ | n ≥ 1, m ≥ 1 }
>
> L₂ = { aⁿbᵐcᵐdⁿ | n ≥ 1, m ≥ 1 }

A cadeia w = aⁿbⁿcⁿdⁿ pertence à **interseção** L₁ ∩ L₂ (basta tomar m = n). Para derivar tal cadeia, qualquer gramática para L deve "decidir" se a correspondência primária é entre os a's e b's (e entre c's e d's, como em L₁) ou entre os a's e d's (e entre b's e c's, como em L₂). Como ambas as interpretações são necessárias para gerar L₁ ∪ L₂, e como uma GLC não pode verificar simultaneamente ambas as correspondências para a mesma subcadeia, toda gramática para L será necessariamente ambígua nas cadeias aⁿbⁿcⁿdⁿ.

A demonstração rigorosa de que L é inerentemente ambígua foi estabelecida por **Parikh** (1966) e utiliza técnicas sofisticadas de combinatória e teoria dos números. Uma prova detalhada pode ser encontrada em Hopcroft, Ullman & Motwani (2006, Cap. 7) e em Sudkamp (2006, Cap. 18).

### 7.6.3 Teorema de Parikh

O **Teorema de Parikh** (1966) estabelece uma conexão profunda entre linguagens livres de contexto e linguagens regulares em termos de suas **imagens de Parikh** (vetores de contagem de símbolos). Embora o teorema em si não trate diretamente de ambiguidade, seus corolários e as técnicas utilizadas em sua demonstração são frequentemente empregados para provar que certas linguagens são inerentemente ambíguas.

> **Teorema 7.4 (Parikh, 1966).** Toda linguagem livre de contexto tem a mesma imagem de Parikh que alguma linguagem regular.

Uma consequência importante é que se uma linguagem livre de contexto L é "comutativa" (ou seja, a pertinência a L depende apenas da contagem de cada símbolo, não da ordem), então L é necessariamente regular. Isso fornece uma ferramenta para demonstrar que certas linguagens **não** são livres de contexto, complementando o Lema do Bombeamento.

A existência de linguagens inerentemente ambíguas demonstra um **limite fundamental** da classe das linguagens livres de contexto: a ambiguidade pode ser uma propriedade estrutural inescapável, não um artefato de uma gramática mal projetada (Sipser, 2012).

---

## 7.7 Aplicações em Compiladores

### 7.7.1 Análise Sintática (Parsing)

A fase de **análise sintática** de um compilador tem como objetivo central a construção (explícita ou implícita) de uma árvore de derivação para o programa-fonte. O parser recebe uma sequência de *tokens* (produzida pelo analisador léxico) e verifica se essa sequência pode ser gerada pela gramática da linguagem, produzindo a estrutura sintática correspondente (Aho, Lam, Sethi & Ullman, 2007).

### 7.7.2 Parsing Top-Down (Parsers LL)

Nos parsers **top-down** (descendentes), a árvore de derivação é construída da **raiz para as folhas**:

1. Iniciar com o símbolo inicial S na raiz.
2. Expandir o não-terminal mais à esquerda usando uma produção adequada.
3. Repetir até que todas as folhas sejam terminais que casam com a entrada.

Este processo corresponde à construção de uma **derivação mais à esquerda**. Os parsers **LL(k)** (*Left-to-right, Leftmost derivation, k symbols of lookahead*) utilizam k símbolos de antecipação (*lookahead*) para decidir deterministicamente qual produção aplicar. Parsers LL(1) são particularmente populares por sua simplicidade e eficiência (Menezes, 2010).

### 7.7.3 Parsing Bottom-Up (Parsers LR)

Nos parsers **bottom-up** (ascendentes), a árvore é construída das **folhas para a raiz**:

1. Iniciar com os terminais da entrada nas folhas.
2. Identificar um **handle** (subcadeia que corresponde ao lado direito de uma produção).
3. Reduzir o handle ao não-terminal do lado esquerdo da produção.
4. Repetir até reduzir toda a entrada ao símbolo inicial S.

Este processo corresponde ao **reverso** de uma derivação mais à direita. Os parsers **LR(k)** (*Left-to-right, Rightmost derivation in reverse, k symbols of lookahead*) são mais poderosos que os LL(k), aceitando uma classe maior de gramáticas. Variantes incluem SLR, LALR (utilizado pelo Yacc/Bison) e LR canônico (Aho, Lam, Sethi & Ullman, 2007).

### 7.7.4 Árvore Sintática Abstrata (AST) vs. Árvore de Derivação Concreta

Na prática, compiladores raramente constroem a árvore de derivação concreta (parse tree) completa. Em vez disso, constroem uma **Árvore Sintática Abstrata** (AST, *Abstract Syntax Tree*), que é uma versão **simplificada** da árvore de derivação:

| Árvore de Derivação (Concreta)         | Árvore Sintática Abstrata (AST)         |
|-----------------------------------------|-----------------------------------------|
| Contém todos os não-terminais           | Omite não-terminais auxiliares           |
| Contém todos os terminais (parênteses, palavras-chave de agrupamento) | Omite terminais redundantes |
| Reflete fielmente a gramática           | Reflete a estrutura semântica essencial  |
| Pode ser muito profunda e verbosa       | Compacta e orientada à semântica         |

**Exemplo.** Para `id+id*id` com a gramática não-ambígua:

Árvore de derivação concreta (como na Seção 7.5.5 — contém nós E, T, F).

AST correspondente:

```
        +
       / \
      id   *
          / \
         id  id
```

A AST captura diretamente a estrutura da expressão: o operador `+` na raiz, com o operando `id` à esquerda e a subexpressão `id*id` (representada pelo nó `*`) à direita. Os não-terminais intermediários (E, T, F) e os parênteses são dispensados por não contribuírem para a semântica.

### 7.7.5 Contribuições do Dragon Book

O livro *Compilers: Principles, Techniques, and Tools* de **Aho, Sethi e Ullman** (1986), conhecido como *Dragon Book*, e sua segunda edição com **Lam** (2007), é possivelmente a obra mais influente na área de construção de compiladores. Entre suas contribuições para o tema deste capítulo, destacam-se:

- A formalização das relações entre gramáticas, derivações e árvores de derivação;
- O desenvolvimento sistemático de técnicas de eliminação de ambiguidade;
- A teoria dos parsers LL e LR, incluindo algoritmos de construção de tabelas;
- A noção de **tradução dirigida pela sintaxe** (*syntax-directed translation*), na qual atributos semânticos são associados aos nós da árvore de derivação e avaliados durante o parsing;
- Ferramentas como **Yacc** (*Yet Another Compiler-Compiler*), que geram parsers LALR automaticamente a partir de especificações gramaticais.

---

## 7.8 Exemplo em C

Uma implementação em linguagem C dos conceitos e algoritmos discutidos neste capítulo está disponível no arquivo `src/07-derivacao/arvore_derivacao.c`:

- **Construção de árvore de derivação** para gramáticas livres de contexto simples

Consulte os arquivos-fonte e seus respectivos comentários para detalhes de implementação. Cada programa inclui exemplos de entrada que correspondem às gramáticas e árvores apresentadas nas seções anteriores, permitindo ao estudante verificar os resultados manualmente.

---

## Referências

AHO, A. V.; LAM, M. S.; SETHI, R.; ULLMAN, J. D. **Compilers: Principles, Techniques, and Tools**. 2. ed. Boston: Addison-Wesley, 2007.

AHO, A. V.; SETHI, R.; ULLMAN, J. D. **Compilers: Principles, Techniques, and Tools**. Reading, MA: Addison-Wesley, 1986.

CHOMSKY, N. On certain formal properties of grammars. **Information and Control**, v. 2, n. 2, p. 137–167, 1959.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Elsevier, 2006.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre: Bookman, 2010.

PARIKH, R. J. On context-free languages. **Journal of the ACM**, v. 13, n. 4, p. 570–581, 1966.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage Learning, 2012.

SUDKAMP, T. A. **Languages and Machines: An Introduction to the Theory of Computer Science**. 3. ed. Boston: Addison-Wesley, 2006.
