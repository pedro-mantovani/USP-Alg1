#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct paciente_ PACIENTE;

    PACIENTE* PACIENTE_criar(int ID);
    bool PACIENTE_apagar(PACIENTE** paciente);
	void PACIENTE_imprimir(PACIENTE* paciente);
	int PACIENTE_get_ID(PACIENTE* paciente);
	bool PACIENTE_set_ID(PACIENTE* paciente, int ID);
    bool PACIENTE_set_vida(PACIENTE* paciente, bool vida);

#endif