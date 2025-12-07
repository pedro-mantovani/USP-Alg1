#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "paciente.h"
#include "heap.h"

//implementação sequencial da heap, que aproveita o uso dos índices do vetor para facilitar a busca e estabelecer a relação de ordem presente na heap 
struct heap_{
    PACIENTE *fila[TAM_HEAP]; //vetor de pacientes que representará a fila, de tamanho máximo definido
    int fim; //indica a posição livre para inserção 
};

HEAP *HEAP_criar(void){ //operação de criar heap, inicializa todos os elementos da estrutura 
    HEAP *fila = (HEAP*) malloc(sizeof(HEAP)); //aloca endereço de memória para a esturura
    if(fila){
        fila->fim = 0; // indica que não há elementos na fila, primeira posição disponível para inserção é 0
    }
    return fila; //retorna o endereço de memória para o cliente 
}

void HEAP_apagar(HEAP **fila){ //apaga a estrutura de dados (mas não apaga os pacientes)
    if(fila && *fila){ //verifica se a fila existe 
        while(!HEAP_vazia(*fila)){ //caso haja elementos na heap, eles serão removidos antes de liberar espaço da estrutura de memória 
            HEAP_remover(*fila); 
        }
        free(*fila); //libera o endereço de memória 
        *fila = NULL; //inicializa como nulo 
    }
}

void HEAP_swap(HEAP *fila, int i, int j){ //função auxiliar que troca elementos, dado dois índices do vetor (vai ser usada na fix-up)
    PACIENTE* aux = fila->fila[i];
    fila->fila[i] = fila->fila[j]; 
    fila->fila[j] = aux; 
}

void HEAP_fixup(HEAP *fila){ //função auxiliar de ajustar a heap para inserções
    if(fila){ 
        int ultimo = fila->fim - 1; //posição do último elemento da heap
        int pai = (ultimo - 1)/2; //posição do pai do ultimo elemento
        while(ultimo > 0 && PACIENTE_get_prioridade(fila->fila[ultimo]) < PACIENTE_get_prioridade(fila->fila[pai])){
            HEAP_swap(fila, ultimo, pai);
            ultimo = pai;
            pai = (ultimo - 1)/2;
        }
    }
}

bool HEAP_inserir(HEAP *fila, PACIENTE *paciente){
    if(fila && !HEAP_cheia(fila)){ //para podermos inserir na heap, ela precisa existir (primeira condição) E não pode estar cheia(segunda condição) 
        fila->fila[fila->fim] = paciente; //coloca o paciente na ultima posição livre para inserção 
        fila->fim++; //incrementa a última posição para inserção 
        HEAP_fixup(fila); //ajusta a heap
        return true;
    }else return false; 
}

int menor_filho(HEAP *fila, int dir, int esq){ //encontra o menor filho dado um índice do vetor, retorna o índice do menor 
    if(PACIENTE_get_prioridade(fila->fila[dir]) < PACIENTE_get_prioridade(fila->fila[esq])){
        return dir;
    }else{
        return esq; 
    }
}


void HEAP_fixdown(HEAP *fila){ //função auxiliar que ajusta a heap para remoções
    if(fila){
        int pai = 0; //posição da raíz, ou primeiro elemento da fila
        int esq, dir, menor; //posições do filho esquerdo, direito e o menor entre eles, respectivamente 

        while(pai < fila->fim){ //enquando a posição do pai for menor que a posição do ultimo elemento
            esq = 2*pai + 1;
            dir = 2*pai + 2; //indexação dos filhos direito e esquerdo, obedecendo a ordem da heap 
            if(esq >= fila->fim){ //se não há filho esquerdo chegamos nas folhas
                break; 
            } 
            if(dir < fila->fim){
                menor = menor_filho(fila, dir, esq); 
            }else{
                menor = esq; //só há o filho esquerdo 
            }
            if(PACIENTE_get_prioridade(fila->fila[pai]) <= PACIENTE_get_prioridade(fila->fila[menor])){ //a ordem da heap já está correta 
                break;
            }
            HEAP_swap(fila, pai, menor); //se não, fazemos a troca 
            pai = menor; 

        }
    } 
}

PACIENTE *HEAP_remover(HEAP *fila){ //função recebe a heap e devolve o primeiro item da fila (paciente com maior prioridade, raíz da heap)
    if(fila && !HEAP_vazia(fila)){ //fila precisa existir e não pode estar vazia 
        PACIENTE *removido; //paciente que será retornado ao cliente 
        removido = fila->fila[0]; //primeiro paciente será removido 
        fila->fila[0] = fila->fila[fila->fim - 1]; //o ultimo elemento será levado para raíz 
        fila->fim--; //decrementamos o tamanho da fila 
        HEAP_fixdown(fila); //reajuste da heap 

        return removido;
    }
    else return NULL; //caso nao seja possível remover o paciente por algum motivo do condicional inicial
}

void HEAP_imprimir(HEAP *fila){ //vai imprimir os elementos da heap por ordem de maior para menor prioridade (maior prioridade: 1 e menor:5)
    if(!fila || HEAP_vazia(fila)) return;

    //para imprimir os elementos da heap, será necessário criar uma cópia dela mesma pois removeremos os pacientes em ordem, o que destruíria a heap original
    HEAP *heap_aux = HEAP_criar(); 
    if (!heap_aux) return;

    for(int i = 0; i < fila->fim; i++){
        heap_aux->fila[i] = fila->fila[i];
    } //copiamos, em ordem, um vetor para o outro 
    heap_aux->fim = fila->fim; 
    while(!HEAP_vazia(heap_aux)){ //vai removendo os pacientes em ordem de prioridade 
        PACIENTE *p = HEAP_remover(heap_aux); 
        PACIENTE_imprimir_com_status(p); 
    }
    free(heap_aux); //liberamos a memória alocada para a heap auxiliar 
}

bool HEAP_busca_id(HEAP *fila, int id){ //busca um paciente pelo id. como a heap não é ordenada por id, a busca é sequencial
    if(fila == NULL || HEAP_vazia(fila)) return false;

    for(int i = 0; i < fila->fim; i++){
        if(id == PACIENTE_get_ID(fila->fila[i])){
            return true;
        }
    }
    return false; 
}

bool HEAP_cheia(HEAP *fila){
    if(fila){
        if(fila->fim == TAM_HEAP){
            return true; 
        }
    } return false; 
}

bool HEAP_vazia(HEAP *fila){
    if(fila){
        if(fila->fim == 0){
            return true;
        }
    } return false;
}

int HEAP_tamanho(HEAP *fila){ //devolve o tamanho da fila
    int tamanho;
    if(fila){
        tamanho = fila->fim;
        return tamanho;
    } else return -1; //caso não exista fila 
}