#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

void registrar(LISTA* l, FILA* f) {
    printf("Digite o ID do usuário (número): ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("Erro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }
    if(ID < 0){
        printf("Erro: Não são permitidos IDs negativos!\n");
        return;
    }
    PACIENTE* paciente = LISTA_busca(l, ID);
    // Verifica se já existe paciente com esse ID
    if (paciente != NULL) {
        printf("ID já cadastrado.\n");
        if(FILA_busca(f, ID)){
            printf("Esse paciente já está na fila de espera!\n");
            return;
        }
    }else{
        // Lê o nome do paciente
        printf("Digite o nome do usuário: ");
        char nome[81];
        getchar();
        fgets(nome, 81, stdin);
        nome[strcspn(nome, "\n")] = '\0';


        // Cria novo paciente
        paciente = PACIENTE_criar(ID, nome);
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
    }

    // Insere paciente na fila de espera
    if (!FILA_inserir(f, paciente)) {
        printf("Erro: fila de espera cheia!\n");
        return;
    }
    printf("Paciente inserido na fila de espera.\n");
}


void obito(LISTA* l, FILA* f){ //recebe a lista(relação de pacientes)
    if(l && !LISTA_vazia(l)){ //verifica se a lista existe 
        int id;
        printf("Digite o ID do paciente para registrar óbito: ");
        if(scanf("%d", &id) != 1){
            printf("Erro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }
        if(FILA_busca(f, id) == NULL){ //verifica se o paciente está na fila de espera
            if(LISTA_remover(l, id)){
                printf("Óbito do paciente registrado.\n");
            }else{
                printf("Erro: paciente não encontrado!\n"); // Só da erro se o paciente não for encontrado ou a lista não existir (o que já vimos não ser o caso)
            }
        }else{
            printf("Erro: paciente ainda não foi atendido!\n"); //o paciente ainda está na fila (não pode morrer)
        }
    }
    else printf("Erro: lista de pacientes está vazia!\n"); 
}

void adicionar_procedimento(LISTA* l, FILA* f){
    printf("Digite o ID do paciente para adicionar um procedimento: ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("Erro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }
    if(FILA_busca(f, ID) != NULL){
        printf("Erro: paciente ainda não foi atendido!\n");
        return;
    }
    PACIENTE* paciente = LISTA_busca(l, ID);
    if(paciente == NULL){
        printf("Erro: paciente não encontrado!\n");
        return;
    }
    PILHA* hist = PACIENTE_get_historico(paciente);
    char procedimento[101];
    printf("Digite o procedimento que será adicionado: ");
    getchar();
    fgets(procedimento, 101, stdin);
    procedimento[strcspn(procedimento, "\n")] = '\0';
    HIST* proc = hist_criar(procedimento);
    if(pilha_empilhar(hist, proc)){
        printf("Procedimento inserido com sucesso.\n");
        return;
    }
    printf("Erro ao inserir procedimento!\n");
}

void desfazer_procedimento(LISTA* l){
    printf("Digite o ID do paciente para desfazer um procedimento: ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("Erro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }
    PACIENTE* paciente = LISTA_busca(l, ID);
    if(paciente == NULL){
        printf("Erro: paciente não encontrado!\n");
        return;
    }
    PILHA* hist = PACIENTE_get_historico(paciente);
    HIST* procedimento = pilha_desempilhar(hist);
    if(procedimento == NULL)
        printf("Nenhum procedimento a ser retirado.\n");
    else{
        printf("Procedimento \"%s\" retirado.\n", hist_get(procedimento));
        hist_apagar(&procedimento);
    }
    return;
}


void atender(FILA* f){

    // Tira o paciente da fila
    if(f != NULL && !FILA_vazia(f)){
        PACIENTE* p = FILA_remover(f);
        printf("Paciente \"%s\" (ID: %d) chamado(a) para atendimento.\n", PACIENTE_get_nome(p), PACIENTE_get_ID(p));
    }

    // Reporta se fila não existir ou estiver vazia
    else{
        if(f == NULL) printf("Erro: fila não existe!\n");
        else if(FILA_vazia(f)) printf("Erro: fila está vazia!\n");
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

void imprimir_historico(LISTA *lista){
    if(lista && !LISTA_vazia(lista)){
        int id;
        printf("Insira o ID do paciente: ");
        if(scanf("%d", &id) != 1){
            printf("Erro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }
        PACIENTE *p = LISTA_busca(lista, id); 
        if(p != NULL){
            PILHA *historico = PACIENTE_get_historico(p); //pega o histórico do paciente(uma pilha)
            if(pilha_vazia(historico)){
                printf("O paciente não possui histórico.\n"); //caso a pilha de históricos do paciente esteja vazia 
            }
            else{
                pilha_print(historico); //imprime os itens da pilha (os procedimentos realizados) 
            }  
        }
        else{
            printf("Erro: paciente não encontrado na lista!\n"); 
        }
    }
    else printf("Erro: lista de pacientes está vazia!\n"); 
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

    printf("Sistema do pronto-socorro iniciado. Selecione uma das opções:\n");
    menu();
    bool flag = 0;
    while(!flag){
        printf("\nDigite uma ação (1-9): ");
        int acao;
        if(scanf("%d", &acao) == 1){
            printf("\n");
            switch(acao){
                case 1: registrar(relacao_pacientes, fila_de_espera); break;
                case 2: obito(relacao_pacientes, fila_de_espera); break;
                case 3: adicionar_procedimento(relacao_pacientes, fila_de_espera); break;
                case 4: desfazer_procedimento(relacao_pacientes); break;
                case 5: atender(fila_de_espera); break;
                case 6: mostrar_fila(fila_de_espera); break;
                case 7: imprimir_historico(relacao_pacientes); break;
                case 8: menu(); break;
                case 9: flag = 1; break;
                default: printf("Comando não encontrado, digite um número de 1 a 9.\n");
            }
        }
        else{
            printf("Entrada inválida. Digite apenas números no menu.\n");
            while(getchar() != '\n');
        }
    }

    // -------------------------------------------------

    // Chama função SAVE para salvar os dados em disco
    SAVE(relacao_pacientes, fila_de_espera);

    // Limpa memória do programa
    LISTA_apagar(&relacao_pacientes);
    FILA_apagar(&fila_de_espera);

    printf("Fim do programa.\n");
    return 0;
}