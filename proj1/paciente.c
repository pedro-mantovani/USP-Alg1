#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "pilha.h"

struct paciente_ {
    int ID;
    char nome[81];
    bool vida; // True = vivo, false = morto
    PILHA* historico; // Armazena os procedimentos do histórico médico
};

PACIENTE* PACIENTE_criar(int ID, char nome[]){
    PACIENTE* paciente = (PACIENTE*) malloc(sizeof(PACIENTE));
    if(paciente != NULL){
        paciente->ID = ID; // Atribui ID
        strcpy(paciente->nome, nome); // atribui o nome
        paciente->vida = true; // Paciente sempre inicia com vida
        paciente->historico = pilha_criar(); // Cria histórico de procedimentos
        return paciente;
    }
    return NULL;
}

bool PACIENTE_apagar(PACIENTE** paciente){
    if(paciente != NULL && *paciente != NULL){
        pilha_apagar(&(*paciente)->historico); // apaga histórico
        free(*paciente);
        *paciente = NULL;
        return true;
    }
    return false;
}

void PACIENTE_imprimir(PACIENTE* paciente){
    if(paciente != NULL){
        printf("Nome: %s\n", paciente->nome);
        printf("ID: %d\n", paciente->ID);
    }
}

PILHA* PACIENTE_get_historico(PACIENTE* paciente){
    if(paciente != NULL){
        return paciente->historico;
    }
    return NULL;
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

bool PACIENTE_set_nome(PACIENTE* paciente, char nome[]){
    if(paciente != NULL){
        strcpy(paciente->nome, nome);
        return true;
    }
    return false;
}