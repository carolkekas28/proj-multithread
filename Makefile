CC=gcc
CFLAGS=-Wall -pthread

all: leitores_escritores

leitores_escritores: main.c leitor.c escritor.c logger.c sync.c
	$(CC) $(CFLAGS) -o leitores_escritores main.c leitor.c escritor.c logger.c sync.c

clean:
	rm -f leitores_escritores
