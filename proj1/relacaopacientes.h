#ifndef RELACAOPACIENTES_H
    #define RELACAOPACIENTES_H
    #include <stdlib.h>
    #include <stdbool.h>
    #include "paciente.h"

    typedef struct lista_ LISTA;
    LISTA *LISTA_criar();
	bool LISTA_inserir(LISTA *lista, PACIENTE *paciente);
	bool LISTA_remover(LISTA *lista, int chave);
	PACIENTE *LISTA_remover_inicio(LISTA *lista);
    PACIENTE *LISTA_busca(LISTA *lista, int chave);  
	bool LISTA_apagar(LISTA **lista);
	int LISTA_tamanho(LISTA *lista);
	bool LISTA_vazia(LISTA *lista);
	bool LISTA_cheia(LISTA *lista);
	void LISTA_imprimir(LISTA *lista);
    int LISTA_id_fim(LISTA *lista); 

#endif 



