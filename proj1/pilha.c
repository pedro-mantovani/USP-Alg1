#include "pilha.h"
#include "hist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
    HIST* hist;
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

void pilha_apagar(PILHA **pilha);
    
PILHA* pilha_inserir(HIST* hist);
    
bool pilha_vazia(PILHA *pilha);
    
bool pilha_cheia(PILHA *pilha);
    
int pilha_tamanho(PILHA *pilha);
    
HIST *pilha_topo(PILHA *pilha);

PILHA* pilha_empilhar(PILHA* pilha, HIST* hist){
    if(pilha != NULL){
        
    }
}

HIST *pilha_desempilhar(PILHA *pilha);

void pilha_print(PILHA *p);