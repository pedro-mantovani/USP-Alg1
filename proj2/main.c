#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "paciente.h"
#include "AVL.h"
#include "heap.h"
#include "IO.h"
#include "hist.h"
#include "pilha.h"

// Função para imprimir o menu
void menu(void){
    printf("1. Registrar paciente\n");
    printf("2. Remover paciente\n");
    printf("3. Listar pacientes\n");
    printf("4. Buscar paciente por ID\n");
    printf("5. Mostrar fila de espera\n");
    printf("6. Dar alta ao paciente\n");
    printf("7. Adicionar procedimento ao histórico médico\n");
    printf("8. Desfazer procedimento do histórico médico\n");
    printf("9. Mostrar menu\n");
    printf("10. Sair\n");
}

// Função para registrar um paciente
void registrar(AVL* registros, HEAP* fila, int* contador){

    // Lê o ID do paciente
    printf("Digite o ID para cadastro do usuário (número): ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("\nErro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }
    if(ID < 0){
        printf("\nErro: Não são permitidos IDs negativos!\n");
        return;
    }

    // Verificando se já existe paciente no registro com esse ID
    PACIENTE* paciente = AVL_buscar(registros, ID);
    int paciente_existente = 0; 
    char nome[81];

    // Paciente já cadastrado
    // Tal como no projeto 1, se não estiver na fila, o programa vê isso como um paciente que já frequentou o hospital e voltou
    // Sua prioridade e chegada serão atualizadas e ele será inserido na fila de espera, sem precisar ser criado de novo
    if(paciente != NULL){
        printf("\nID já cadastrado.\n");
        paciente_existente = 1;
        if(HEAP_busca_id(fila, ID)){
            printf("\nEsse paciente já está na fila de espera!\n");
            return;
        }
    }

    // Paciente não cadastrado
    else{
        // Lê o nome do paciente
        printf("\nDigite o nome do usuário: ");
        getchar();
        fgets(nome, 81, stdin);
        nome[strcspn(nome, "\n")] = '\0';
    }

    // Lê prioridade do paciente
    printf("\nDefina a prioridade do paciente dentre as opções abaixo:\n\n");
    printf("1. Emergência\n");
    printf("2. Muito urgente\n");
    printf("3. Urgente\n");
    printf("4. Pouco urgente\n");
    printf("5. Não urgente\n");
    printf("\nDigite uma prioridade de 1 a 5: ");
    
    int prioridade;
    if(scanf("%d", &prioridade) != 1 || prioridade > 5 || prioridade < 1){
        printf("\nErro: entrada inválida!\n");
        return;
    }

    // Lê ordem de chegada do paciente a partir do contador global
    int chegada = *contador;

    // Cria novo paciente já definindo sua prioriade e ordem de chegada para inserir na lista
    if(paciente_existente == 0){
        paciente = PACIENTE_criar(ID, nome, prioridade, chegada);
        if(paciente == NULL) {
            printf("\nErro ao criar paciente!\n");
            return;
        }

        // Insere paciente na AVL
        if(!AVL_inserir(registros, paciente)){
            printf("\nErro ao inserir paciente no sistema!\n");
            return;
        }
        printf("\nPaciente cadastrado no sistema.\n");
    }

    // Se o paciente já existe, define o estado atual do paciente existente
    else{
        PACIENTE_set_prioridade(paciente, prioridade);
        PACIENTE_set_chegada(paciente, chegada);
    }

    // Insere paciente na fila de espera
    if(!HEAP_inserir(fila, paciente)) {
        printf("\nErro: fila de espera cheia!\n");
        return;
    }
    printf("\nPaciente inserido na fila de espera.\n");
    (*contador)++;
}

// Função para remover um paciente dos registros
void remover(AVL* registros, HEAP* fila){

    // Verifica se a AVL existe e se não está vazia 
    if(registros && !AVL_vazia(registros)){
        int ID;
        printf("Digite o ID do paciente para remover do registro: ");
        if(scanf("%d", &ID) != 1){
            printf("\nErro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }

        // Verifica se o paciente não está na fila de espera para proceder com a remoção
        if(HEAP_busca_id(fila, ID) == false){
            if(AVL_remover(registros, ID)){
                printf("\nPaciente removido do registro.\n");
            }
            // Caso o paciente não exista na AVL
            else{
                printf("\nErro: paciente não encontrado!\n");
            }
        }

        // Caso o paciente ainda esteja na fila
        else{
            printf("\nErro: paciente ainda não foi atendido!\n");
        }
    }
    else printf("Erro: registo de pacientes está vazio!\n"); 
}

// Função para listar todos os pacientes cadastrados no sistema
void listar(AVL* registros){

    // Verifica se os registros existem
    if(registros != NULL && !AVL_vazia(registros)){
        printf("Registros:\n");
        AVL_imprimir_em_ordem(registros);
    }

    // Reporta se não for possível fazer a impressão
    else{
        if(registros == NULL) printf("Erro: o arquivo de registros não existe!\n");
        else if(AVL_vazia(registros)) printf("O arquivo de registros está vazio.\n");
    }
}

// Função para buscar um paciente nos registros com seu ID
void buscar(AVL* registros){

    // Verifica se os registros existem
    if(registros != NULL && !AVL_vazia(registros)){
        int ID;
        printf("Digite o ID do paciente a ser buscado no registro: ");
        if(scanf("%d", &ID) != 1){
            printf("\nErro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }

        // Busca pelo paciente
        PACIENTE* p = AVL_buscar(registros, ID);

        // Imprime seus dados
        if(p != NULL){
            printf("\nPaciente encontrado: ");
            PACIENTE_imprimir_completo(p);
        }
        else{
            printf("\nPaciente não encontrado no registro.\n");
        }
    }

    // Reporta se não for possível realizar a busca
    else{
        if(registros == NULL) printf("Erro: o arquivo de registros não existe!\n");
        else if(AVL_vazia(registros)) printf("O arquivo de registros está vazio.\n");
    }
}

// Função para imprimir a fila de espera
void mostrar_fila(HEAP* fila){

    // Verifica se a fila existe
    if(fila != NULL && !HEAP_vazia(fila)){
        printf("Fila de espera:\n");
        HEAP_imprimir(fila);
    }

    // Reporta se não for possível fazer a impressão
    else{
        if(fila == NULL) printf("Erro: fila de espera não existe!\n");
        else if(HEAP_vazia(fila)) printf("A fila de espera está vazia.\n");
    }
}

// Função para dar alta para um paciente (o tirar da fila de espera)
void dar_alta(HEAP* fila){

    // Tira o paciente da fila de espera
    if(fila != NULL && !HEAP_vazia(fila)){
        PACIENTE* p = HEAP_remover(fila);
        printf("Paciente \"%s\" (ID: %d) foi chamado(a) para atendimento e recebeu alta.\n", PACIENTE_get_nome(p), PACIENTE_get_ID(p));
        PACIENTE_set_chegada(p, -1);
        PACIENTE_set_prioridade(p, -1);
    }

    // Reporta se fila de espera não existir ou estiver vazia
    else{
        if(fila == NULL) printf("Erro: fila de espera não existe!\n");
        else if(HEAP_vazia(fila)) printf("Erro: fila de espera está vazia!\n");
    }
}

// Função para adicionar um procedimento a um paciente
void adicionar_procedimento(AVL* registros, HEAP* fila){

    // Pergunta o ID do paciente
    printf("Digite o ID do paciente para adicionar um procedimento: ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("Erro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }

    // Verifica se o paciente possui cadastro
    PACIENTE* paciente = AVL_buscar(registros, ID);
    if(paciente == NULL){
        printf("Erro: paciente não encontrado!\n");
        return;
    }

    // Pega o histórico do paciente e adiciona um procedimento
    PILHA* hist = PACIENTE_get_historico(paciente);

    if(pilha_cheia(hist)){
        printf("\nErro: histórico do paciente cheio!\n");
        printf("Remova um procedimento antigo antes de adicionar um novo.\n");
        return;
    }

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

// Desfaz o último procedimento de um paciente
void desfazer_procedimento(AVL* registros){

    // Pergunta qual o paciente
    printf("Digite o ID do paciente para desfazer um procedimento: ");
    int ID;
    if(scanf("%d", &ID) != 1){
        printf("Erro: ID inválido!\n");
        while(getchar() != '\n');
        return;
    }

    // Encontra seu registro
    PACIENTE* paciente = AVL_buscar(registros, ID);
    if(paciente == NULL){
        printf("Erro: paciente não encontrado!\n");
        return;
    }

    // PPega seu histórico
    PILHA* hist = PACIENTE_get_historico(paciente);

    // Retira o último procedimento e o imprime
    HIST* procedimento = pilha_desempilhar(hist);
    if(procedimento == NULL)
        printf("Nenhum procedimento a ser retirado.\n");
    else{
        printf("Procedimento \"%s\" retirado.\n", hist_get(procedimento));
        hist_apagar(&procedimento);
    }
    return;
}

// Main: função principal para 
int main(){

    // Declara os registros (AVL) e fila (HEAP)
    AVL* registros = NULL;
    HEAP* fila = NULL;
    int contador = 0;

    // Cria as estruturas vazias para carregar o conteudo do save file delas ou para iniciá-las vazias caso ainda não exista save file
    registros = AVL_criar();
    fila = HEAP_criar();
    
    // Tenta abrir o save file
    FILE* arquivo_savefile = fopen("registros.bin", "rb");

    // Se existir save file
    if(arquivo_savefile != NULL){
        // apenas verifica a existência, agora fechamos para o LOAD abrir corretamente
        fclose(arquivo_savefile);

        // Chama função LOAD pra realizar o carregamento da AVL e da HEAP
        if(!LOAD(&registros, &fila, &contador)){
            printf("Erro: Falha ao carregar os dados do arquivo!\n");

            // Em caso de falha, limpa a lista e a fila e programa termina em erro
            AVL_apagar(&registros);
            HEAP_apagar(&fila);
            return 1;
        }
        printf("Dados carregados com sucesso!\n");

    }
    
    // Se não existir save file dos registros
    else{
        printf("Nenhum arquivo de dados encontrado. Iniciando novo sistema.\n");
    }

    /*
    Loop principal do menu
    */

    printf("Sistema do pronto-socorro iniciado. Selecione uma das opções:\n\n");
    menu();
    bool flag = 0;
    while(!flag){
        printf("\nDigite uma ação de 1 a 10 (digite 9 para ver o menu): ");
        int acao;
        if(scanf("%d", &acao) == 1){
            printf("\n");
            switch(acao){
                case 1: registrar(registros, fila, &contador); break;
                case 2: remover(registros, fila); break;
                case 3: listar(registros); break;
                case 4: buscar(registros); break;
                case 5: mostrar_fila(fila); break;
                case 6: dar_alta(fila); break;
                case 7: adicionar_procedimento(registros, fila); break;
                case 8: desfazer_procedimento(registros); break;
                case 9: menu(); break;
                case 10: flag = 1; break;
                default: printf("Comando não encontrado. Digite números apenas de 1 a 10.\n");
            }
        }
        else{
            printf("\nEntrada inválida. Digite apenas números no menu.\n");
            while(getchar() != '\n');
        }
    }

    /*
    Rotina de fechamento do programa
    */

    // Chama função SAVE para salvar os dados em disco
    SAVE(registros, fila, contador);

    // Limpa memória do programa 
    AVL_apagar(&registros);
    HEAP_apagar(&fila);

    printf("Fim do programa.\n\n");
    return 0;
}