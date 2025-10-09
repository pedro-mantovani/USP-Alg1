#include <stdio.h> 
#include <stdlib.h>
#include "paciente.h"
#include "relacaopacientes.h"

//A relação de pacientes trata-se de uma lista encadeada (pois não tem limite de memória)
//A lista a ser implementada será uma lista encadeada circular com nó cabeça, para facilitar em procedimentos de busca e, consequentemente, de inserção e remoção 

typedef struct no_ NO;

struct no_ { //definição do tipo nó 
    PACIENTE *paciente;
    NO *proximo; 
}; 

struct lista_ {
    NO *sentinela; 
    NO* fim;
    int tamanho; 
};

LISTA *LISTA_criar(){
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA)); 
    if(lista){
        lista->sentinela = (NO*)malloc(sizeof(NO)); 
        if(!lista->sentinela){
            free (lista); 
            return NULL;
        }
        lista->sentinela->proximo = lista->sentinela;
        lista->fim = lista->sentinela; 
        lista->tamanho = 0;
        return lista;
    } else return NULL; 
}

bool LISTA_inserir(LISTA *lista, PACIENTE *paciente){
    if(lista){
        NO *novo = (NO*)malloc(sizeof(NO));

        if(!novo) return false;

        novo->paciente = paciente;  

        lista->fim->proximo = novo;
        novo->proximo = lista->sentinela;
        lista->fim = novo;

        lista->tamanho++; 
        return true;
    } else return false; 
}

PACIENTE *LISTA_remover(LISTA *lista, int id){
    if(lista && !LISTA_vazia(lista)){
        NO *p = lista->sentinela->proximo;
        NO *a = lista->sentinela;

        while(p != lista->sentinela && PACIENTE_get_ID(p->paciente) != id){
            a = p;
            p = p->proximo;
        }

        if(p == lista->sentinela) return NULL;

        PACIENTE *retornar = p->paciente;
        a->proximo = p->proximo;

        if(p == lista->fim) lista->fim = a;

        free(p);
        p = NULL;

        lista->tamanho--;
        return retornar;
    } else return NULL;
}

PACIENTE *LISTA_busca(LISTA *lista, int id){
    if(!lista || LISTA_vazia(lista)) return NULL;
    NO *p = lista->sentinela->proximo;
    while(p != lista->sentinela){
        if(PACIENTE_get_ID(p->paciente) == id){
            return p->paciente;  
        }
        p = p->proximo;
    } return NULL;  
}


PACIENTE *LISTA_remover_inicio(LISTA *lista){
    if(lista && !LISTA_vazia(lista)){
        NO *aux = lista->sentinela->proximo;
        lista->sentinela->proximo = aux->proximo; 
        PACIENTE *paciente = aux->paciente; 
        free (aux);
        aux = NULL; 
        lista->tamanho--;
        
        if(LISTA_vazia(lista)){
            lista->fim = lista->sentinela; 
        }

        return paciente; 
    } else return NULL; 
}

bool LISTA_apagar(LISTA **lista){
    if(*lista){
        while(!LISTA_vazia(*lista)){
            PACIENTE *paciente; 
            paciente = LISTA_remover_inicio(*lista); 
            PACIENTE_apagar(&paciente); 
        }
        free((*lista)->sentinela); 
        free(*lista); 
        *lista = NULL; 
        return true;
    } else return false; 
}

int LISTA_tamanho(LISTA *lista){
    if(lista){
        return lista->tamanho;
    } else return -1; //erro 
} 

bool LISTA_vazia(LISTA *lista){
    if(!lista) return true;
    else return (lista->tamanho == 0);
}

bool LISTA_cheia(LISTA *lista){
    if(!lista) return true;

    NO *teste = (NO*)malloc(sizeof(NO)); 
    
    if(!teste) return true;

    free(teste);
    return false;
}

void LISTA_imprimir(LISTA *lista){
    if(lista){
        NO *p = lista->sentinela->proximo;

        for(int i = 0; i < lista->tamanho; i++){
            printf("%d \n", PACIENTE_get_ID(p->paciente));
            p = p->proximo;
        } printf("\n"); 
    }
}

int LISTA_ID_fim(LISTA *lista){
    if(lista && !LISTA_vazia(lista)){
        int id = PACIENTE_get_ID(lista->fim->paciente); 
        return id;
    } else return -1; 
}