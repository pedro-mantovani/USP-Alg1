#include <stdio.h>
#include <stdbool.h>
#include "hist.h"
#include "pilha.h"

void menu(void){
    printf("1. Registrar paciente\n");
    printf("2. Registrar óbito de paciente\n");
    printf("3. Adicionar procedimento ao histórico médico\n");
    printf("4. Desfazer procedimento do histórico médico\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar histórico do paciente\n");
    printf("8. Mostrar menu\n");
    printf("9. Sair\n");
}

void registrar(){

}

void obito(){

}

void adicionar_procedimento(){

}

void desfazer_procedimento(){

}

void atender(){

}

void mostrar_fila(){

}

void imprimir_historico(){

}


int main(){
    printf("Sistema do pronto socorro iniciado, selecione uma das opções:\n");
    menu();
    bool flag = 0;
    while(!flag){
        int acao;
        scanf("%d", &acao);
        switch(acao){
            case 1: registrar(); break;
            case 2: obito(); break;
            case 3: adicionar_procedimento(); break;
            case 4: desfazer_procedimento(); break;
            case 5: atender(); break;
            case 6: mostrar_fila(); break;
            case 7: imprimir_historico(); break;
            case 8: menu(); break;
            case 9: flag = 1; break;
            default: printf("Comando não encontrado, digite um número de 1 a 9\n");
        }
    }
    printf("Fim do programa\n");
    return 0;
}