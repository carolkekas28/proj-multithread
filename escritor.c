#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "sync.h"

void* escritor(void* arg) {
    int id = *(int*)arg;
    while(1) {
        entrar_escritor(id);
        snprintf(estado.buffer, MAX_BUFFER, "Escrito por escritor %d", id);
        printf("Escritor %d escreveu\n", id);
        sleep(1);
        sair_escritor(id);
        sleep(rand() % 3 + 1);
    }
}
