CC=gcc
TARGET=p-counter
all:
	$(CC) main.c -Wall -o $(TARGET)
clean:
	rm $(TARGET)