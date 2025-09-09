#ifndef PILHA_H
    #define PILHA_H

    #include <stdbool.h>

    typedef struct pilha PILHA;

    PILHA* pilha_criar(void);
    void pilha_apagar(PILHA **pilha);
    bool pilha_vazia(PILHA *pilha);
    bool pilha_cheia(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    HIST *pilha_topo(PILHA *pilha);
    bool pilha_empilhar(PILHA *pilha, HIST *hist);
    HIST *pilha_desempilhar(PILHA *pilha);
    void pilha_print(PILHA *p);

#endif