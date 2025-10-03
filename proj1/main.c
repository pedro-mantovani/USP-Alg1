#include <stdio.h>
#include <stdbool.h>
#include "hist.h"
#include "pilha.h"
#include "paciente.h"
#include "triagem.h"
#include "relacaopacientes.h"
#include "IO.h"

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

// #### COLOCA QUE ID NEGATIVO NAO PODE SER INSERIDO!!!!!!!!!!!!!
// Isso pq -1 é o nosso índice de erro
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


void obito(LISTA* l){
    printf("Funcao ainda nao implementada.\n");
}

void adicionar_procedimento(LISTA* l){
    printf("Funcao ainda nao implementada.\n");
}

void desfazer_procedimento(LISTA* l){
    printf("Funcao ainda nao implementada.\n");
}

void atender(FILA* f){

    // Tira o paciente da fila
    if(f != NULL && !FILA_vazia(f)){
        PACIENTE* p = FILA_remover(f);
        printf("Paciente com ID %d chamado para atendimento.\n", PACIENTE_get_ID(p));
    }

    // Reporta se fila não existir ou estiver vazia
    else{
        if(f == NULL) printf("Erro: fila não existe!\n");
        else if(FILA_vazia(f)) printf("Erro: fila está vazia.\n");
    }
}

void mostrar_fila(FILA* f){

    // Usa FILA_print para fazer a impressão
    if(f != NULL && !FILA_vazia(f)){
        printf("Fila:\n");
        FILA_print(f);
    }

    // Reporta se não for possível fazer a impressão
    else{
        if(f == NULL) printf("Erro: fila não existe!\n");
        else if(FILA_vazia(f)) printf("A fila está vazia.\n");
    }
}

void imprimir_historico(LISTA* l){
    printf("Funcao ainda nao implementada.\n");
}


int main(){
    // Declara lista e fila
    LISTA* relacao_pacientes = NULL;
    FILA* fila_de_espera = NULL;

    // Cria as estruturas vazias para carregar o conteudo do save file delas ou para iniciá-las vazias caso ainda não exista save file
    relacao_pacientes = LISTA_criar();
    fila_de_espera = FILA_criar();

    // Tenta abrir lista
    FILE* lista_savefile = fopen("lista.bin", "rb");

    // Se existir save file da lista
    if (lista_savefile != NULL){
        fclose(lista_savefile);

        // Chama função LOAD pra realizar o carregamento
        if (!LOAD(&relacao_pacientes, &fila_de_espera)) {
            printf("Erro: Falha ao carregar os dados do arquivo!\n");

            // Em caso de falha, limpa a lista e a fila e programa termina em erro
            LISTA_apagar(&relacao_pacientes);
            FILA_apagar(&fila_de_espera);
            return 1;
        }
        printf("Dados carregados com sucesso!\n");

    }
    
    // Se não existir save file da lista
    else{
        printf("Nenhum arquivo de dados encontrado. Iniciando novo sistema.\n");
    }

    // -------------------------------------------------

    printf("Sistema do pronto-socorro iniciado, selecione uma das opções:\n");
    menu();
    bool flag = 0;
    while(!flag){
        int acao;
        scanf("%d", &acao);
        switch(acao){
            case 1: registrar(relacao_pacientes, fila_de_espera); break; // Pedro
            case 2: obito(relacao_pacientes); break; // Mafer
            case 3: adicionar_procedimento(relacao_pacientes); break; // Pedro
            case 4: desfazer_procedimento(relacao_pacientes); break; // Pedro
            case 5: atender(fila_de_espera); break; // Clara
            case 6: mostrar_fila(fila_de_espera); break; // Clara
            case 7: imprimir_historico(relacao_pacientes); break; // Mafer
            case 8: menu(); break; // Feito
            case 9: flag = 1; break;
            default: printf("Comando não encontrado, digite um número de 1 a 9\n");
        }
    }

    // -------------------------------------------------

    // Chama função SAVE para salvar os dados em disco
    SAVE(relacao_pacientes, fila_de_espera);

    // Limpa memória do programa
    LISTA_apagar(&relacao_pacientes);
    FILA_apagar(&fila_de_espera);

    printf("Fim do programa\n");
    return 0;
}