#include "hist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct historico_{
    char procedimento[101];
};

HIST* hist_criar(char proc[]){
    HIST* hist = (HIST*) malloc(sizeof(HIST));
    if(hist != NULL){
        strcpy(hist->procedimento, proc);
    }
    return hist;
}

bool hist_apagar(HIST **hist){
    if(hist != NULL && *hist != NULL){
        free(*hist);
        *hist = NULL;
        return true;
    }
    return false;
}

void hist_imprimir(HIST *hist){
    if(hist != NULL)
        printf("%s\n", hist->procedimento);
}


char *hist_get(HIST *hist) {
    if (hist != NULL)
        return hist->procedimento;
    return NULL;
}

bool hist_set(HIST *hist, char proc[]){
    if (hist != NULL){
        strcpy(hist->procedimento, proc);
        return (true);
    }
    return (false);
}