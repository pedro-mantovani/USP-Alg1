#ifndef HEAP_H
    #define HEAP_H

    #include <stdbool.h>
    #include "paciente.h"

    // define o tamanho máximo da fila de espera 
    // sei la o rudinei colocou tamanho no slide dele e no projeto 1 a fila tinha limite
    // e segundo o gemini é dificil trabalhar em heap dinamica com realloc
    // mas nao sei se ele vai implicar com eficiencia, decidam ai o que fazer kk
    // tipo, talvez fique super ineficiente quando tiver que imprimir a heap ja que duplica ela
    #define TAM_HEAP 1000

    typedef struct heap_ HEAP;

    // cria a heap vazia (acho que min heap deve ser o caminho, com o 1 no topo/raiz)
    HEAP* HEAP_criar(void);

    // apaga a estrutura da heap (mas nao pode apagar os pacientes, isso é pra AVL fazer)
    void HEAP_apagar(HEAP** heap);

    // insere paciente na fila de espera
    // a Heap tem que organizar automaticamente baseada PRIMEIRO em Prioridade (1 < 5) e se tiver empatado, em ordem de chegada (1 < 2)
    bool HEAP_inserir(HEAP* heap, PACIENTE* paciente);

    // remove e retorna o paciente de maior prioridade e menor ordem de chegada (raiz da Heap)
    PACIENTE* HEAP_remover(HEAP* heap);

    // olha quem é o próximo sem remover (gemini colocou isso, nao sei se é útil)
    PACIENTE* HEAP_topo(HEAP* heap);

    // imprime a fila de espera ordenada (da maior prioridade para menor)
    // atenção segundo o gemini: implementação deve fazer uma cópia da heap para não destruir a original (ja que é feita usando tira do topo -> reorganiza -> tira do topo -> reorganiza...)
    void HEAP_imprimir(HEAP* heap);

    // busca se um paciente já está na fila (para evitar duplicidade na espera)
    // nota segundo o gemini: busca em Heap é O(n), infelizmente, pois não é ordenada por ID
    bool HEAP_busca_id(HEAP* heap, int id);

    // utilitários
    bool HEAP_cheia(HEAP* heap);
    bool HEAP_vazia(HEAP* heap);
    int HEAP_tamanho(HEAP* heap);

#endif