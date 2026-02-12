# Linguagens Formais e Autômatos

Material acadêmico sobre **Linguagens Formais e Autômatos**, disciplina fundamental dos cursos de Ciência da Computação. O repositório reúne notas de aula, resumos teóricos e exemplos práticos implementados em linguagem C.

## Sobre o Conteúdo

O conteúdo abrange a teoria clássica de linguagens formais e autômatos, fundamentado nas obras de referência da área:

- **Hopcroft, Ullman e Motwani** — *Introduction to Automata Theory, Languages, and Computation*
- **Sipser** — *Introduction to the Theory of Computation*
- **Menezes** — *Linguagens Formais e Autômatos*
- **Sudkamp** — *Languages and Machines*

Os tópicos cobrem desde os conceitos matemáticos preliminares até gramáticas livres de contexto e autômatos com pilha, passando por autômatos finitos, linguagens regulares e propriedades de fechamento.

## Sumário

1. [Conceitos Matemáticos para Linguagens Formais](docs/01-conceitos-matematicos.md)
2. [Alfabetos, Palavras, Linguagens, Gramáticas e Hierarquia de Linguagens](docs/02-alfabetos-palavras-linguagens.md)
3. [Autômato Finito Determinístico e Não Determinístico](docs/03-automatos-finitos.md)
4. [Linguagens Regulares, Expressões Regulares e Gramática Regular](docs/04-linguagens-regulares.md)
5. [Minimização de Autômato, Lema do Bombeamento e Conversão de AFND para AFD](docs/05-minimizacao-bombeamento-conversao.md)
6. [Gramática Livre de Contexto e Autômato com Pilha](docs/06-gramatica-livre-contexto.md)
7. [Árvore de Derivação e Ambiguidade](docs/07-arvore-derivacao-ambiguidade.md)

## Exemplos em C

Cada tópico possui exemplos práticos implementados em linguagem C, disponíveis no diretório `src/`. Os códigos ilustram os conceitos teóricos apresentados nas notas de aula, como simulação de autômatos finitos, verificação de expressões regulares e análise de gramáticas.

## Como Compilar

O projeto utiliza um `Makefile` para compilação. Para compilar todos os exemplos:

```bash
make all
```

Para limpar os arquivos gerados:

```bash
make clean
```

## Referências Bibliográficas

- HOPCROFT, J. E.; ULLMAN, J. D.; MOTWANI, R. *Introduction to Automata Theory, Languages, and Computation*. 3rd ed. Pearson, 2006.
- SIPSER, M. *Introduction to the Theory of Computation*. 3rd ed. Cengage Learning, 2012.
- MENEZES, P. B. *Linguagens Formais e Autômatos*. 6ª ed. Bookman, 2011.
- SUDKAMP, T. A. *Languages and Machines*. 3rd ed. Addison-Wesley, 2005.
- LEWIS, H. R.; PAPADIMITRIOU, C. H. *Elements of the Theory of Computation*. 2nd ed. Prentice Hall, 1997.

## Licença

Este projeto está licenciado sob a [Apache License 2.0](LICENSE).
