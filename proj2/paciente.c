#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "AVL.h"
#include "heap.h"
#include "pilha.h"
#include "hist.h"

struct paciente_ {
    int ID;
    char nome[81];
    int prioridade;
    int chegada;
    PILHA* historico;
};

PACIENTE* PACIENTE_criar(int ID, char nome[], int prioridade, int chegada){
    PACIENTE* paciente = (PACIENTE*) malloc(sizeof(PACIENTE));
    if(paciente != NULL){
        paciente->ID = ID; // Atribui ID
        strcpy(paciente->nome, nome); // atribui o nome
        paciente->prioridade = prioridade; // atribui prioridade
        paciente->chegada = chegada; // atribui ordem de chegada
        paciente->historico = pilha_criar(); // cria o histórico
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

// Função para imprimir os dados de um paciente (imprime o nome completo)
void PACIENTE_imprimir_completo(PACIENTE* paciente){
    if(paciente != NULL){
        printf ("%s (ID: %04d) || Status: ", paciente->nome, paciente->ID);
        int prioridade = paciente->prioridade;
        switch(prioridade){
            case -1: printf("Não presente no hospital\n"); break;
            case 1: printf("Emergência\n"); break;
            case 2: printf("Muito urgente\n"); break;
            case 3: printf("Urgente\n"); break;
            case 4: printf("Pouco urgente\n"); break;
            case 5: printf("Não urgente\n"); break;
        }
        pilha_print(paciente->historico);
    }
}

// Função para imprimir os dados do paciente (imprime no máximo 20 caracteres do nome)
void PACIENTE_imprimir_resumido(PACIENTE* paciente){
    if(paciente != NULL){
        int len = strlen(paciente->nome);
        
        if(len > 20){
            printf("%.17s... (ID: %04d) || Status: ", paciente->nome, paciente->ID);
        }
        else{
            printf("%-20s (ID: %04d) || Status: ", paciente->nome, paciente->ID);
        }

        int prioridade = paciente->prioridade;
        switch(prioridade){
            case -1: printf("Não presente no hospital\n"); break;
            case 1: printf("Emergência\n"); break;
            case 2: printf("Muito urgente\n"); break;
            case 3: printf("Urgente\n"); break;
            case 4: printf("Pouco urgente\n"); break;
            case 5: printf("Não urgente\n"); break;
        }
        pilha_print(paciente->historico);
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