#include "hist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
O TAD histórico será usado pelo TAD pilha para formar o histórico de um paciente
Ele nada mais é que um tad que armazena um procedimento (string de 100 caracteres)
*/

struct historico_{
    char procedimento[101]; // 100 caracteres + \n
};

HIST* hist_criar(char proc[]){
    HIST* hist = (HIST*) calloc(1, sizeof(HIST)); // Aloca espaço para o histórico
    if(hist != NULL){
        strcpy(hist->procedimento, proc); // Copia o procedimento para o campo da struct
    }
    return hist; // Devolve o ponteiro para hist
}

bool hist_apagar(HIST **hist){
    if(hist != NULL && *hist != NULL){ // Verifica se o histórico existe
        free(*hist); // Desaloca a memória
        *hist = NULL; // Faz ele apontar para NULL evitando acessos indevidos
        return true;
    }
    return false;
}

void hist_imprimir(HIST *hist){
    if(hist != NULL)
        printf("%s\n", hist->procedimento); // Imprime o procedimento
}


char *hist_get(HIST *hist) {
    if (hist != NULL)
        return hist->procedimento; // Retorna a string que contém o procedimento
    return NULL;
}

bool hist_set(HIST *hist, char proc[]){
    if (hist != NULL){
        strcpy(hist->procedimento, proc); // Altera o valor atual do procedimento para a string dada
        return (true);
    }
    return (false);
}