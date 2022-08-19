output: main.o heap.o heapify.o 
	gcc main.o heap.o heapify.o -o output

main.o: main.c heap.c heap.h heapify.c heapify.h
	gcc -c main.c heap.c heapify.c

heap.o: heap.c heap.h heapify.c heapify.h 
	gcc -c heap.c heapify.c

heapify.o: heapify.c heapify.h 
	gcc -c heapify.c

clean: 
	rm *.o