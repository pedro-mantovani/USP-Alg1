#ifndef RELACAOPACIENTES_H
    #define RELACAOPACIENTE_H
    #include <stdlib.h>
    #include <stdbool.h>
    #include "paciente.h"


    typedef struct relacao_ RELACAO; 
    RELACAO *relacao_criar();
    bool relacao_paciente_inserir(RELACAO *r, PACIENTE *paciente);
    bool relacao_paciente_apagar(RELACAO *r, PACIENTE *paciente); 
    PACIENTE *relacao_paciente_buscar(RELACAO *r, int ID);
    bool relacao_listar(RELACAO *r);
    bool relacao_vazia(RELACAO *r);
    bool relacao_cheia(RELACAO *r);






\
#endif 



