#include <stdio.h>
#include <stdlib.h>
#include "IO.h"
#include "paciente.h"
#include "triagem.h"
#include "relacaopacientes.h"
#include "pilha.h"
#include "hist.h"

bool SAVE(LISTA *lista, FILA *fila) {
    if(lista == NULL || fila == NULL) return false;

    // ----------------------- Salvando a fila -----------------------

    // Abre o arquivo (ou cria um caso não existir)
    FILE *fp_fila = fopen("fila.bin", "wb");
    if(fp_fila == NULL) return false;

    // Salva a quantidade de pacientes presentes na fila no primeiro int do fila.bin
    int fila_tamanho = FILA_tamanho(fila);
    fwrite(&fila_tamanho, sizeof(int), 1, fp_fila);

    // Loop guarda todos os IDs da fila em ordem
    for(int i = 0; i < fila_tamanho; i++){

        // Remove paciente da fila e pega o ID dele
        PACIENTE* p = FILA_remover(fila);
        int id = PACIENTE_get_ID(p);

        // Escreve o ID dele no arquivo
        fwrite(&id, sizeof(int), 1, fp_fila);
    }

    // fecha o arquivo
    fclose(fp_fila);


    // -------- Salvando a lista de pacientes + procedimentos --------

    // Abre o arquivo (ou cria um caso não existir)
    FILE *fp_lista = fopen("lista.bin", "wb");
    if (fp_lista == NULL) return false;

    // Salva a quantidade de pacientes registrados na lista no primeiro int do lista.bin
    int total_pacientes = LISTA_tamanho(lista);
    fwrite(&total_pacientes, sizeof(int), 1, fp_lista);

    // Loop guarda todos os IDs + procedimentos de cada ID da lista em ordem
    for(int i = 0; i < total_pacientes; i++){

        // Remve paciente da lista e pega o ID dele
        PACIENTE *p = LISTA_remover_inicio(lista);
        int id = PACIENTE_get_ID(p);

        // Escreve o ID dele no arquivo
        fwrite(&id, sizeof(int), 1, fp_lista);

        // Pega o histórico desse paciente e o tamanho
        PILHA* historico = PACIENTE_get_historico(p);
        int hist_tamanho = pilha_tamanho(historico);

        // Salva a quantidade de procedimentos desse paciente específico em um int logo a seguida de seu ID
        fwrite(&hist_tamanho, sizeof(int), 1, fp_lista);

        // Cria array temporario e faz um loop para nele salvar a pilha dos procedimentos do paciente na ordem topo->base, por meio da função desempilhar
        HIST* temp_procedimentos[hist_tamanho];
        for(int j = 0; j < hist_tamanho; j++){
            temp_procedimentos[j] = pilha_desempilhar(historico);
        }
        
        // Faz um loop invertido no array temporario para salvar os procedimentos na ordem base->topo 
        for(int j = hist_tamanho - 1; j >= 0; j--) {
            fwrite(hist_get(temp_procedimentos[j]), sizeof(char), 101, fp_lista);
        }

        // Apaga cada procedimento
        for(int j = 0; j < hist_tamanho; j++){
            hist_apagar(&temp_procedimentos[j]);
        }
        
        // Apaga o paciente
        PACIENTE_apagar(&p);
    }

    // Fecha o arquivo
    fclose(fp_lista);

    return true;
}



bool LOAD(LISTA **lista, FILA **fila){
    if(!*lista || !*fila) return false;

    FILE *fp_lista = fopen("lista.bin", "rb");

    // Tenta abrir a lista, pula o load se ela não existir
    if(fp_lista == NULL) return true;

    // Lê quantos pacientes tem no arquivo através do primeiro int (que armazena a quantidade)
    int total_pacientes;
    fread(&total_pacientes, sizeof(int), 1, fp_lista);

    // Cria a quantidade de pacientes dentro do programa
    for(int i = 0; i < total_pacientes; i++){

        // A cada iteração, lê o próximo ID do arquivo pra criar um paciente correspondente
        int id;
        fread(&id, sizeof(int), 1, fp_lista);
        PACIENTE* p = PACIENTE_criar(id);

        // Lê a quantidade de procedimentos do paciente da iteração tem
        int hist_tamanho;
        fread(&hist_tamanho, sizeof(int), 1, fp_lista);
        PILHA* historico = PACIENTE_get_historico(p);

        // Lê cada procedimento e adiciona ao histórico do paciente da iteração
        for(int j = 0; j < hist_tamanho; j++){
            char procedimento[101];
            fread(procedimento, sizeof(char), 101, fp_lista);
            HIST* h = hist_criar(procedimento);

            // Perceba que, como salvamos na ordem base->topo, empilharemos agora de baixo para cima, mantendo a estrutura original
            pilha_empilhar(historico, h);
        }
        LISTA_inserir(*lista, p);
    }
    fclose(fp_lista);

    // Refaz a fila de acordo com o .bin da fila (caso exista fila ativa)
    FILE *fp_fila = fopen("fila.bin", "rb");
    if(fp_fila != NULL){

        // Lê quantos IDs estão presentes na fila através do primeiro int (que armazena a quantidade)
        int fila_tamanho;
        fread(&fila_tamanho, sizeof(int), 1, fp_fila);

        // Busca por cada PACIENTE* na lista a partir do ID lido
        for(int i = 0; i < fila_tamanho; i++){
            int id;
            fread(&id, sizeof(int), 1, fp_fila);

            // Usa a função de busca para encontrar o paciente
            PACIENTE* paciente_existente = LISTA_busca(*lista, id);
            if(paciente_existente != NULL){

                // Adiciona paciente na fila se for encontrado
                FILA_inserir(*fila, paciente_existente);
            }
        }
        fclose(fp_fila);
    }

    return true;
}