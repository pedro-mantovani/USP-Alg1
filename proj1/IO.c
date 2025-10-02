#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if(!lista || !fila) 
        return false;
    
    PACIENTE *it; // Variável auxiliar 

    // Salvando os itens da lista

    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if(!fp_lista)
        return false;

    it = LISTA_remover_inicio(lista);
    int chave;
    while(it != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = PACIENTE_get_chave(it);
        fwrite(&chave, sizeof(int), 1, fp_lista);
        // Apaga o item removido
        PACIENTE_apagar(&it);
        // Atualiza a variável auxiliar
        it = LISTA_remover_inicio(lista);
    }
    // Libera memória
    LISTA_apagar(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if(!fp_fila)
        return false;

    it = FILA_remover(fila);
    while(it != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = PACIENTE_get_chave(it);
        fwrite(&chave, sizeof(int), 1, fp_fila);
        // Apaga o item removido
        PACIENTE_apagar(&it);
        // Atualiza a variável auxiliar
        it = FILA_remover(fila);
    }
    // Libera memória
    FILA_apagar(&fila);
    fclose(fp_fila); fp_fila = NULL;

    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if(!*lista || !*fila) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        PACIENTE *it = PACIENTE_criar(chave);
        LISTA_inserir(*lista, it);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        PACIENTE *it = PACIENTE_criar(chave);
        FILA_inserir(*fila, it);
    }
    fclose(fp_fila); // Libera memória

    return true;
}