all:main.o sparse.o 
	gcc -o all main.o sparse.o
main.o:main.c sparse.c
	gcc -c main.c
sparse.o:main.c sparse.c
	gcc -c sparse.c
clean:
	rm -f* .o *~

