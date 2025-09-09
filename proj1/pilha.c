#include "pilha.h"
#include "hist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 10
#define ERRO -1

typedef struct no_{
    HIST* hist;
    struct no_* anterior;
}NO;

struct pilha{
    NO* topo;
    int tamanho;
};

PILHA* pilha_criar(void){
    PILHA* pilha = (PILHA*) malloc(sizeof(PILHA));
    if(pilha != NULL){
        pilha -> topo = NULL;
        pilha -> tamanho = 0;
    }
    return pilha;
}

void pilha_apagar(PILHA **pilha){
    NO* aux;
    if(!pilha_vazia(*pilha)){
        while((*pilha)->topo != NULL){
            aux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            hist_apagar(&(aux->hist));
            aux->anterior = NULL;
            free(aux);
            aux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
}
    
bool pilha_vazia(PILHA *pilha){
    return (pilha == NULL || pilha->tamanho == 0);
}

bool pilha_cheia(PILHA *pilha){
    if(pilha != NULL){
        NO* teste = (NO*)malloc(sizeof(NO));
        if(pilha->tamanho != TAM_MAX && teste != NULL){
            free(teste);
            return false;
        }
    }
    return true;
}
    
int pilha_tamanho(PILHA *pilha){
    if(pilha != NULL){
        return pilha->tamanho;
    }
    return ERRO;
}
    
HIST *pilha_topo(PILHA *pilha){
    if(!pilha_vazia(pilha)){
        return pilha->topo->hist;
    }
    return NULL;
}

bool pilha_empilhar(PILHA* pilha, HIST* hist){
    if(!pilha_cheia(pilha)){
        NO *novo = (NO*) malloc(sizeof(NO));
        if(novo != NULL){
            novo->anterior = pilha->topo;
            novo->hist = hist;
            pilha->topo = novo;
            pilha->tamanho ++;
            return true;
        }
    }
    return false;
}


HIST *pilha_desempilhar(PILHA *pilha){
    if(!pilha_vazia(pilha)){
        HIST *ultimo = pilha->topo->hist;
        NO *temp = pilha->topo;
        pilha->topo = pilha->topo->anterior;
        temp->anterior = NULL;
        free(temp);
        temp = NULL;
        pilha->tamanho --;
        return ultimo;
    }
    return NULL;
}

void pilha_print(PILHA *pilha){
    if(!pilha_vazia(pilha)){
        NO* aux = pilha->topo;
        while(aux != NULL){
            hist_imprimir(aux->hist);
            aux = aux->anterior;
        }
    }
}