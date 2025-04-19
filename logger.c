#include <stdio.h>
#include "sync.h"

void atualizar_estado() {

    printf("╔═════════════ ESTADO DO SISTEMA ═════════════╗\n");

    // Escritor ativo
    if (estado.escritores_ativos > 0)
        printf("║ Escritor ativo        : [E%d]              ║\n", escritor_ativo_id);
    else
        printf("║ Escritor ativo        : (nenhum)           ║\n");

    // Leitores ativos
    printf("║ Leitores ativos       : ");
    if (estado.leitores_ativos == 0) {
        printf("(nenhum)");
    } else {
        for (int i = 0; i < idx_leitores_ativos; i++)
            printf("L%d ", leitores_ativos_ids[i]);
    }
    printf("\n");

    // Buffer
    printf("║ Buffer                : \"%s\"\n", estado.buffer);
    printf("║---------------------------------------------║\n");

    // Leitores esperando
    printf("║ Leitores esperando    : ");
    if (estado.leitores_esperando == 0) {
        printf("(nenhum)");
    } else {
        for (int i = 0; i < idx_leitores_esperando; i++)
            printf("L%d ", leitores_esperando_ids[i]);
    }
    printf("\n");

    // Escritores esperando
    printf("║ Escritores esperando  : ");
    if (estado.escritores_esperando == 0) {
        printf("(nenhum)");
    } else {
        for (int i = 0; i < idx_escritores_esperando; i++)
            printf("E%d ", escritores_esperando_ids[i]);
    }
    printf("\n");

    printf("╚══════════════════════════════════════════════╝\n");
    fflush(stdout);
}
