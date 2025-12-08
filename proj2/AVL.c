#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVL.h"
#include "paciente.h"

#define max(a, b) (( (a) > (b) ) ? (a) : (b))
#define ERRO -1

typedef struct no_{
    PACIENTE* paciente;
    struct no_* esq;
    struct no_* dir;
    int altura;
} NO;

struct arv_avl{
    NO* raiz;
    int tamanho;
};

// Função para criar e inicializar uma árvore
AVL* AVL_criar(){
    AVL* avl = (AVL*)(malloc(sizeof(AVL)));
    if(avl != NULL){
        avl->raiz = NULL;
        avl->tamanho = 0;
    }
    return avl;
}

// Função auxiliar para apagar recursivamente uma árvore
void AVL_apagar_aux(NO *no){
    if(no != NULL){
        AVL_apagar_aux(no->esq);
        AVL_apagar_aux(no->dir);
        PACIENTE_apagar(&(no->paciente));
        free(no);
    }
}

// Função principal para apagar uma árvore
void AVL_apagar(AVL **arv){
    if(arv == NULL || *arv == NULL) return;
    AVL_apagar_aux((*arv)->raiz);
    free(*arv);
    *arv = NULL;
}

// Função que retorna o tamanho de uma árvore
int AVL_tamanho(AVL* arvore){
    if(arvore != NULL)
        return arvore->tamanho;
    else return ERRO;
}

// Função para verificar se uma árvore estpa vazia
bool AVL_vazia(AVL* arvore){
    if(!arvore) return true;
    else return (arvore->tamanho == 0);
}

// Função para acessar a altura de um nó
int AVL_altura_no(NO* no){
    if(no == NULL)
        return -1; // convenção: altura de nó nulo = -1
    return no->altura;
}

// Função auxiliar para imprimir uma árvore em ordem crescente
void AVL_imprimir_nos_em_ordem(NO* raiz){
    if(raiz != NULL){
        AVL_imprimir_nos_em_ordem(raiz->esq);
        PACIENTE_imprimir_com_status(raiz->paciente);
        AVL_imprimir_nos_em_ordem(raiz->dir);
    }
}

// Função principal para imprimir uma árvore
void AVL_imprimir_em_ordem(AVL* arvore){
    if(arvore != NULL)
        AVL_imprimir_nos_em_ordem(arvore->raiz);
}

// Função auxiliar para transformar uma AVL em um vetor
void AVL_salvar_nos(NO* raiz, PACIENTE** vec, int* i) {
    if (raiz != NULL) {
        AVL_salvar_nos(raiz->esq, vec, i);
        vec[*i] = raiz->paciente;
        (*i)++;
        AVL_salvar_nos(raiz->dir, vec, i);
    }
}

// Função principal para transformar uma AVL em um vetor
PACIENTE** AVL_salvar(AVL* arvore) {
    if (arvore != NULL) {
        int tamanho = AVL_tamanho(arvore);
        PACIENTE** vec = malloc(sizeof(PACIENTE*) * tamanho);
        if(vec == NULL)
            return NULL;

        int i = 0;
        AVL_salvar_nos(arvore->raiz, vec, &i);

        return vec;
    }
    return NULL;
}

// Rotações
NO* rotacao_direita(NO* A){
    if(A == NULL || A->esq == NULL) return A;
    NO* B = A->esq;
    A->esq = B->dir;
    B->dir = A;

    // atualiza alturas
    A->altura = max(AVL_altura_no(A->esq), AVL_altura_no(A->dir)) + 1;
    B->altura = max(AVL_altura_no(B->esq), AVL_altura_no(B->dir)) + 1;
    return B; // nova raiz da subárvore
}

NO* rotacao_esquerda(NO* A){
    if(A == NULL || A->dir == NULL) return A;
    NO* B = A->dir;
    A->dir = B->esq;
    B->esq = A;

    // atualiza alturas
    A->altura = max(AVL_altura_no(A->esq), AVL_altura_no(A->dir)) + 1;
    B->altura = max(AVL_altura_no(B->esq), AVL_altura_no(B->dir)) + 1;
    return B; // nova raiz da subárvore
}

// Rotações duplas
NO* rotacao_esquerda_direita(NO* A){
    if(A == NULL) return A;
    A->esq = rotacao_esquerda(A->esq);
    return rotacao_direita(A);
}

NO* rotacao_direita_esquerda(NO* A){
    if(A == NULL) return A;
    A->dir = rotacao_direita(A->dir);
    return rotacao_esquerda(A);
}

// Função para criar um nó
NO* criar_no(PACIENTE* paciente){
    NO* no = (NO*)malloc(sizeof(NO));
    if(no != NULL){
        no->altura = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->paciente = paciente;
    }
    return no;
}

// Função auxiliar para inserir um nó na árvore
NO *AVL_inserir_no(NO *raiz, PACIENTE *paciente, int* add){
    // Encontrou a posição
    if(raiz == NULL){
        raiz = criar_no(paciente);
        if(raiz)
            *add = 1;
    }
    // Procura na direita se o ID do paciente é maior que o nó e na esquerda caso contrário
    else if(PACIENTE_get_ID(paciente) > PACIENTE_get_ID(raiz->paciente))
        raiz->dir = AVL_inserir_no(raiz->dir, paciente, add);
    else if(PACIENTE_get_ID(paciente) < PACIENTE_get_ID(raiz->paciente))
        raiz->esq = AVL_inserir_no(raiz->esq, paciente, add);
    
    if(raiz != NULL){
        // Corrige a altura
        raiz->altura = max(AVL_altura_no(raiz->esq), AVL_altura_no(raiz->dir)) + 1;

        // Corrige o balanceamento
        int fb = AVL_altura_no(raiz->esq) - AVL_altura_no(raiz->dir);
        if(fb == -2){
            int fb_dir = AVL_altura_no(raiz->dir->esq) - AVL_altura_no(raiz->dir->dir);
            if(fb_dir <= 0)
                raiz = rotacao_esquerda(raiz);
            else
                raiz = rotacao_direita_esquerda(raiz);
        }
        else if(fb == 2){
            int fb_esq = AVL_altura_no(raiz->esq->esq) - AVL_altura_no(raiz->esq->dir);
            if(fb_esq >= 0)
                raiz = rotacao_direita(raiz);
            else
                raiz = rotacao_esquerda_direita(raiz);
        }
    }

    return raiz;
}

// Função principal para inserir um paciente
bool AVL_inserir(AVL *arv, PACIENTE *paciente){
    if(arv == NULL || paciente == NULL) return false;
    int add = 0;
    arv->raiz = AVL_inserir_no(arv->raiz, paciente, &add);
    if(add)
        arv->tamanho ++;
    return add;
}

// Função auxiliar para realizar uma busca
PACIENTE* AVL_busca_no(NO* raiz, int ID){
    // Não encontrou
    if(raiz == NULL)
        return NULL;
    
    // Encontrou
    if(ID == PACIENTE_get_ID(raiz->paciente))
        return raiz->paciente;
    
    // Procura na direita se o ID do paciente é maior que o nó e na esquerda caso contrário
    if(ID > PACIENTE_get_ID(raiz->paciente))
        return AVL_busca_no(raiz->dir, ID);
    else
        return AVL_busca_no(raiz->esq, ID);
}

// Função principal para realizar uma busca
PACIENTE* AVL_buscar(AVL* arv, int ID){
    if(arv == NULL) return NULL;
    return AVL_busca_no(arv->raiz, ID);
}

/*
Raciocínio da remoção:
- 0 filhos: libera nó
- 1 filho: substitui pelo filho
- 2 filhos: troca com o máximo da subárvore esquerda
*/

// Função auxiliar da remoção
NO* AVL_remover_aux(NO *raiz, int ID, bool remover){

    // Não encontrado
    if(raiz == NULL)
        return NULL;
    
    // Encontrado
    if(ID == PACIENTE_get_ID(raiz->paciente)){

        // Um ou nenhum filho
        if(raiz->esq == NULL || raiz->dir == NULL){
            NO* aux = raiz;
            NO* substituto = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
            // substitui raiz pelo seu único filho (ou NULL se folha)
            raiz = substituto;

            if(remover) // Apaga o paciente
                PACIENTE_apagar(&(aux->paciente));
            
            // Libera o nó
            free(aux);
            aux = NULL;
        }

        // Ambos os filhos: troca pelo máximo da esquerda
        else {
            NO* aux = raiz->esq;
            // Encontra maior valor da sub-arvore esquerda
            while(aux->dir != NULL)
                aux = aux->dir;

            // Removendo o paciente
            PACIENTE_apagar(&(raiz->paciente));

            // Troca raiz e aux
            raiz->paciente = aux->paciente;

            // Remove o nó auxiliar
            // Note que o item não é apagado pois isso o apagaria da raíz também (são os mesmos ponteiros)
            raiz->esq = AVL_remover_aux(raiz->esq, PACIENTE_get_ID(raiz->paciente), false);
        }
    }

    // Caso não tenha encontrado continua procurando
    else if(ID < PACIENTE_get_ID(raiz->paciente))
        raiz->esq = AVL_remover_aux(raiz->esq, ID, true);
    else
        raiz->dir = AVL_remover_aux(raiz->dir, ID, true);

    // Arruma a altura
    raiz->altura = max(AVL_altura_no(raiz->esq), AVL_altura_no(raiz->dir)) + 1;

    // Arruma o balanceamento
    int fb = AVL_altura_no(raiz->esq) - AVL_altura_no(raiz->dir);
    if(fb == -2){
        int fb_dir = AVL_altura_no(raiz->dir->esq) - AVL_altura_no(raiz->dir->dir);
        if(fb_dir <= 0)
            raiz = rotacao_esquerda(raiz);
        else
            raiz = rotacao_direita_esquerda(raiz);
    }
    else if(fb == 2){
        int fb_esq = AVL_altura_no(raiz->esq->esq) - AVL_altura_no(raiz->esq->dir);
        if(fb_esq >= 0)
            raiz = rotacao_direita(raiz);
        else
            raiz = rotacao_esquerda_direita(raiz);
    }

    return raiz;
}

// Função principal da remoção
bool AVL_remover(AVL* arv, int ID){
    // verifica se a árvore e o ID existem antes de tentar remover
    if(AVL_buscar(arv, ID) == NULL)
        return false;
    
    arv->raiz = AVL_remover_aux(arv->raiz, ID, true);
    arv->tamanho--;
    return true;
}