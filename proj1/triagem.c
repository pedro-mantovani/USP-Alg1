#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "triagem.h"

struct fila_ {
    PACIENTE* paciente[TAM];
    int inicio;
    int fim;
    int tamanho;
};

FILA* FILA_criar(void){
    FILA* fila = (FILA*) calloc(1, sizeof(FILA)); // garantir que a inicialização não é lixo, evitando bugs potenciais
    if(fila != NULL){
        fila->inicio = 0;  // inicialização dos membros da struct
        fila->fim = 0;
        fila->tamanho = 0; 
        return fila;
    }
    return NULL;
}

void FILA_apagar(FILA** fila){
        if(fila != NULL && *fila != NULL){
            for(int i = 0; i < (*fila)->tamanho; i++){
                PACIENTE_apagar(&(*fila)->paciente[((*fila)->inicio + i) % TAM]);
            }
            free(*fila);
            *fila = NULL;
        }
}

bool FILA_inserir(FILA* fila, PACIENTE* paciente){
    if(fila != NULL && paciente != NULL && !FILA_cheia(fila)){
        fila->paciente[fila->fim] = paciente;
        fila->fim = (fila->fim + 1) % TAM;
        fila->tamanho++;
        return true;
    }
    return false;
}

PACIENTE* FILA_remover(FILA* fila){
    PACIENTE* p;
    if(fila != NULL && !FILA_vazia(fila)){
        p = fila->paciente[fila->inicio];
        fila->paciente[fila->inicio] = NULL;
        fila->inicio = (fila->inicio + 1) % TAM;
        fila->tamanho--;
        return p;
    }
    return NULL;
}

bool FILA_vazia(FILA* fila){
    return (fila != NULL && fila->tamanho == 0);
}

bool FILA_cheia(FILA* fila){
    return (fila != NULL && fila->tamanho == TAM);
}

void FILA_print(FILA* fila){
    if(fila != NULL && !FILA_vazia(fila)){
        for(int i = 0; i < fila->tamanho; i++){
            PACIENTE_imprimir(fila->paciente[(fila->inicio + i) % TAM]);
        }
    }
}