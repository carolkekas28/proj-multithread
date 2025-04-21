#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "sync.h"

// Protótipos
void* leitor(void* arg);
void* escritor(void* arg);

int main(int argc, char* argv[]) {
    srand(time(NULL));   // Inicializa gerador de números aleatórios
    init_sync();         // Inicializa estado compartilhado

    // Valores padrão
    int num_leitores = 5;
    int num_escritores = 2;

    // Argumentos da linha de comando
    if (argc >= 2) {
        num_leitores = atoi(argv[1]);
        if (num_leitores <= 0 || num_leitores > 10) {
            printf("Número de leitores inválido. Usando padrão: 5\n");
            num_leitores = 5;
        }
    }

    if (argc >= 3) {
        num_escritores = atoi(argv[2]);
        if (num_escritores <= 0 || num_escritores > 3) {
            printf("Número de escritores inválido. Usando padrão: 2\n");
            num_escritores = 2;
        }
    }

    // Alocação dinâmica
    pthread_t* leitores = malloc(num_leitores * sizeof(pthread_t));
    pthread_t* escritores = malloc(num_escritores * sizeof(pthread_t));

    // Criação das threads leitoras
    for (int i = 0; i < num_leitores; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&leitores[i], NULL, leitor, id);
    }

    // Criação das threads escritoras
    for (int i = 0; i < num_escritores; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&escritores[i], NULL, escritor, id);
    }

    // Simulação por tempo fixo
    sleep(30);

    printf("Execução encerrada.\n");

    free(leitores);
    free(escritores);

    exit(0);
}
