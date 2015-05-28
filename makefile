SHELL=C:/Windows/System32/cmd.exe

all: compile

makedirs:
	if not exist "build" mkdir build
	if not exist bin mkdir bin

debug:
	makedirs
	flex reglas.l
	bison gramatica.y -d
	clang lex.yy.c -o build/lexer.o -c
	clang++ conjuntos -g main.cpp conjuntos.cpp automata.cpp funciones.cpp -Wl,build/lexer.o -o  bin/conjunto.exe


compile: makedirs
	flex reglas.l
	bison gramatica.y -d
	clang lex.yy.c -c -o build/lexer.o
	clang++ main.cpp htmlWriter.cpp -Wl,build/lexer.o -o  bin/pp.exe
    
run: all
	./conjuntos
	
debugrun:debug
	./conjuntos

clean:
	$(RM) conjuntos
	$(RM) lex.yy.c