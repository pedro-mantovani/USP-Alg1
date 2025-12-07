#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "paciente.h"
#include "heap.h"
#include "AVL.h"

bool SAVE(AVL* avl, HEAP* heap, int contador) {
    if (avl == NULL || heap == NULL) return false;

    // SALVANDO A AVL (REGISTROS) ##############################################################
   
    FILE* fp_reg = fopen("registros.bin", "wb");
    if(!fp_reg) return false;

    // Salva contador global e quantidade total de pacientes
    int total = AVL_tamanho(avl);
    fwrite(&contador, sizeof(int), 1, fp_reg);
    fwrite(&total, sizeof(int), 1, fp_reg);

    // Transforma AVL em vetor
    PACIENTE** lista_pacientes = NULL;
    if(total > 0) lista_pacientes = AVL_salvar(avl);

    // Loop para salvar cada paciente
    for(int i = 0; i < total; i++){
        PACIENTE* p = lista_pacientes[i];

        // Pega os dados do paciente
        int id = PACIENTE_get_ID(p);
        int prioridade = PACIENTE_get_prioridade(p);
        int chegada = PACIENTE_get_chegada(p);
        
        // Prepara pra salvar o nome
        char nome[81] = {0}; 
        const char* nome_raw = PACIENTE_get_nome(p);
        if(nome_raw != NULL) strcpy(nome, nome_raw); 

        // Salva os dados de cada paciente
        fwrite(&id, sizeof(int), 1, fp_reg);
        fwrite(nome, sizeof(char), 81, fp_reg);
        fwrite(&prioridade, sizeof(int), 1, fp_reg);
        fwrite(&chegada, sizeof(int), 1, fp_reg);
    }

    // libera o vetor auxiliar
    if(lista_pacientes != NULL) free(lista_pacientes); 
    fclose(fp_reg);


    // SALVANDO A HEAP (FILA) ##################################################################

    FILE* fp_fila = fopen("fila.bin", "wb");
    if(!fp_fila) return false;

    // Salva o tamanho da fila
    int tamanho_fila = HEAP_tamanho(heap);
    fwrite(&tamanho_fila, sizeof(int), 1, fp_fila);

    // Salva apenas os IDs da fila
    // Como o programa vai fechar mesmo, podemos já ir destruindo a heap pra pegar os itens
    while(!HEAP_vazia(heap)){
        PACIENTE* p = HEAP_remover(heap);
        if(p != NULL){
            int id = PACIENTE_get_ID(p);
            fwrite(&id, sizeof(int), 1, fp_fila);
        }
    }

    fclose(fp_fila);
    
    return true;
}



bool LOAD(AVL** avl, HEAP** heap, int* contador){
    if(*avl == NULL || *heap == NULL) return false;

    // CARREGA AVL ("registros.bin") ###########################################################

    FILE* fp_reg = fopen("registros.bin", "rb");
    
    // Se for NULL, so sai normalmente
    if(fp_reg == NULL) return true; 

    // Lê o contador global e o total de pacientes
    int total_pacientes = 0;
    fread(contador, sizeof(int), 1, fp_reg); // Lê o valor direto para a variável global da main
    fread(&total_pacientes, sizeof(int), 1, fp_reg);

    // Loop para criar cada paciente e inserir na AVL
    for(int i = 0; i < total_pacientes; i++){
        int id;
        char nome[81];
        int prioridade;
        int chegada;

        // Lê os dados na ordem que foram salvos (id, nome, prioridade, chegada)
        fread(&id, sizeof(int), 1, fp_reg);
        fread(nome, sizeof(char), 81, fp_reg);
        fread(&prioridade, sizeof(int), 1, fp_reg);
        fread(&chegada, sizeof(int), 1, fp_reg);

        // Cria o paciente
        PACIENTE* p = PACIENTE_criar(id, nome, prioridade, chegada);
        
        // Insere na AVL e ela se organiza sozinha
        if (p != NULL) AVL_inserir(*avl, p);
    }
    fclose(fp_reg);


    // CARREGA FILA DE ESPERA ("fila.bin") #####################################################

    FILE* fp_fila = fopen("fila.bin", "rb");
    
    // Se não existir arquivo de fila (mas existia de registro), segue em frente
    if(fp_fila != NULL){
        // Lê o tamanho da fila
        int tamanho_fila = 0;
        fread(&tamanho_fila, sizeof(int), 1, fp_fila);

        // Faz o loop com o tamanho da fila pra inserir todos os pacientes
        for(int i = 0; i < tamanho_fila; i++){
            int id_fila;
            fread(&id_fila, sizeof(int), 1, fp_fila);

            // Busca o paciente que já existe na AVL
            PACIENTE* p = AVL_buscar(*avl, id_fila);
            
            if(p != NULL){
                // Insere ele na Heap e ela se organiza automaticamente 
                HEAP_inserir(*heap, p);
            }
        }
        fclose(fp_fila);
    }

    return true;
}