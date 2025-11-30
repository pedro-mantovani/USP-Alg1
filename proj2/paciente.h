#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    typedef struct paciente_ PACIENTE;

    
    PACIENTE* PACIENTE_criar(int ID, char nome[], int prioridade, int chegada);
    // prioridade = o tipo de emergencia; chegada = armazena a ordem de chegada do paciente automaticamente (usa contador global na main)
    
    bool PACIENTE_apagar(PACIENTE** paciente);
    void PACIENTE_imprimir(PACIENTE* paciente);
    
    int PACIENTE_get_ID(PACIENTE* paciente);
    const char* PACIENTE_get_nome(PACIENTE* paciente);
    int PACIENTE_get_prioridade(PACIENTE* paciente);
    int PACIENTE_get_chegada(PACIENTE* paciente);

    bool PACIENTE_set_ID(PACIENTE* paciente, int ID);
    bool PACIENTE_set_nome(PACIENTE* paciente, char nome[]);
    bool PACIENTE_set_prioridade(PACIENTE* paciente, int prioridade);
    bool PACIENTE_set_chegada(PACIENTE* paciente, int chegada);

#endif