#include <stdio.h>
#include <stdbool.h>
#include "hist.h"
#include "pilha.h"
#include "paciente.h"
#include "triagem.h"

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

void registrar(LISTA* l, FILA* f) {
    printf("Qual o ID do usuário?\n");
    int ID;
    scanf("%d", &ID);

    // Verifica se já existe paciente com esse ID
    if (LISTA_busca(l, ID) != NULL) {
        printf("Erro: ID já cadastrado!\n");
        return;
    }

    // Cria novo paciente
    PACIENTE* paciente = PACIENTE_criar(ID);
    if (paciente == NULL) {
        printf("Erro ao criar paciente!\n");
        return;
    }

    // Insere paciente na lista
    if (!LISTA_inserir(l, paciente)) {
        printf("Erro ao inserir paciente no sistema!\n");
        return;
    }
    printf("Paciente cadastrado no sistema.\n");

    // Insere paciente na fila
    if (!FILA_inserir(f, paciente)) {
        printf("Erro: fila de espera cheia!\n");
        return;
    }
    printf("Paciente inserido na fila de espera.\n");
}


void obito(){

}

void adicionar_procedimento(){
    printf("Qual o ID do paciente que terá um procedimento adicionado?\n");
    int ID;
    scanf("%d", &ID);

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
            case 1: registrar(); break; // Pedro
            case 2: obito(); break; // Mafer
            case 3: adicionar_procedimento(); break; // Pedro
            case 4: desfazer_procedimento(); break; // Pedro
            case 5: atender(); break; // Clara
            case 6: mostrar_fila(); break; // Clara
            case 7: imprimir_historico(); break; // Mafer
            case 8: menu(); break; // Feito
            case 9: flag = 1; break;
            default: printf("Comando não encontrado, digite um número de 1 a 9\n");
        }
    }
    printf("Fim do programa\n");
    return 0;
}