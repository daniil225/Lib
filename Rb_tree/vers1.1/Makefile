

all: res

res: main.o Rb_Tree.o
	gcc -o res main.o Rb_Tree.o

main.o: main.c
	gcc -c main.c

Rb_Tree.o: Rb_Tree.c
	gcc -c Rb_Tree.c


clean:
	rm *.o res