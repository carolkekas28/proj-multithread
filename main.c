#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "sync.h"

void* leitor(void* arg);
void* escritor(void* arg);

int main() {
    srand(time(NULL)); 
    init_sync(); 

    pthread_t leitores[5], escritores[2];
    int ids_leitor[5] = {0, 1, 2, 3, 4};
    int ids_escritor[2] = {0, 1};

    for (int i = 0; i < 5; i++)
        pthread_create(&leitores[i], NULL, leitor, &ids_leitor[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&escritores[i], NULL, escritor, &ids_escritor[i]);

    sleep(15); 

    printf("Tempo de execução finalizado. Encerrando o programa...\n");

    exit(0); 
}
