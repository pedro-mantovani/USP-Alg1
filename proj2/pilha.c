#include "pilha.h"
#include "hist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 10
#define ERRO -1

/*
TAD para uma pilha genérica que utiliza o tad histórico
*/


// Define um nó como sendo um procedimento (item + ponteiro para item anterior)
typedef struct no_{
    HIST* hist;
    struct no_* anterior;
}NO;

// Define a pilha como um nó para o topo e seu tamanho
struct pilha{
    NO* topo;
    int tamanho;
};

PILHA* pilha_criar(void){
    PILHA* pilha = (PILHA*) malloc(sizeof(PILHA)); // Aloca o espaço para a pilha
    if(pilha != NULL){ // Verifica se foi bem sucedido
        pilha -> topo = NULL; // Inicializa os valores
        pilha -> tamanho = 0;
    }
    return pilha;
}

void pilha_apagar(PILHA **pilha){
    NO* aux;
    if(!pilha_vazia(*pilha)){
        while((*pilha)->topo != NULL){ // Percorre todos os nós apagando-os
            aux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            hist_apagar(&(aux->hist));
            aux->anterior = NULL;
            free(aux);
            aux = NULL;
        }
    }
    free(*pilha); // Libera a própria pilha
    *pilha = NULL; // Faz o ponteiro do usuário apontar para NULL evitando acesso indevido
}
    
bool pilha_vazia(PILHA *pilha){
    return (pilha == NULL || pilha->tamanho == 0); // Verifica se a pilha existe ou tem tamanho zero
}

bool pilha_cheia(PILHA *pilha){
    if(pilha != NULL){
        NO* teste = (NO*)malloc(sizeof(NO)); // Verifica se há espaço na memória
        if(pilha->tamanho != TAM_MAX && teste != NULL){ // Verifica se ultrapassou o tamanho máximo escolhido (10)
            free(teste); // Libera o ponteiro de teste alocado
            return false;
        }
    }
    return true;
}
    
int pilha_tamanho(PILHA *pilha){
    if(pilha != NULL){ // Verifica se a pilha existe
        return pilha->tamanho; // Retorna o tamanho da pilha
    }
    return ERRO;
}
    
HIST *pilha_topo(PILHA *pilha){
    if(!pilha_vazia(pilha)){
        return pilha->topo->hist; // retorna qual o procedimento do topo da pilha (não apaga, diferente do desempilhar)
    }
    return NULL;
}

bool pilha_empilhar(PILHA* pilha, HIST* hist){
    if(!pilha_cheia(pilha)){ // Verifica se a pilha não está cheia
        NO *novo = (NO*) malloc(sizeof(NO)); // Aloca um nó
        if(novo != NULL){ // Verifica se foi possível alocar o nó
            novo->anterior = pilha->topo; // Faz o novo nó apontar para o topo
            novo->hist = hist; // Faz o novo nó apontar para o procedimento dado pelo usuário
            pilha->topo = novo; // Altera o topo da pilha
            pilha->tamanho ++; // Aumenta o tamanho da pilha
            return true;
        }
    }
    return false;
}


HIST *pilha_desempilhar(PILHA *pilha){
    if(!pilha_vazia(pilha)){ // Verifica se a pilha não está vazia
        HIST *ultimo = pilha->topo->hist; // Salva o último procedimento
        NO *temp = pilha->topo; // Salva o ponteiro do topo
        pilha->topo = pilha->topo->anterior; // Altera o topo
        temp->anterior = NULL; // Corta a ligação do antigo topo com o restante da pilha
        free(temp); // Libera a memória do antigo topo
        temp = NULL; // Impede que o antigo topo seja acessado indevidamente
        pilha->tamanho --; // Diminui o tamanho da pilha
        return ultimo; // Devolve para o usuário o procedimento que estava no topo
    }
    return NULL;
}

void pilha_print(PILHA *pilha){
    if(!pilha_vazia(pilha)){ // Verifica se a pilha não está vazia/existe
        NO* aux = pilha->topo; // Cria um vetor auxiliar para percorrer todos os elementos
        printf("   Histórico:\n");
        while(aux != NULL){
            char* procedimento = hist_get(aux->hist); // Pega o elemento
            if(procedimento != NULL) printf("   └-> %s\n", procedimento); // Imprime o elemento
            aux = aux->anterior; // Passa para o próximo
        }
    }else{
        printf("   (Nenhum procedimento registrado)\n");
    }
    printf("\n");
}