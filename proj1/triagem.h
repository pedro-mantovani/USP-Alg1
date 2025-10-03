#ifndef TRIAGEM_H
    #define TRIAGEM_H

    #include <stdbool.h>
    #include "paciente.h"

    typedef struct fila_ FILA; // fila circular sequencial
    #define TAM 200 // quantidade máxima de pessoas na emergência

    FILA* FILA_criar(void);
    void FILA_apagar(FILA** fila);

    bool FILA_inserir(FILA* fila, PACIENTE* paciente);
    PACIENTE* FILA_remover(FILA* fila);

    bool FILA_vazia(FILA* fila);
    bool FILA_cheia(FILA* fila);
    int FILA_tamanho(FILA* fila);

    void FILA_print(FILA* fila);

#endif