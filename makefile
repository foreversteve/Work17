all: writing.o control.o
	gcc -o writing writing.o
	gcc -o control control.o
writing.o: writing.c game.h
	gcc -c writing.c game.h
control.o: writing.c game.h
	gcc -c control.c game.h
