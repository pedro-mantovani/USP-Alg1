#ifndef HEAP_H
    #define HEAP_H

    #include <stdbool.h>
    #include "paciente.h"

    // Define o tamanho máximo da fila de espera 
    #define TAM_HEAP 1000

    typedef struct heap_ HEAP;

    // Cria a heap vazia 
    HEAP* HEAP_criar(void);

    // Apaga a estrutura da heap mas não apaga os pacientes
    void HEAP_apagar(HEAP** heap);

    // Insere paciente na fila de espera
    bool HEAP_inserir(HEAP* heap, PACIENTE* paciente);

    // Remove e retorna o paciente de maior prioridade e menor ordem de chegada (raiz da Heap)
    PACIENTE* HEAP_remover(HEAP* heap);

    // Imprime a fila de espera ordenada 
    void HEAP_imprimir(HEAP* heap);

    // Busca se um paciente já está na fila (para evitar duplicidade na espera)
    bool HEAP_busca_id(HEAP* heap, int id);

    // Verifica se está cheia
    bool HEAP_cheia(HEAP* heap);

    // Verifica se está vazia
    bool HEAP_vazia(HEAP* heap);

    // Retorna a quantidade total de pacientes (útil para o I/O)
    int HEAP_tamanho(HEAP* heap);

#endif