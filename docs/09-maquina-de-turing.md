# Capítulo 9 — Máquina de Turing

## 9.1 Introdução e Contexto Histórico

A **Máquina de Turing** (MT) é o modelo computacional mais poderoso e influente da teoria da computação. Proposta em 1936 pelo matemático britânico **Alan Mathison Turing** no artigo seminal *"On Computable Numbers, with an Application to the Entscheidungsproblem"*, a Máquina de Turing não apenas resolveu um dos grandes problemas abertos da lógica matemática, mas também lançou os fundamentos teóricos de toda a ciência da computação moderna. Diferentemente dos autômatos finitos e dos autômatos com pilha estudados nos capítulos anteriores, a Máquina de Turing dispõe de uma **fita infinita** de leitura e escrita, o que lhe confere poder computacional suficiente para simular qualquer algoritmo concebível.

O contexto histórico da criação da Máquina de Turing remonta ao **Entscheidungsproblem** (problema da decisão), formulado por **David Hilbert** e **Wilhelm Ackermann** em 1928. Hilbert perguntava se existiria um procedimento mecânico capaz de determinar, para qualquer enunciado da lógica de primeira ordem, se este é universalmente válido. A questão exigia, antes de tudo, uma definição precisa do conceito de "procedimento mecânico" — ou seja, de **computabilidade**. Turing respondeu negativamente ao Entscheidungsproblem, demonstrando que não existe Máquina de Turing capaz de decidir, para toda sentença da lógica de primeira ordem, se ela é válida ou não (Turing, 1936).

De forma independente e quase simultânea, **Alonzo Church** chegou à mesma conclusão por meio do **cálculo lambda** (*lambda calculus*), um formalismo que captura a noção de função computável por uma abordagem radicalmente diferente (Church, 1936). A equivalência entre os dois modelos — demonstrada pelo próprio Turing em um apêndice de seu artigo — deu origem à **Tese de Church-Turing**, que afirma que todo procedimento algorítmico efetivo pode ser realizado por uma Máquina de Turing. Embora não seja um teorema no sentido formal (pois envolve o conceito informal de "algoritmo"), a Tese de Church-Turing é universalmente aceita e constitui um dos pilares da teoria da computação (Sipser, 2012).

As contribuições de Turing transcendem a solução do Entscheidungsproblem. O conceito de **Máquina de Turing Universal** — uma máquina capaz de simular qualquer outra Máquina de Turing a partir de sua descrição codificada — antecipou em mais de uma década a arquitetura de computadores de programa armazenado proposta por **John von Neumann** (1945). Além disso, a demonstração da **indecidibilidade** do problema da parada (*halting problem*) inaugurou o estudo dos limites fundamentais da computação, revelando que existem problemas bem formulados que **nenhum** algoritmo pode resolver.

Na hierarquia de Chomsky, a Máquina de Turing ocupa a posição mais elevada, correspondendo ao **Tipo 0** (gramáticas irrestritas). As linguagens reconhecidas por Máquinas de Turing — denominadas **recursivamente enumeráveis** — englobam todas as classes inferiores da hierarquia:

| Tipo | Classe de Gramática | Autômato Reconhecedor | Exemplo |
|------|--------------------|-----------------------|---------|
| **0** | **Irrestrita** | **Máquina de Turing** | **L = { ⟨M⟩ \| M para com entrada vazia }** |
| 1 | Sensível ao Contexto | Autômato Linearmente Limitado | L = { aⁿbⁿcⁿ \| n ≥ 1 } |
| 2 | Livre de Contexto | Autômato com Pilha | L = { aⁿbⁿ \| n ≥ 1 } |
| 3 | Regular | Autômato Finito | L = { w ∈ {a,b}* \| w termina com ab } |

> *"It is possible to invent a single machine which can be used to compute any computable sequence. If this machine U is supplied with a tape on the beginning of which is written the S.D ['standard description'] of some computing machine M, then U will compute the same sequence as M."*
> — Turing, *On Computable Numbers, with an Application to the Entscheidungsproblem* (1936)

Este capítulo apresenta a definição formal da Máquina de Turing, suas variantes, as classes de linguagens que ela define e os limites fundamentais da computação. Seguimos de perto as abordagens de **Hopcroft, Ullman & Motwani** (2006), **Sipser** (2012), **Menezes** (2010), **Sudkamp** (2006) e os textos clássicos de **Turing** (1936), **Church** (1936) e **Davis** (1958).

---

## 9.2 Definição Formal da Máquina de Turing

### 9.2.1 A Máquina de Turing Determinística

**Definição 9.1.** Uma **Máquina de Turing** (determinística, com fita infinita à direita) é uma 7-tupla:

> M = (Q, Σ, Γ, δ, q₀, q_aceita, q_rejeita)

onde:

- **Q** é um conjunto finito de **estados**;
- **Σ** é o **alfabeto de entrada**, um conjunto finito de símbolos que **não** contém o símbolo branco ⊔;
- **Γ** é o **alfabeto da fita**, um conjunto finito com Σ ⊂ Γ e ⊔ ∈ Γ, onde ⊔ é o **símbolo branco** (*blank symbol*);
- **δ** é a **função de transição**:

  > δ: (Q \ {q_aceita, q_rejeita}) × Γ → Q × Γ × {L, R}

- **q₀** ∈ Q é o **estado inicial**;
- **q_aceita** ∈ Q é o **estado de aceitação**;
- **q_rejeita** ∈ Q é o **estado de rejeição**, com q_aceita ≠ q_rejeita.

A função de transição δ(q, a) = (q', b, D) indica que, quando a máquina está no estado q lendo o símbolo a na fita, ela: (1) muda para o estado q'; (2) escreve o símbolo b na célula atual da fita, substituindo a; e (3) move a cabeça de leitura/escrita uma célula para a **esquerda** (L) ou para a **direita** (R). Não há transições definidas a partir dos estados q_aceita e q_rejeita — a computação termina imediatamente ao alcançar qualquer um deles (Sipser, 2012; Hopcroft, Ullman & Motwani, 2006).

> **Atenção:** A exigência de que q_aceita ≠ q_rejeita é fundamental para que a máquina possa distinguir entre aceitação e rejeição de forma inequívoca. Além disso, diferentemente dos autômatos finitos e dos autômatos com pilha, a Máquina de Turing pode **escrever** na fita e **mover-se em ambas as direções**, o que lhe confere a capacidade de reutilizar e modificar informações previamente processadas.

### 9.2.2 Configuração

**Definição 9.2.** Uma **configuração** (ou **descrição instantânea**) de uma Máquina de Turing M é uma cadeia da forma:

> uqv, com u ∈ Γ*, q ∈ Q, v ∈ Γ*

onde u é o conteúdo da fita à esquerda da cabeça de leitura, q é o estado atual, e v é o conteúdo da fita a partir da posição da cabeça (inclusive) até o último símbolo não-branco à direita (ou o símbolo sob a cabeça, se todos à direita forem brancos). A cabeça de leitura encontra-se posicionada sobre o **primeiro símbolo** de v.

A **configuração inicial** para uma entrada w = w₁w₂…wₙ ∈ Σ* é:

> q₀w₁w₂…wₙ

indicando que a máquina inicia no estado q₀ com a cabeça sobre o primeiro símbolo da entrada, e o restante da fita contém símbolos brancos.

Uma configuração é de **aceitação** se contém o estado q_aceita; é de **rejeição** se contém o estado q_rejeita; é de **parada** se é de aceitação ou de rejeição. Em qualquer configuração de parada, a computação termina imediatamente.

**Definição 9.3 (Passo de computação).** Dizemos que a configuração C₁ **produz** a configuração C₂ (escrevemos C₁ ⊢ C₂) se C₂ é obtida de C₁ pela aplicação de exatamente uma transição de δ. Escrevemos C₁ ⊢* Cₖ se C₁ produz Cₖ em zero ou mais passos.

### 9.2.3 Computação e Aceitação

**Definição 9.4.** A Máquina de Turing M **aceita** uma cadeia w se existe uma sequência de configurações C₁, C₂, …, Cₖ tal que:

1. C₁ = q₀w (configuração inicial);
2. cada Cᵢ **produz** Cᵢ₊₁ segundo a função de transição δ (Cᵢ ⊢ Cᵢ₊₁);
3. Cₖ contém o estado q_aceita (configuração de aceitação).

A máquina **rejeita** w se a sequência termina em uma configuração contendo q_rejeita. Se a computação **nunca atinge** q_aceita nem q_rejeita, a máquina **entra em laço infinito** (*loop*) sobre a entrada w. Essa possibilidade de laço infinito é uma diferença crucial em relação aos modelos mais restritos: autômatos finitos e autômatos com pilha sempre param após processar a entrada, mas uma Máquina de Turing pode computar indefinidamente.

**Definição 9.5.** A **linguagem reconhecida** (ou **aceita**) por M é:

> L(M) = { w ∈ Σ* | M aceita w }

---

## 9.3 Exemplos de Máquinas de Turing

### 9.3.1 MT para L = { aⁿbⁿcⁿ | n ≥ 1 }

A linguagem L = { aⁿbⁿcⁿ | n ≥ 1 } é o exemplo canônico de linguagem que **não** é livre de contexto (como demonstrado pelo Lema do Bombeamento para GLCs), mas que pode ser reconhecida por uma Máquina de Turing. No Capítulo 8, vimos que esta linguagem é sensível ao contexto; naturalmente, toda linguagem sensível ao contexto é também reconhecida por uma MT.

**Exemplo 9.1.** Máquina de Turing M₁ que reconhece L = { aⁿbⁿcⁿ | n ≥ 1 }:

**Ideia informal:** A cada iteração, M₁ marca (substitui por X, Y, Z, respectivamente) um `a`, um `b` e um `c` não marcados. Quando todos os símbolos estiverem marcados e nenhum símbolo não marcado restar, a máquina aceita.

> M₁ = ({q₀, q₁, q₂, q₃, q₄, q_aceita, q_rejeita}, {a, b, c}, {a, b, c, X, Y, Z, ⊔}, δ, q₀, q_aceita, q_rejeita)

**Transições principais:**

| Estado | Lê | Escreve | Move | Próximo estado | Descrição |
|--------|-----|---------|------|----------------|-----------|
| q₀ | a | X | R | q₁ | Marca um `a` |
| q₀ | Y | Y | R | q₃ | Verifica se todos marcados |
| q₁ | a | a | R | q₁ | Avança sobre `a`'s |
| q₁ | Y | Y | R | q₁ | Avança sobre `Y`'s |
| q₁ | b | Y | R | q₂ | Marca um `b` |
| q₂ | b | b | R | q₂ | Avança sobre `b`'s |
| q₂ | Z | Z | R | q₂ | Avança sobre `Z`'s |
| q₂ | c | Z | L | q₄ | Marca um `c` |
| q₃ | Y | Y | R | q₃ | Avança sobre `Y`'s |
| q₃ | Z | Z | R | q₃ | Avança sobre `Z`'s |
| q₃ | ⊔ | ⊔ | R | q_aceita | Todos marcados → aceita |
| q₄ | * | * | L | q₄ | Retorna ao início |
| q₄ | X | X | R | q₀ | Reinicia ciclo |

**Exemplo 9.2.** Trace da computação de M₁ sobre a entrada `aabbcc`:

> q₀aabbcc
> ⊢ Xq₁abbcc
> ⊢ Xaq₁bbcc
> ⊢ XaYq₂bcc
> ⊢ XaYbq₂cc
> ⊢ XaYq₄bZc
> ⊢ Xaq₄YbZc
> ⊢ Xq₄aYbZc
> ⊢ q₄XaYbZc
> ⊢ Xq₀aYbZc
> ⊢ XXq₁YbZc
> ⊢ XXYq₁bZc
> ⊢ XXYYq₂Zc
> ⊢ XXYYZq₂c
> ⊢ XXYYq₄ZZ
> ⊢ … (retorna ao início)
> ⊢ XXq₀YYZZc → … → aceita

### 9.3.2 MT para Palíndromos

**Exemplo 9.3.** Máquina de Turing M₂ que reconhece L = { w ∈ {a, b}* | w = wᴿ } (palíndromos sobre {a, b}):

**Ideia informal:** M₂ verifica se o primeiro e o último símbolo não marcados são iguais. Em cada iteração, marca o primeiro símbolo, percorre a fita até o último símbolo não marcado, verifica a igualdade, marca-o, e retorna ao início.

> M₂ = ({q₀, q_a, q_b, q_volta, q_verifica, q_aceita, q_rejeita}, {a, b}, {a, b, X, ⊔}, δ, q₀, q_aceita, q_rejeita)

**Descrição dos estados:**

- **q₀:** Lê o primeiro símbolo não marcado. Se `a`, vai para q_a; se `b`, vai para q_b; se `⊔` ou `X`, aceita (cadeia vazia ou todos marcados).
- **q_a:** Avança à direita até encontrar o último símbolo não marcado. Verifica se é `a`; se sim, marca e retorna.
- **q_b:** Avança à direita até encontrar o último símbolo não marcado. Verifica se é `b`; se sim, marca e retorna.
- **q_volta:** Retorna a cabeça ao início (primeiro símbolo não marcado) para nova iteração.
- **q_verifica:** Verifica se todos os símbolos foram marcados (condição de aceitação).

**Exemplo 9.4.** Trace parcial de M₂ sobre a entrada `abba`:

> q₀abba
> ⊢ Xq_abba
> ⊢ Xbq_aba
> ⊢ Xbbq_aa
> ⊢ Xbbq_verifica(a) → a = a ✓ → marca: XbbX
> ⊢ q_volta XbbX → retorna ao início
> ⊢ Xq₀bbX
> ⊢ XXq_bbX
> ⊢ XXq_verifica(b) → b = b ✓ → marca: XXXX
> ⊢ q₀XXXX → todos marcados → q_aceita ✓

---

## 9.4 Variantes da Máquina de Turing

Uma propriedade notável da Máquina de Turing é a sua **robustez**: diversas variantes naturais do modelo básico resultam em poder computacional **equivalente**. Essa robustez é, em si, uma evidência forte em favor da Tese de Church-Turing.

### 9.4.1 MT Multifita

**Definição 9.6.** Uma **Máquina de Turing multifita** (*multi-tape Turing machine*) é uma MT que possui k ≥ 2 fitas, cada uma com sua própria cabeça de leitura/escrita. A função de transição tem a forma:

> δ: Q × Γᵏ → Q × Γᵏ × {L, R, S}ᵏ

onde S indica que a cabeça permanece estacionária. A entrada é fornecida na primeira fita; as demais iniciam em branco.

**Teorema 9.1.** Toda Máquina de Turing multifita com k fitas pode ser simulada por uma Máquina de Turing padrão (de fita única).

> **Prova (esboço).** A simulação utiliza uma única fita cujo conteúdo codifica as k fitas intercaladas, com marcadores especiais para indicar a posição de cada cabeça. Para simular um passo da MT multifita, a MT de fita única faz uma varredura completa de sua fita para ler os k símbolos sob as cabeças virtuais, determina a transição a aplicar, e faz uma segunda varredura para atualizar os símbolos e as posições das cabeças. O overhead é polinomial no comprimento da fita, mas não altera a classe de linguagens reconhecidas (Sipser, 2012).

### 9.4.2 MT Não-Determinística

**Definição 9.7.** Uma **Máquina de Turing não-determinística** (MTND) é definida como a MT determinística, exceto que a função de transição é substituída por uma **relação de transição**:

> δ: (Q \ {q_aceita, q_rejeita}) × Γ → P(Q × Γ × {L, R})

onde P(·) denota o conjunto das partes. Para cada par (estado, símbolo), pode haver **múltiplas** transições possíveis. A MTND aceita uma entrada w se **existe pelo menos uma** sequência de escolhas que leva a uma configuração de aceitação.

**Teorema 9.2.** Toda Máquina de Turing não-determinística pode ser simulada por uma Máquina de Turing determinística.

> **Prova (esboço).** A MT determinística explora sistematicamente todas as ramificações possíveis da computação não-determinística usando uma busca em largura (*breadth-first search*). Utiliza-se uma MT de 3 fitas: a primeira armazena a entrada, a segunda registra a ramificação sendo explorada (codificada como sequência de escolhas), e a terceira serve como fita de trabalho para simular a computação. A simulação é exaustiva: se alguma ramificação leva à aceitação, a MT determinística eventualmente a encontrará. Se nenhuma ramificação aceita e todas terminam (rejeição ou parada), a MT determinística rejeita. A máquina determinística resultante pode ser exponencialmente mais lenta, mas reconhece a mesma linguagem (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 9.4.3 MT com Fita Infinita em Ambas as Direções

**Definição 9.8.** Uma **Máquina de Turing com fita bi-infinita** é uma MT cuja fita se estende infinitamente tanto para a esquerda quanto para a direita. A cabeça de leitura/escrita pode mover-se em ambas as direções sem restrição.

**Teorema 9.3.** Uma MT com fita bi-infinita é equivalente em poder computacional a uma MT padrão (fita infinita apenas à direita).

> **Prova (esboço).** A simulação utiliza uma MT de duas fitas: a primeira fita armazena a metade direita da fita bi-infinita (a partir da posição inicial), e a segunda armazena a metade esquerda (em ordem reversa). Movimentos à direita na fita bi-infinita correspondem a movimentos à direita na primeira fita; movimentos à esquerda da posição inicial correspondem a movimentos à direita na segunda fita. Pelo Teorema 9.1, a MT de duas fitas pode ser convertida em uma MT de fita única (Sipser, 2012).

### 9.4.4 Equivalência entre Variantes

> **Teorema 9.4.** As seguintes classes de máquinas reconhecem exatamente a mesma classe de linguagens (as linguagens recursivamente enumeráveis):
>
> (a) Máquina de Turing determinística (fita única, infinita à direita);
> (b) Máquina de Turing multifita;
> (c) Máquina de Turing não-determinística;
> (d) Máquina de Turing com fita bi-infinita.

Essa equivalência é um dos resultados mais importantes da teoria da computação, pois mostra que o poder computacional da MT é **invariante** sob modificações naturais do modelo. Quaisquer diferenças entre as variantes são de **eficiência** (tempo ou espaço), não de **capacidade** (Hopcroft, Ullman & Motwani, 2006).

> **Atenção:** A equivalência entre variantes não implica equivalência de **eficiência**. Uma MT não-determinística pode aceitar em tempo polinomial problemas que, segundo a conjectura P ≠ NP, requerem tempo exponencial em uma MT determinística. Entretanto, do ponto de vista da **decidibilidade** e da **reconhecibilidade**, todas as variantes são idênticas.

---

## 9.5 Linguagens Recursivamente Enumeráveis e Recursivas

### 9.5.1 Linguagens Turing-Reconhecíveis (RE)

**Definição 9.9.** Uma linguagem L é **Turing-reconhecível** (ou **recursivamente enumerável**, RE) se existe uma Máquina de Turing M tal que:

> L = L(M)

isto é, M aceita toda cadeia w ∈ L. Para cadeias w ∉ L, a máquina pode **rejeitar** ou **entrar em laço infinito**. O termo "recursivamente enumerável" provém do fato de que, se L é não-vazia, existe uma MT que **enumera** (lista) todos os elementos de L: a máquina escreve na fita, um a um, todos os membros de L (possivelmente com repetições e fora de ordem). Essa equivalência entre reconhecimento e enumeração justifica a nomenclatura (Sipser, 2012).

**Exemplo 9.5.** A linguagem A_MT = { ⟨M, w⟩ | M é uma MT que aceita w } é recursivamente enumerável: uma Máquina de Turing Universal U pode simular M sobre w e aceitar se M aceita. Porém, se M não aceita w (rejeita ou entra em laço), U pode não parar.

### 9.5.2 Linguagens Turing-Decidíveis (Recursivas)

**Definição 9.10.** Uma linguagem L é **Turing-decidível** (ou **recursiva**) se existe uma Máquina de Turing M que **para** sobre toda entrada:

- Se w ∈ L, então M aceita w.
- Se w ∉ L, então M rejeita w.

Uma tal máquina é chamada de **decisor** (*decider*). Observe que todo decisor é, em particular, um reconhecedor; logo, toda linguagem decidível é recursivamente enumerável. A distinção entre reconhecimento e decisão é sutil mas essencial: um reconhecedor pode não parar sobre entradas que não pertencem à linguagem, enquanto um decisor **sempre** para, produzindo uma resposta definitiva para qualquer entrada.

**Exemplo 9.6.** A linguagem L = { aⁿbⁿ | n ≥ 0 } é decidível: uma MT pode percorrer a entrada, marcando pares de `a`'s e `b`'s, e aceitar se e somente se todos os símbolos forem marcados sem que haja sobras de `a`'s ou `b`'s. Essa MT sempre para, pois a cada iteração pelo menos dois símbolos são marcados, e o número total de símbolos é finito.

### 9.5.3 Relação entre as Classes

**Teorema 9.5.** A classe das linguagens recursivas está estritamente contida na classe das linguagens recursivamente enumeráveis:

> Recursivas ⊂ RE

> **Prova (esboço).** A inclusão Recursivas ⊆ RE segue diretamente das definições: todo decisor é um reconhecedor. Para mostrar que a inclusão é **estrita** (própria), basta exibir uma linguagem que é RE mas não recursiva. A linguagem de aceitação A_MT = { ⟨M, w⟩ | M é uma MT que aceita w } é Turing-reconhecível (uma MT universal pode simulá-la), mas não é decidível (como será demonstrado na Seção 9.7). Portanto, Recursivas ⊊ RE (Sipser, 2012).

### 9.5.4 Linguagens que Não São RE

**Teorema 9.6.** Existem linguagens que não são recursivamente enumeráveis.

> **Prova (esboço).** O conjunto de todas as linguagens sobre um alfabeto Σ tem cardinalidade **incontável** (pois corresponde ao conjunto das partes de Σ*, isomorfo a 2^ℕ). Por outro lado, o conjunto de todas as Máquinas de Turing é **enumerável** (cada MT admite uma descrição finita como cadeia sobre um alfabeto fixo). Como há mais linguagens do que máquinas, existem linguagens que não são reconhecidas por nenhuma MT (Sipser, 2012; Hopcroft, Ullman & Motwani, 2006).

### 9.5.5 Complemento e Decidibilidade

**Teorema 9.7.** Uma linguagem L é decidível se e somente se tanto L quanto seu complemento L̄ = Σ* \ L são recursivamente enumeráveis.

> **Prova (esboço).** (⇒) Se L é decidível, um decisor M pode ser convertido em reconhecedores tanto para L quanto para L̄ (basta inverter aceitação e rejeição). (⇐) Se M₁ reconhece L e M₂ reconhece L̄, construímos um decisor que simula M₁ e M₂ em paralelo sobre a entrada w: como w ∈ L ou w ∈ L̄, uma das duas máquinas necessariamente aceita, e o decisor para com a resposta apropriada (Sipser, 2012).

---

## 9.6 Tese de Church-Turing

### 9.6.1 Enunciado

A **Tese de Church-Turing** (também chamada **Tese de Church** ou **Hipótese de Church-Turing**) afirma que:

> A classe das funções **intuitivamente computáveis** (isto é, calculáveis por algum procedimento algorítmico efetivo) coincide com a classe das funções **Turing-computáveis**.

Em termos de linguagens:

> Uma linguagem é **decidível por um algoritmo** se e somente se é **Turing-decidível**.

Observe que a Tese de Church-Turing **não** é um teorema matemático — é uma **tese** (ou **hipótese**) que relaciona um conceito formal (Turing-computabilidade) com um conceito informal (computabilidade intuitiva). Não pode, portanto, ser demonstrada no sentido rigoroso; pode, contudo, ser refutada pela exibição de um contraexemplo (Sipser, 2012).

### 9.6.2 Evidências

A Tese de Church-Turing é sustentada por diversas linhas de evidência convergentes:

1. **Equivalência de modelos formais.** Todos os modelos de computação propostos independentemente — Máquinas de Turing (Turing, 1936), cálculo lambda (Church, 1936), funções recursivas de Gödel-Herbrand-Kleene, sistemas de Post, máquinas de registradores — foram demonstrados **equivalentes** em poder computacional. A convergência de formalismos tão diversos para a mesma classe de funções computáveis é um forte indício de que essa classe é "natural" e independente do modelo escolhido.

2. **Ausência de contraexemplo.** Em quase nove décadas desde a formulação da tese, **nenhum** procedimento algorítmico intuitivamente aceitável foi descoberto que não pudesse ser implementado por uma Máquina de Turing.

3. **Robustez do modelo.** Como visto na Seção 9.4, variantes substanciais da MT (multifita, não-determinística, fita bi-infinita) não ampliam a classe de linguagens reconhecíveis. Essa robustez sugere que a MT captura uma propriedade intrínseca da computabilidade, não um artefato da definição particular.

### 9.6.3 Implicações

A Tese de Church-Turing tem implicações profundas:

- **Fundamentos:** Permite afirmar que problemas **indecidíveis** (como o problema da parada) não podem ser resolvidos por **nenhum** método algorítmico — não apenas por Máquinas de Turing.
- **Prática:** Autoriza o uso de descrições informais de alto nível para algoritmos, com a garantia de que qualquer algoritmo assim descrito pode ser implementado como uma MT.
- **Limites da computação:** A tese delimita a fronteira entre o **computável** e o **não-computável**, uma distinção central para a ciência da computação, a lógica e a matemática (Sipser, 2012; Davis, 1958).

---

## 9.7 Decidibilidade e Indecidibilidade

### 9.7.1 Problemas Decidíveis

**Definição 9.11.** Um problema de decisão é **decidível** (ou **computável**) se existe uma Máquina de Turing (decisor) que, para toda instância do problema, responde corretamente "sim" ou "não" em tempo finito.

**Exemplo 9.7.** São decidíveis os seguintes problemas sobre linguagens regulares:

- A_AFD = { ⟨B, w⟩ | B é um AFD que aceita w }
- V_AFD = { ⟨A⟩ | A é um AFD e L(A) = ∅ }
- EQ_AFD = { ⟨A, B⟩ | A e B são AFDs com L(A) = L(B) }

**Exemplo 9.8.** São decidíveis os seguintes problemas sobre linguagens livres de contexto:

- A_GLC = { ⟨G, w⟩ | G é uma GLC que gera w } (pelo algoritmo CYK)
- V_GLC = { ⟨G⟩ | G é uma GLC e L(G) = ∅ }

### 9.7.2 O Problema da Parada

O **problema da parada** (*halting problem*) pergunta: "Dada uma Máquina de Turing M e uma entrada w, M para (aceita ou rejeita) quando executada sobre w?"

Formalmente, definimos a linguagem:

> HALT_MT = { ⟨M, w⟩ | M é uma MT e M para sobre a entrada w }

**Teorema 9.8.** O problema da parada é **indecidível**: não existe Máquina de Turing que decida HALT_MT.

> **Prova (esboço, por diagonalização).** Suponha, por contradição, que exista um decisor H para HALT_MT: H(⟨M, w⟩) aceita se M para sobre w, e rejeita caso contrário. Construímos uma nova MT D que, ao receber ⟨M⟩ como entrada:
>
> 1. Executa H(⟨M, ⟨M⟩⟩).
> 2. Se H aceita (ou seja, M para sobre ⟨M⟩), então D entra em laço infinito.
> 3. Se H rejeita (M não para sobre ⟨M⟩), então D para e aceita.
>
> Agora consideremos D executada sobre sua própria descrição ⟨D⟩:
>
> - Se D para sobre ⟨D⟩, então H(⟨D, ⟨D⟩⟩) aceita, e pela construção D entra em laço — **contradição**.
> - Se D não para sobre ⟨D⟩, então H(⟨D, ⟨D⟩⟩) rejeita, e pela construção D para — **contradição**.
>
> Em ambos os casos, chegamos a uma contradição. Portanto, o decisor H não pode existir, e HALT_MT é indecidível (Turing, 1936; Sipser, 2012).

### 9.7.3 Outros Problemas Indecidíveis

A indecidibilidade do problema da parada pode ser utilizada, por meio de **reduções**, para demonstrar a indecidibilidade de muitos outros problemas:

**Exemplo 9.9.** Problemas indecidíveis clássicos:

- **A_MT** = { ⟨M, w⟩ | M é uma MT que aceita w } — indecidível (embora Turing-reconhecível).
- **V_MT** = { ⟨M⟩ | M é uma MT e L(M) = ∅ } — indecidível (e nem mesmo Turing-reconhecível).
- **EQ_MT** = { ⟨M₁, M₂⟩ | L(M₁) = L(M₂) } — indecidível.
- **Equivalência de GLCs:** { ⟨G₁, G₂⟩ | G₁, G₂ são GLCs com L(G₁) = L(G₂) } — indecidível.
- **Ambiguidade de GLCs:** { ⟨G⟩ | G é uma GLC ambígua } — indecidível.

### 9.7.4 Reduções

**Definição 9.12.** Uma linguagem A é **redutível por mapeamento** (*mapping reducible*) a uma linguagem B, escrito A ≤ₘ B, se existe uma função computável f: Σ* → Σ* tal que, para toda cadeia w:

> w ∈ A ⟺ f(w) ∈ B

**Teorema 9.9.** Se A ≤ₘ B e B é decidível, então A é decidível. Equivalentemente, se A é indecidível e A ≤ₘ B, então B é indecidível.

A técnica de redução é a ferramenta principal para demonstrar a indecidibilidade de novos problemas: reduz-se um problema **sabidamente indecidível** (como HALT_MT) ao problema em questão. Intuitivamente, se podemos transformar qualquer instância de um problema indecidível A em uma instância equivalente de B, então B é "pelo menos tão difícil" quanto A e, portanto, também indecidível (Sipser, 2012).

> **Teorema 9.10 (Rice).** Toda propriedade não-trivial das linguagens recursivamente enumeráveis é indecidível. Formalmente, se P é uma propriedade de linguagens RE tal que P não é a propriedade vazia nem a propriedade universal (isto é, existem MTs M₁ e M₂ com L(M₁) ∈ P e L(M₂) ∉ P), então a linguagem { ⟨M⟩ | L(M) ∈ P } é indecidível.

O Teorema de Rice generaliza muitos dos resultados de indecidibilidade mencionados acima: saber se L(M) é vazia, finita, regular, livre de contexto, ou igual a Σ* são todas propriedades não-triviais das linguagens RE e, portanto, indecidíveis (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

---

## 9.8 Máquina de Turing Universal

### 9.8.1 Definição e Significado

**Definição 9.13.** Uma **Máquina de Turing Universal** (MTU) é uma Máquina de Turing U que, ao receber como entrada a codificação ⟨M⟩ de uma Máquina de Turing M e uma cadeia w, **simula** o comportamento de M sobre w:

> U(⟨M, w⟩) = M(w)

isto é, U aceita ⟨M, w⟩ se e somente se M aceita w; U rejeita se M rejeita; e U entra em laço se M entra em laço sobre w.

A existência da MTU foi demonstrada por Turing (1936) e constitui um dos resultados mais profundos da teoria da computação. A MTU mostra que é possível construir uma **única** máquina capaz de executar **qualquer** programa — bastando fornecer a descrição do programa como parte da entrada.

### 9.8.2 Codificação de Máquinas de Turing

Para que a MTU funcione, é necessário um esquema de **codificação** que represente qualquer MT como uma cadeia de símbolos. Uma codificação típica utiliza um alfabeto fixo (por exemplo, {0, 1}) e especifica:

1. Os estados Q = {q₁, q₂, …, qₙ}, codificados como 1, 11, 111, …;
2. Os símbolos de Γ, codificados de forma análoga;
3. A função de transição δ, codificada como uma lista de quíntuplas (estado, símbolo lido, símbolo escrito, direção, próximo estado), separadas por um delimitador.

A cadeia resultante ⟨M⟩ é a **descrição** de M. Todo detalhe da codificação pode variar, desde que seja fixa e computável — o poder da MTU não depende da codificação particular escolhida (Hopcroft, Ullman & Motwani, 2006).

### 9.8.3 Conexão com a Arquitetura de von Neumann

A Máquina de Turing Universal antecipa conceitualmente a **arquitetura de programa armazenado** (von Neumann, 1945), na qual um computador de propósito geral armazena tanto os **dados** quanto o **programa** na mesma memória. A analogia é direta:

| Máquina de Turing Universal | Computador de von Neumann |
|-----------------------------|---------------------------|
| Fita com ⟨M⟩ e w | Memória com programa e dados |
| Função de transição de U | Unidade de controle (CPU) |
| Simulação de M | Execução do programa |
| Codificação ⟨M⟩ | Código de máquina |

A MTU demonstra, no nível teórico, que a distinção entre **hardware** e **software** é dispensável: um único dispositivo fixo (a MTU) pode executar qualquer programa, desde que este seja fornecido como entrada. Essa ideia fundamental permeia toda a computação moderna (Davis, 1958; Sipser, 2012).

### 9.8.4 Enumeradores

Intimamente relacionado à MTU está o conceito de **enumerador**:

**Definição 9.14.** Um **enumerador** é uma Máquina de Turing com uma fita de saída auxiliar (chamada *impressora*). O enumerador pode escrever cadeias na fita de saída, separadas por um delimitador especial. A **linguagem enumerada** é o conjunto de todas as cadeias que eventualmente são escritas na fita de saída.

**Teorema 9.11.** Uma linguagem L é recursivamente enumerável se e somente se existe um enumerador que enumera L.

Esse resultado justifica o nome "recursivamente **enumerável**" e fornece uma caracterização alternativa da classe RE: uma linguagem é RE quando seus membros podem ser listados por um processo computacional, ainda que essa listagem possa ser infinita e fora de ordem (Sipser, 2012).

---

## 9.9 Relação com a Hierarquia de Chomsky

### 9.9.1 Tipo 0: Gramáticas Irrestritas e Máquinas de Turing

**Teorema 9.12.** Uma linguagem é recursivamente enumerável se e somente se é gerada por uma gramática irrestrita (Tipo 0 da Hierarquia de Chomsky).

> **Prova (esboço).** (⇒) Dada uma MT M que reconhece L, constrói-se uma gramática irrestrita G cujas regras simulam, em reverso, as transições de M: G gera w se e somente se M aceita w. (⇐) Dada uma gramática irrestrita G, constrói-se uma MT não-determinística que, a partir do símbolo inicial S, aplica produções de G de forma não-determinística e aceita se derivar a cadeia de entrada w (Hopcroft, Ullman & Motwani, 2006; Sipser, 2012).

### 9.9.2 Hierarquia Completa

A tabela a seguir resume a Hierarquia de Chomsky completa, integrando os conceitos desenvolvidos ao longo dos capítulos anteriores:

| Tipo | Gramática | Autômato | Classe de Linguagens | Capítulo |
|------|-----------|----------|---------------------|----------|
| 3 | Regular (A → aB, A → a) | Autômato Finito (AF) | Regulares | Cap. 3–5 |
| 2 | Livre de Contexto (A → α) | Autômato com Pilha (AP) | Livres de Contexto | Cap. 6–7 |
| 1 | Sensível ao Contexto (αAβ → αγβ) | Autômato Linearmente Limitado (ALL) | Sensíveis ao Contexto | Cap. 8 |
| 0 | Irrestrita (α → β) | Máquina de Turing (MT) | Recursivamente Enumeráveis | Cap. 9 |

As inclusões são estritas:

> Regulares ⊊ Livres de Contexto ⊊ Sensíveis ao Contexto ⊊ Recursivamente Enumeráveis

Cada nível da hierarquia introduz um mecanismo computacional adicional:

- **AF → AP:** adição de uma **pilha** (memória LIFO);
- **AP → ALL:** substituição da pilha por uma **fita limitada** ao comprimento da entrada;
- **ALL → MT:** remoção da limitação de espaço — a fita torna-se **infinita**.

### 9.9.3 Linguagens Recursivas na Hierarquia

As linguagens **recursivas** (decidíveis) ocupam uma posição intermediária entre as sensíveis ao contexto e as recursivamente enumeráveis:

> Regulares ⊊ Livres de Contexto ⊊ Sensíveis ao Contexto ⊆ Recursivas ⊊ RE

Toda linguagem sensível ao contexto é decidível (pois o autômato linearmente limitado sempre para), mas existem linguagens decidíveis que não são sensíveis ao contexto. A classe das linguagens recursivas é, portanto, estritamente maior que a classe das linguagens sensíveis ao contexto e estritamente menor que a classe das linguagens recursivamente enumeráveis (Sipser, 2012; Menezes, 2010).

### 9.9.4 Diagrama de Inclusões

A relação entre todas as classes de linguagens estudadas neste curso pode ser visualizada como uma sequência de conjuntos aninhados:

```
┌─────────────────────────────────────────────────────────────┐
│  Todas as linguagens (incontavelmente muitas)               │
│  ┌───────────────────────────────────────────────────────┐  │
│  │  Recursivamente Enumeráveis (RE) — Tipo 0             │  │
│  │  ┌─────────────────────────────────────────────────┐  │  │
│  │  │  Recursivas (Decidíveis)                        │  │  │
│  │  │  ┌───────────────────────────────────────────┐  │  │  │
│  │  │  │  Sensíveis ao Contexto — Tipo 1           │  │  │  │
│  │  │  │  ┌─────────────────────────────────────┐  │  │  │  │
│  │  │  │  │  Livres de Contexto — Tipo 2        │  │  │  │  │
│  │  │  │  │  ┌───────────────────────────────┐  │  │  │  │  │
│  │  │  │  │  │  Regulares — Tipo 3           │  │  │  │  │  │
│  │  │  │  │  └───────────────────────────────┘  │  │  │  │  │
│  │  │  │  └─────────────────────────────────────┘  │  │  │  │
│  │  │  └───────────────────────────────────────────┘  │  │  │
│  │  └─────────────────────────────────────────────────┘  │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

Cada fronteira neste diagrama representa uma **separação estrita**: existem linguagens em cada nível que não pertencem ao nível imediatamente inferior. O estudo dessas fronteiras — e dos mecanismos que permitem cruzá-las — é o tema central da teoria das linguagens formais e da computabilidade.

---

## 9.10 Exemplo em C

Uma implementação em linguagem C dos conceitos discutidos neste capítulo está disponível no diretório `src/09-maquina-turing/`:

- **Simulação de Máquina de Turing** — implementação de uma MT determinística com fita única que reconhece a linguagem L = { aⁿbⁿ | n ≥ 1 }

Consulte os arquivos-fonte e seus respectivos comentários para detalhes de implementação. Cada programa inclui exemplos de entrada que correspondem às máquinas e computações apresentadas nas seções anteriores, permitindo ao estudante verificar os resultados manualmente.

---

## Referências

CHURCH, A. An unsolvable problem of elementary number theory. **American Journal of Mathematics**, v. 58, n. 2, p. 345–363, 1936.

DAVIS, M. **Computability and Unsolvability**. New York: McGraw-Hill, 1958.

GÖDEL, K. Über formal unentscheidbare Sätze der Principia Mathematica und verwandter Systeme I. **Monatshefte für Mathematik und Physik**, v. 38, p. 173–198, 1931.

HILBERT, D.; ACKERMANN, W. **Grundzüge der theoretischen Logik**. Berlin: Springer, 1928.

HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. **Introdução à Teoria de Autômatos, Linguagens e Computação**. 2. ed. Rio de Janeiro: Elsevier, 2006.

MENEZES, P. B. **Linguagens Formais e Autômatos**. 6. ed. Porto Alegre: Bookman, 2010.

POST, E. L. Finite combinatory processes — formulation 1. **The Journal of Symbolic Logic**, v. 1, n. 3, p. 103–105, 1936.

SIPSER, M. **Introdução à Teoria da Computação**. 2. ed. São Paulo: Cengage Learning, 2012.

SUDKAMP, T. A. **Languages and Machines: An Introduction to the Theory of Computer Science**. 3. ed. Boston: Addison-Wesley, 2006.

TURING, A. M. On computable numbers, with an application to the Entscheidungsproblem. **Proceedings of the London Mathematical Society**, Series 2, v. 42, p. 230–265, 1936.

VON NEUMANN, J. **First Draft of a Report on the EDVAC**. Moore School of Electrical Engineering, University of Pennsylvania, 1945.
