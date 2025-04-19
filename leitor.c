#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sync.h"

void* leitor(void* arg) {
    int id = *(int*)arg;
    while(1) {
        entrar_leitor(id);
        printf("Leitor %d leu: %s\n", id, estado.buffer);
        sleep(1);
        sair_leitor(id);
        sleep(rand() % 3);
    }
}
