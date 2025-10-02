#ifndef RELACAOPACIENTES_H
    #define RELACAOPACIENTE_H
    #include <stdlib.h>
    #include <stdbool.h>
    #include "paciente.h"

    typedef struct lista_ LISTA; //sim
    LISTA *LISTA_criar(); //sim
	bool LISTA_inserir(LISTA *lista, PACIENTE *paciente); //sim 
	PACIENTE *LISTA_remover(LISTA *lista, int chave);  //sim
	PACIENTE *LISTA_remover_inicio(LISTA *lista);  //sim 
    PACIENTE *LISTA_busca(LISTA *lista, int chave);  
	bool LISTA_apagar(LISTA **lista); //sim 
	int LISTA_tamanho(LISTA *lista); //sim
	bool LISTA_vazia(LISTA *lista); //sim 
	bool LISTA_cheia(LISTA *lista); //sim 
	void LISTA_imprimir(LISTA *lista); //sim

#endif 



