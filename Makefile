
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = dictionary
OBJS = dictionary.o ArvoreBinaria.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

dictionary.o: dictionary.c ArvoreBinaria.h
	$(CC) $(CFLAGS) -c dictionary.c

ArvoreBinaria.o: ArvoreBinaria.c ArvoreBinaria.h
	$(CC) $(CFLAGS) -c ArvoreBinaria.c

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean