# Makefile para compilação dos exemplos de Linguagens Formais e Autômatos

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
BINDIR = bin

# Lista de executáveis
EXECUTABLES = \
	$(BINDIR)/conjuntos \
	$(BINDIR)/relacoes \
	$(BINDIR)/linguagens \
	$(BINDIR)/afd \
	$(BINDIR)/afnd \
	$(BINDIR)/regex_basico \
	$(BINDIR)/conversao_afnd_afd \
	$(BINDIR)/minimizacao \
	$(BINDIR)/automato_pilha \
	$(BINDIR)/arvore_derivacao

# Alvo padrão: compilar todos os executáveis
all: $(BINDIR) $(EXECUTABLES)

# Criação do diretório de saída
$(BINDIR):
	mkdir -p $(BINDIR)

# Conceitos Matemáticos
$(BINDIR)/conjuntos: src/01-conceitos-matematicos/conjuntos.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BINDIR)/relacoes: src/01-conceitos-matematicos/relacoes.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Alfabetos e Linguagens
$(BINDIR)/linguagens: src/02-alfabetos/linguagens.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Autômatos
$(BINDIR)/afd: src/03-automatos/afd.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BINDIR)/afnd: src/03-automatos/afnd.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Expressões Regulares
$(BINDIR)/regex_basico: src/04-regulares/regex_basico.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Minimização e Conversão
$(BINDIR)/conversao_afnd_afd: src/05-minimizacao/conversao_afnd_afd.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BINDIR)/minimizacao: src/05-minimizacao/minimizacao.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Gramáticas Livres de Contexto
$(BINDIR)/automato_pilha: src/06-livre-contexto/automato_pilha.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Derivação
$(BINDIR)/arvore_derivacao: src/07-derivacao/arvore_derivacao.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Compilar e executar todos os programas sequencialmente
run-all: all
	@for exe in $(EXECUTABLES); do \
		echo "========================================"; \
		echo "Executando: $$exe"; \
		echo "========================================"; \
		./$$exe; \
		echo ""; \
	done

# Limpeza: remover diretório de saída e todos os executáveis
clean:
	rm -rf $(BINDIR)

.PHONY: all clean run-all
