#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "paciente.h"
#include "heap.h"
#include "AVL.h"
#include "pilha.h"

// Função para salvar os dados do sistema
bool SAVE(AVL* avl, HEAP* heap, int contador) {

    // Verifica se a avl e a heap existem
    if (avl == NULL || heap == NULL) return false;

    // cria ou abre o arquivo registros
    FILE* fp_reg = fopen("registros.bin", "wb");
    if(!fp_reg) return false;

    // Salva o contador e quantidade total de pacientes
    int total = AVL_tamanho(avl);
    fwrite(&contador, sizeof(int), 1, fp_reg);
    fwrite(&total, sizeof(int), 1, fp_reg);

    // Transforma AVL em vetor para iterar linearmente
    PACIENTE** lista_pacientes = NULL;
    if(total > 0) lista_pacientes = AVL_salvar(avl);

    // Loop para salvar cada paciente
    for(int i = 0; i < total; i++){
        PACIENTE* p = lista_pacientes[i];

        // Pega os dados básicos do paciente
        int id = PACIENTE_get_ID(p);
        int prioridade = PACIENTE_get_prioridade(p);
        int chegada = PACIENTE_get_chegada(p);
        
        // Prepara pra salvar o nome (garante array limpo para caso de nomes menores)
        char nome[81] = {0}; 
        const char* nome_raw = PACIENTE_get_nome(p);
        if(nome_raw != NULL) strncpy(nome, nome_raw, 80); 

        // Escreve os dados básicos
        fwrite(&id, sizeof(int), 1, fp_reg);
        fwrite(nome, sizeof(char), 81, fp_reg);
        fwrite(&prioridade, sizeof(int), 1, fp_reg);
        fwrite(&chegada, sizeof(int), 1, fp_reg);

        // Pega o histórico
        PILHA* historico = PACIENTE_get_historico(p);
        int hist_tamanho = pilha_tamanho(historico);

        // Salva o tamanho do histórico
        fwrite(&hist_tamanho, sizeof(int), 1, fp_reg);

        if (hist_tamanho > 0) {

            // Cria um vetor temporário para armazenar os ponteiros do histórico
            // Não é necessário malloc pois o máximo é de 10 procedimentos (pequeno)
            HIST* temp_procedimentos[hist_tamanho];

            // 1. Desempilha tudo para o vetor temporário para poder ler
            // O topo da pilha vai para o índice 0 do vetor
            for(int j = 0; j < hist_tamanho; j++){
                temp_procedimentos[j] = pilha_desempilhar(historico);
            }
            
            // 2. Salva no arquivo na ordem cronológica (Base -> Topo)
            // Isso facilita o carregamento (LOAD) depois
            for(int j = hist_tamanho - 1; j >= 0; j--) {
                char* proc_texto = hist_get(temp_procedimentos[j]);
                // Garante que escreve algo válido mesmo se for NULL
                if (proc_texto) 
                    fwrite(proc_texto, sizeof(char), 101, fp_reg);
                else 
                    fwrite("", sizeof(char), 101, fp_reg); 
            }

            // 3. Reempilha os itens de volta no paciente!
            // Isso permite que a main ainda faça operações com o histórico e evita double free
            // A ordem de empilhar deve ser do Fundo para o Topo, para restaurar a ordem original.
            for(int j = hist_tamanho - 1; j >= 0; j--){
                pilha_empilhar(historico, temp_procedimentos[j]);
            }
        }
    }

    // Libera apenas o vetor auxiliar de ponteiros criado pelo AVL_salvar
    // Os pacientes em si continuam vivos na memória apontados pela AVL
    if(lista_pacientes != NULL) free(lista_pacientes); 
    fclose(fp_reg);

    // Salvando a Heap

    // Cira o arquivo fila
    FILE* fp_fila = fopen("fila.bin", "wb");
    if(!fp_fila) return false;

    // Salva o tamanho da fila
    int tamanho_fila = HEAP_tamanho(heap);
    fwrite(&tamanho_fila, sizeof(int), 1, fp_fila);

    // Salva apenas os IDs da fila
    // Aqui consumimos a estrutura da Heap (destrutivo para a heap, seguro para os pacientes)
    // Isso é aceitável pois o programa está encerrando.
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

// Função para carregar os dados nas estruturas auxiliares
bool LOAD(AVL** avl, HEAP** heap, int* contador){
    if(*avl == NULL || *heap == NULL) return false;

    // CARREGA AVL ("registros.bin")

    FILE* fp_reg = fopen("registros.bin", "rb");
    
    // Se arquivo não existe, apenas retorna true (primeira execução)
    if(fp_reg == NULL) return true; 

    // Lê o contador global e o total de pacientes
    int total_pacientes = 0;
    if (fread(contador, sizeof(int), 1, fp_reg) != 1) { fclose(fp_reg); return false; }
    if (fread(&total_pacientes, sizeof(int), 1, fp_reg) != 1) { fclose(fp_reg); return false; }

    // Loop para recriar cada paciente
    for(int i = 0; i < total_pacientes; i++){
        int id;
        char nome[81];
        int prioridade;
        int chegada;

        fread(&id, sizeof(int), 1, fp_reg);
        fread(nome, sizeof(char), 81, fp_reg);
        fread(&prioridade, sizeof(int), 1, fp_reg);
        fread(&chegada, sizeof(int), 1, fp_reg);

        PACIENTE* p = PACIENTE_criar(id, nome, prioridade, chegada);

        int hist_tamanho;
        fread(&hist_tamanho, sizeof(int), 1, fp_reg);
        
        if (p != NULL) {
            PILHA* historico = PACIENTE_get_historico(p);

            // Lê cada procedimento e adiciona ao histórico
            for(int j = 0; j < hist_tamanho; j++){
                char procedimento[101];
                fread(procedimento, sizeof(char), 101, fp_reg);
                
                HIST* h = hist_criar(procedimento);
                // Como salvamos da base para o topo, vamos empilhando conforme lemos
                // para restaurar a ordem correta (o último lido será o topo)
                pilha_empilhar(historico, h);
            }
            
            // Insere na AVL
            AVL_inserir(*avl, p);
        } else {
            // Se falhou criar paciente, precisa pular os bytes do histórico no arquivo
            // para não corromper a leitura do próximo paciente
            fseek(fp_reg, hist_tamanho * 101, SEEK_CUR);
        }
    }
    fclose(fp_reg);


    // Carrega a fila de espera
    FILE* fp_fila = fopen("fila.bin", "rb");
    
    if(fp_fila != NULL){
        int tamanho_fila = 0;
        fread(&tamanho_fila, sizeof(int), 1, fp_fila);

        for(int i = 0; i < tamanho_fila; i++){
            int id_fila;
            fread(&id_fila, sizeof(int), 1, fp_fila);

            // Busca o ponteiro do paciente que já foi criado na AVL
            PACIENTE* p = AVL_buscar(*avl, id_fila);
            
            if(p != NULL){
                HEAP_inserir(*heap, p);
            }
        }
        fclose(fp_fila);
    }

    return true;
}