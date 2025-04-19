#include <pthread.h>
#include <stdio.h>
#include "sync.h"

// Estado global
Estado estado;
pthread_mutex_t mutex;
pthread_cond_t cond_leitor;
pthread_cond_t cond_escritor;

int leitores_ativos_ids[MAX_THREADS];
int leitores_esperando_ids[MAX_THREADS];
int escritores_esperando_ids[MAX_THREADS];
int escritor_ativo_id = -1;
int idx_leitores_ativos = 0;
int idx_leitores_esperando = 0;
int idx_escritores_esperando = 0;

void init_sync() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_leitor, NULL);
    pthread_cond_init(&cond_escritor, NULL);
    estado = (Estado){0, 0, 0, 0, ""};
}

void entrar_leitor(int id) {
    pthread_mutex_lock(&mutex);
    registrar_leitor_esperando(id);
    estado.leitores_esperando++;
    while (estado.escritores_ativos > 0)
        pthread_cond_wait(&cond_leitor, &mutex);
    estado.leitores_esperando--;
    remover_leitor_esperando(id);
    estado.leitores_ativos++;
    registrar_leitor_ativo(id);
    atualizar_estado();
    pthread_mutex_unlock(&mutex);
}

void sair_leitor(int id) {
    pthread_mutex_lock(&mutex);
    estado.leitores_ativos--;
    remover_leitor_ativo(id);
    if (estado.leitores_ativos == 0)
        pthread_cond_signal(&cond_escritor);  // só acorda escritor quando o último leitor sair
    atualizar_estado();
    pthread_mutex_unlock(&mutex);
}

void entrar_escritor(int id) {
    pthread_mutex_lock(&mutex);
    registrar_escritor_esperando(id);
    estado.escritores_esperando++;
    while (estado.leitores_ativos > 0 || estado.escritores_ativos > 0)
        pthread_cond_wait(&cond_escritor, &mutex);
    estado.escritores_esperando--;
    remover_escritor_esperando(id);
    estado.escritores_ativos++;
    set_escritor_ativo(id);
    atualizar_estado();
    pthread_mutex_unlock(&mutex);
}

void sair_escritor(int id) {
    pthread_mutex_lock(&mutex);
    estado.escritores_ativos--;
    limpar_escritor_ativo();

    if (estado.escritores_esperando > 0)
        pthread_cond_signal(&cond_escritor);
    else
        pthread_cond_broadcast(&cond_leitor);

    atualizar_estado();
    pthread_mutex_unlock(&mutex);
}


void registrar_leitor_ativo(int id) {
    leitores_ativos_ids[idx_leitores_ativos++] = id;
}

void remover_leitor_ativo(int id) {
    for (int i = 0; i < idx_leitores_ativos; i++) {
        if (leitores_ativos_ids[i] == id) {
            for (int j = i; j < idx_leitores_ativos - 1; j++)
                leitores_ativos_ids[j] = leitores_ativos_ids[j + 1];
            idx_leitores_ativos--;
            break;
        }
    }
}

void registrar_leitor_esperando(int id) {
    leitores_esperando_ids[idx_leitores_esperando++] = id;
}

void remover_leitor_esperando(int id) {
    for (int i = 0; i < idx_leitores_esperando; i++) {
        if (leitores_esperando_ids[i] == id) {
            for (int j = i; j < idx_leitores_esperando - 1; j++)
                leitores_esperando_ids[j] = leitores_esperando_ids[j + 1];
            idx_leitores_esperando--;
            break;
        }
    }
}

void registrar_escritor_esperando(int id) {
    escritores_esperando_ids[idx_escritores_esperando++] = id;
}

void remover_escritor_esperando(int id) {
    for (int i = 0; i < idx_escritores_esperando; i++) {
        if (escritores_esperando_ids[i] == id) {
            for (int j = i; j < idx_escritores_esperando - 1; j++)
                escritores_esperando_ids[j] = escritores_esperando_ids[j + 1];
            idx_escritores_esperando--;
            break;
        }
    }
}

void set_escritor_ativo(int id) {
    escritor_ativo_id = id;
}

void limpar_escritor_ativo() {
    escritor_ativo_id = -1;
}