#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "pilha.h"

    typedef struct paciente_ PACIENTE;

    PACIENTE* PACIENTE_criar(int ID, char nome[]);
    bool PACIENTE_apagar(PACIENTE** paciente);
	void PACIENTE_imprimir(PACIENTE* paciente);
    PILHA* PACIENTE_get_historico(PACIENTE* paciente);
	int PACIENTE_get_ID(PACIENTE* paciente);
	bool PACIENTE_set_ID(PACIENTE* paciente, int ID);
    const char* PACIENTE_get_nome(PACIENTE* paciente);
    bool PACIENTE_set_nome(PACIENTE* paciente, char nome[]);

#endif