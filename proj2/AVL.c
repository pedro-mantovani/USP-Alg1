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

int AVL_tamanho(AVL* arvore){
    if(arvore != NULL)
        return arvore->tamanho;
    else return ERRO;
}

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

// Imprime os elementos em ordem crescente
void AVL_imprimir_nos_em_ordem(NO* raiz){
    if(raiz != NULL){
        AVL_imprimir_nos_em_ordem(raiz->esq);
        PACIENTE_imprimir_com_status(raiz->paciente);
        AVL_imprimir_nos_em_ordem(raiz->dir);
    }
}

void AVL_imprimir_em_ordem(AVL* arvore){
    if(arvore != NULL)
        AVL_imprimir_nos_em_ordem(arvore->raiz);
}

// Função para transformar uma AVL em um vetor
void AVL_salvar_nos(NO* raiz, PACIENTE** vec, int* i) {
    if (raiz != NULL) {
        AVL_salvar_nos(raiz->esq, vec, i);
        vec[*i] = raiz->paciente;
        (*i)++;
        AVL_salvar_nos(raiz->dir, vec, i);
    }
}

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

// Rotações: ajustam ponteiros e atualizam alturas corretamente
NO* rodar_direita(NO* A){
    if(A == NULL || A->esq == NULL) return A;
    NO* B = A->esq;
    A->esq = B->dir;
    B->dir = A;

    // atualiza alturas (A é filho direito de B após rotação)
    A->altura = max(AVL_altura_no(A->esq), AVL_altura_no(A->dir)) + 1;
    // B tem a mesma altura
    return B; // nova raiz da subárvore
}

NO* rodar_esquerda(NO* A){
    if(A == NULL || A->dir == NULL) return A;
    NO* B = A->dir;
    A->dir = B->esq;
    B->esq = A;

    // atualiza alturas
    A->altura = max(AVL_altura_no(A->esq), AVL_altura_no(A->dir)) + 1;
    // B tem a mesma altura
    return B; // nova raiz da subárvore
}

// Rotações duplas
NO* rodar_esquerda_direita(NO* A){
    if(A == NULL) return A;
    A->esq = rodar_esquerda(A->esq);
    return rodar_direita(A);
}

NO* rodar_direita_esquerda(NO* A){
    if(A == NULL) return A;
    A->dir = rodar_direita(A->dir);
    return rodar_esquerda(A);
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
NO *AVL_inserir_no(NO *raiz, PACIENTE *paciente){
    // Encontrou a posição
    if(raiz == NULL)
        return criar_no(paciente);
    
    // Se o ID do paciente for maior vai para a direita, senão para a esquerda (igual vai à esquerda aqui)
    if(PACIENTE_get_ID(paciente) > PACIENTE_get_ID(raiz->paciente))
        raiz->dir = AVL_inserir_no(raiz->dir, paciente);
    else
        raiz->esq = AVL_inserir_no(raiz->esq, paciente);
    
    // Corrige a altura
    raiz->altura = max(AVL_altura_no(raiz->esq), AVL_altura_no(raiz->dir)) + 1;

    // Corrige o balanceamento
    int fb = AVL_altura_no(raiz->esq) - AVL_altura_no(raiz->dir);
    if(fb == -2){
        // caso direita pesada
        int fb_dir = AVL_altura_no(raiz->dir->esq) - AVL_altura_no(raiz->dir->dir);
        if(fb_dir <= 0)
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }
    else if(fb == 2){
        // caso esquerda pesada
        int fb_esq = AVL_altura_no(raiz->esq->esq) - AVL_altura_no(raiz->esq->dir);
        if(fb_esq >= 0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }

    return raiz;
}

// Função principal para inserir um paciente
bool AVL_inserir(AVL *arv, PACIENTE *paciente){
    if(arv == NULL || paciente == NULL) return false;
    arv->raiz = AVL_inserir_no(arv->raiz, paciente);
    if(arv->raiz != NULL){
        arv->tamanho ++;
        return 1;
    }
    else return 0;
}

// Função auxiliar para realizar uma busca
PACIENTE* AVL_busca_no(NO* raiz, int ID){
    if(raiz == NULL)
        return NULL;
    
    if(ID == PACIENTE_get_ID(raiz->paciente))
        return raiz->paciente;
    
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
- 2 filhos: troca com predecessor (máx da subárvore esquerda)
*/

// Função auxiliar para o caso do nó a ser removido ter dois filhos
void troca_max_esq(NO* troca, NO* raiz, NO* ant){
    // troca percorre para a direita até o máximo
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    // troca é o nó máximo da subárvore esquerda
    if(raiz == ant)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    // substitui o paciente da raiz pelo paciente do troca
    PACIENTE *antigo = raiz->paciente;
    raiz->paciente = troca->paciente; // transferimos o ponteiro do paciente
    troca->paciente = NULL;       // evita double-free do paciente quando free(troca)
    PACIENTE_apagar(&antigo);     // apaga o paciente antigo da raiz
    free(troca);
    troca = NULL;
}

NO* AVL_remover_aux(NO *raiz, int ID){

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

            // libera o nó antigo (e seu paciente)
            PACIENTE_apagar(&(aux->paciente));
            free(aux);
            aux = NULL;

            // se ficou vazio retorna imediatamente (evita acessar campos de raiz == NULL)
            if(raiz == NULL)
                return NULL;
        }

        // Ambos os filhos: troca pelo máximo da esquerda
        else {
            troca_max_esq(raiz->esq, raiz, raiz);
            // após troca, continuação: precisamos rebalancear essa raiz (já com novo paciente)
        }
    }

    // Ainda tem lugar para procurar (caso não encontrou ainda)
    else if(ID < PACIENTE_get_ID(raiz->paciente))
        raiz->esq = AVL_remover_aux(raiz->esq, ID);
    else
        raiz->dir = AVL_remover_aux(raiz->dir, ID);
 
    // Se raiz se tornou NULL por.remoção em baixo, retorna
    if(raiz == NULL)
        return NULL;

    // Arrumando a altura
    raiz->altura = max(AVL_altura_no(raiz->esq), AVL_altura_no(raiz->dir)) + 1;

    // Arrumando o balanceamento
    int fb = AVL_altura_no(raiz->esq) - AVL_altura_no(raiz->dir);
    if(fb == -2){
        int fb_dir = AVL_altura_no(raiz->dir->esq) - AVL_altura_no(raiz->dir->dir);
        if(fb_dir <= 0)
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }
    else if(fb == 2){
        int fb_esq = AVL_altura_no(raiz->esq->esq) - AVL_altura_no(raiz->esq->dir);
        if(fb_esq >= 0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }

    return raiz;
}

bool AVL_remover(AVL* arv, int ID){
    if(arv == NULL)
        return false;
    // verifica se a ID existe antes de tentar remover
    if(AVL_buscar(arv, ID) == NULL)
        return false;
    arv->raiz = AVL_remover_aux(arv->raiz, ID);
    arv->tamanho--;
    return true;
}

