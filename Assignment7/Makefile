CC=gcc
TARGET=main 

all: try run
try: main.o FO.o
	$(CC) main.o FO.o -o $(TARGET)
main.o: main.c FO.h
	$(CC) -c main.c
FO.o: FO.h FO.c
	$(CC) -c FO.c
run: $(TARGET)
	./$(TARGET) data
clean:
	rm -rvf *.o $(TARGET)

