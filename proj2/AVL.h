#ifndef AVL_H
    #define AVL_H

    #include <stdbool.h>
    #include "paciente.h"

    typedef struct arv_avl AVL;

    // cria a árvore vazia
    AVL* AVL_criar(void);

    // apaga a árvore e todos os pacientes nela
    void AVL_apagar(AVL** arvore);

    // insere um paciente no banco de dados (organiza por ID?)
    bool AVL_inserir(AVL* arvore, PACIENTE* paciente);

    // remove um paciente do banco de dados pelo ID
    bool AVL_remover(AVL* arvore, int id);

    // busca eficiente (O(log n)) por ID
    PACIENTE* AVL_buscar(AVL* arvore, int id);

    // imprime todos os pacientes ordenados por ID (Crescente)
    void AVL_imprimir_em_ordem(AVL* arvore);

    // retorna a quantidade total de pacientes (útil para o I/O)
    int AVL_tamanho(AVL* arvore);

    // verifica se está vazia
    bool AVL_vazia(AVL* arvore);

#endif