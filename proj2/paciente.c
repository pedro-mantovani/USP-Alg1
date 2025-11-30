#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "AVL.h"
#include "heap.h"

struct paciente_ {
    int ID;
    char nome[81];
    int prioridade;
    int chegada;
};

PACIENTE* PACIENTE_criar(int ID, char nome[], int prioridade, int chegada){
    PACIENTE* paciente = (PACIENTE*) malloc(sizeof(PACIENTE));
    if(paciente != NULL){
        paciente->ID = ID; // Atribui ID
        strcpy(paciente->nome, nome); // atribui o nome
        paciente->prioridade = prioridade; // atribui prioridade
        paciente->chegada = chegada; // atribui ordem de chegada
        return paciente;
    }
    return NULL;
}

bool PACIENTE_apagar(PACIENTE** paciente){
    if(paciente != NULL && *paciente != NULL){
        free(*paciente);
        *paciente = NULL;
        return true;
    }
    return false;
}

void PACIENTE_imprimir(PACIENTE* paciente){
    if(paciente != NULL){
        printf("%s (ID: %d)\n", paciente->nome, paciente->ID);
    }
}

int PACIENTE_get_ID(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->ID;
    }
    return -1; // Convenção de que IDs negativos são inválidos
}

const char* PACIENTE_get_nome(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->nome;
    }
    return NULL;
}

int PACIENTE_get_prioridade(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->prioridade;
    }
    return -1;
}

int PACIENTE_get_chegada(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->chegada;
    }
    return -1;
}

bool PACIENTE_set_ID(PACIENTE* paciente, int ID){
    if(paciente != NULL){
        paciente->ID = ID;
        return true;
    }
    return false;
}

bool PACIENTE_set_nome(PACIENTE* paciente, char nome[]){
    if(paciente != NULL){
        strcpy(paciente->nome, nome);
        return true;
    }
    return false;
}

bool PACIENTE_set_prioridade(PACIENTE* paciente, int prioridade){
    if(paciente != NULL){
        paciente->prioridade = prioridade;
        return true;
    }
    return false;
}

bool PACIENTE_set_chegada(PACIENTE* paciente, int chegada){
    if(paciente != NULL){
        paciente->chegada = chegada;
        return true;
    }
    return false;
}