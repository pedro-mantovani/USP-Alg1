#ifndef AVL_H
    #define AVL_H

    #include <stdbool.h>
    #include "paciente.h"

    typedef struct arv_avl AVL;

    // Cria a árvore vazia
    AVL* AVL_criar(void);

    // Apaga a árvore e todos os pacientes nela
    void AVL_apagar(AVL** arvore);

    // Insere um paciente no banco de dados
    bool AVL_inserir(AVL* arvore, PACIENTE* paciente);

    // Remove um paciente do banco de dados pelo ID
    bool AVL_remover(AVL* arvore, int id);

    // Busca por ID
    PACIENTE* AVL_buscar(AVL* arvore, int id);

    // Imprime todos os pacientes ordenados por ID
    void AVL_imprimir_em_ordem(AVL* arvore);

    // Retorna a quantidade total de pacientes (útil para o I/O)
    int AVL_tamanho(AVL* arvore);

    // Verifica se está vazia
    bool AVL_vazia(AVL* arvore);

    // Função para transformar uma AVL em um vetor (útil para o I/O)
    PACIENTE** AVL_salvar(AVL* arvore);

#endif