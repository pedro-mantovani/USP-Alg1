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
    FILA* fila = (FILA*) malloc(sizeof(FILA));
    if(fila != NULL){

        // Inicialização dos membros da struct
        fila->inicio = 0;
        fila->fim = 0;
        fila->tamanho = 0; 
        return fila;
    }
    return NULL;
}

void FILA_apagar(FILA** fila){
        if(fila != NULL && *fila != NULL){
            free(*fila);
            *fila = NULL;
        }
        // OBS: a fila não pode apagar os pacientes da existência!! A LISTA_apagar que faz isso
}

bool FILA_inserir(FILA* fila, PACIENTE* paciente){
    if(fila != NULL && paciente != NULL && !FILA_cheia(fila)){

        // Insere no final de acordo com a lógica do "relógio"
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

        // Remove do início de acordo com a lógica do "relógio"
        p = fila->paciente[fila->inicio];
        fila->paciente[fila->inicio] = NULL;
        fila->inicio = (fila->inicio + 1) % TAM;
        fila->tamanho--;
        return p;
    }
    return NULL;
}

bool FILA_vazia(FILA* fila){
    return (fila == NULL || fila->tamanho == 0);
}

bool FILA_cheia(FILA* fila){
    return (fila != NULL && fila->tamanho == TAM);
}

int FILA_tamanho(FILA* fila){
    if (fila != NULL) {
        return fila->tamanho;
    }
    return -1;
}

void FILA_print(FILA* fila){
    if(fila != NULL && !FILA_vazia(fila)){
        for(int i = 0; i < fila->tamanho; i++){
            printf("%d° - ", i + 1);
            PACIENTE_imprimir(fila->paciente[(fila->inicio + i) % TAM]);
        }
    }
}

PACIENTE* FILA_busca(FILA* fila, int ID){
    if(fila != NULL){
        int n = fila->tamanho;
        int j = fila->inicio;

        for(int i = 0; i < n; i++){
            if(PACIENTE_get_ID(fila->paciente[j]) == ID) return fila->paciente[j];
            j = (j + 1) % TAM;
        }
    }
    return NULL;
}