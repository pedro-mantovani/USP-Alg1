#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "pilha.h"

struct paciente_ {
    int ID;
    bool vida; // true = vivo, false = morto
    PILHA* historico;
};

PACIENTE* PACIENTE_criar(int ID){
    PACIENTE* paciente = (PACIENTE*) malloc(sizeof(PACIENTE));
    if(paciente != NULL){
        paciente->ID = ID; // inicialização das variáveis
        paciente->vida = true; // paciente sempre inicia com vida
        paciente->historico = pilha_criar();
        return paciente;
    }
    return NULL;
}

bool PACIENTE_apagar(PACIENTE** paciente){
    if(paciente != NULL && *paciente != NULL){
        pilha_apagar(&(*paciente)->historico);
        free(*paciente);
        *paciente = NULL;
        return true;
    }
    return false;
}

void PACIENTE_imprimir(PACIENTE* paciente){
    if(paciente != NULL){
        printf("%d\n", paciente->ID);
    }
}

int PACIENTE_get_ID(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->ID;
    }
    return -1; // convenção de que IDs negativos são inválidos
}

bool PACIENTE_set_ID(PACIENTE* paciente, int ID){
    if(paciente != NULL){
        paciente->ID = ID;
        return true;
    }
    return false;
}

bool PACIENTE_set_vida(PACIENTE* paciente, bool vida){
    if(paciente != NULL){
        paciente->vida = vida;
        return true;
    }
    return false;
}