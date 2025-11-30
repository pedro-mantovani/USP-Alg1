#ifndef IO_H
	#define IO_H
	#include "paciente.h"
    #include "AVL.h"
    #include "heap.h"
    #include <stdbool.h>

    bool SAVE(AVL* avl, HEAP* heap, int contador); // Salva os itens da avl e da heap + o contador global em arquivos
    bool LOAD(AVL**  avl, HEAP**  heap, int* contador); // Carrega os itens da avl e da heap + o contador global
	  
#endif
