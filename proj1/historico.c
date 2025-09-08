#include "pilha.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
    ITEM* item;
    NO* anterior;
}NO;

struct pilha{
    NO* topo;
    int tamanho;
};

PILHA* pilha_criar(void){
    PILHA* temp = (PILHA*) malloc(sizeof(PILHA));
    if(temp != NULL){
        temp -> topo = NULL;
        temp -> tamanho = 0;
    }
    return temp;
}

PILHA* pilha_empilhar(PILHA* pilha, ITEM* item){
    if(pilha != NULL){
        
    }
}


