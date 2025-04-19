#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

#define MAX_BUFFER 100
#define MAX_THREADS 10

// Estado compartilhado
typedef struct {
    int leitores_ativos;
    int escritores_ativos;
    int leitores_esperando;
    int escritores_esperando;
    char buffer[MAX_BUFFER];
} Estado;

// Variáveis globais
extern Estado estado;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_leitor;
extern pthread_cond_t cond_escritor;

// Funções de controle
void init_sync();
void entrar_leitor(int id);
void sair_leitor(int id);
void entrar_escritor(int id);
void sair_escritor(int id);
void atualizar_estado();

#endif

#define MAX_IDS 10  

extern int leitores_ativos_ids[MAX_IDS];
extern int leitores_esperando_ids[MAX_IDS];
extern int escritores_esperando_ids[MAX_IDS];
extern int escritor_ativo_id;
extern int idx_leitores_ativos;
extern int idx_leitores_esperando;
extern int idx_escritores_esperando;

void registrar_leitor_ativo(int id);
void remover_leitor_ativo(int id);
void registrar_leitor_esperando(int id);
void remover_leitor_esperando(int id);
void registrar_escritor_esperando(int id);
void remover_escritor_esperando(int id);
void set_escritor_ativo(int id);
void limpar_escritor_ativo();