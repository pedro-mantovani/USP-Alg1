#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "paciente.h"
#include "AVL.h"
#include "heap.h"
#include "IO.h"

int contador;

void menu(void){
    printf("1. Registrar paciente\n");
    printf("2. Remover paciente\n");
    printf("3. Listar pacientes\n");
    printf("4. Buscar paciente por ID\n");
    printf("5. Mostrar fila de espera\n");
    printf("6. Dar alta ao paciente\n");
    printf("7. Mostrar menu\n");
    printf("8. Sair\n");
}

void registrar(AVL* registros, HEAP* fila){
    // Lê o ID do paciente
    printf("Digite o ID para cadastro do usuário (número): ");
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

    // Verificando se já existe paciente no registro com esse ID
    PACIENTE* paciente = AVL_buscar(registros, ID);
    int paciente_existente = 0; 
    char nome[81];

    // Paciente já cadastrado
    // Tal como no projeto 1, se não estiver na fila, o programa vê isso como um paciente que já frequentou o hospital e voltou
    // Sua prioridade e chegada serão atualizadas e ele será inserido na fila de espera, sem precisar ser criado de novo
    if(paciente != NULL){
        printf("ID já cadastrado.\n");
        paciente_existente = 1;
        if(HEAP_busca_id(fila, ID)){
            printf("Esse paciente já está na fila de espera!\n");
            return;
        }
    }

    // Paciente não cadastrado
    else{
        // Lê o nome do paciente
        printf("Digite o nome do usuário: ");
        getchar();
        fgets(nome, 81, stdin);
        nome[strcspn(nome, "\n")] = '\0';
    }

    // Lê prioridade do paciente
    printf("Defina a prioridade do paciente dentre as opções abaixo:\n");
    printf("1. Emergência\n");
    printf("2. Muito urgente\n");
    printf("3. Urgente\n");
    printf("4. Pouco urgente\n");
    printf("5. Não urgente\n");
    printf("\nDigite uma prioridade de 1 a 5: ");
    
    int prioridade;
    if(scanf("%d", &prioridade) != 1 || prioridade > 5 || prioridade < 1){
        printf("Erro: entrada inválida!\n");
        return;
    }

    // Lê ordem de chegada do paciente a partir do contador global
    int chegada = contador;

    // Cria novo paciente já definindo sua prioriade e ordem de chegada para inserir na lista
    if(paciente_existente == 0){
        paciente = PACIENTE_criar(ID, nome, prioridade, chegada);
        if(paciente == NULL) {
            printf("Erro ao criar paciente!\n");
            return;
        }

        // Insere paciente na AVL
        if(!AVL_inserir(registros, paciente)){
            printf("Erro ao inserir paciente no sistema!\n");
            return;
        }
        printf("Paciente cadastrado no sistema.\n");
    }

    // Se o paciente já existe, define o estado atual do paciente existente
    else{
        PACIENTE_set_prioridade(paciente, prioridade);
        PACIENTE_set_chegada(paciente, chegada);
    }

    // Insere paciente na fila de espera
    if(!HEAP_inserir(fila, paciente)) {
        printf("Erro: fila de espera cheia!\n");
        return;
    }
    printf("Paciente inserido na fila de espera.\n");
    contador++;
}

void remover(AVL* registros, HEAP* fila){
    // Verifica se a AVL existe e se não está vazia 
    if(registros && !AVL_vazia(registros)){
        int ID;
        printf("Digite o ID do paciente para remover do registro: ");
        if(scanf("%d", &ID) != 1){
            printf("Erro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }

        // Verifica se o paciente não está na fila de espera para proceder com a remoção
        if(HEAP_busca_id(fila, ID) == false){
            if(AVL_remover(registros, ID)){
                printf("Paciente removido do registro.\n");
            }
            // Caso o paciente não exista na AVL
            else{
                printf("Erro: paciente não encontrado!\n");
            }
        }

        // Caso o paciente ainda esteja na fila
        else{
            printf("Erro: paciente ainda não foi atendido!\n");
        }
    }
    else printf("Erro: registo de pacientes está vazio!\n"); 
}

void listar(AVL* registros){
    // Verificação
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

void buscar(AVL* registros){
    // Verificação
    if(registros != NULL && !AVL_vazia(registros)){
        int ID;
        printf("Digite o ID do paciente a ser buscado no registro: ");
        if(scanf("%d", &ID) != 1){
            printf("Erro: ID inválido!\n");
            while(getchar() != '\n');
            return;
        }

        // Busca (bônus: mostra o status do paciente, ou seja, se ele está aguargando na fila e qual sua prioridade ou se já saiu do hospital)
        PACIENTE* p = AVL_buscar(registros, ID);
        if(p != NULL){
            printf("Paciente encontrado: ");
            PACIENTE_imprimir(p);
            if(PACIENTE_get_prioridade(p) != -1 && PACIENTE_get_chegada(p) != -1){
                printf("Status: presente na fila do hospital em estado ");
                int prioridade = PACIENTE_get_prioridade(p);
                switch(prioridade){
                    case 1: printf("de emergência."); break;
                    case 2: printf("muito urgente."); break;
                    case 3: printf("urgente."); break;
                    case 4: printf("pouco urgente."); break;
                    case 5: printf("não urgente."); break;
                }
            }
            else{
                printf("Status: paciente não está presente no hospital no momento.");
            }
        }
        else{
            printf("Paciente não encontrado no registro.");
        }
    }

    // Reporta se não for possível realizar a busca
    else{
        if(registros == NULL) printf("Erro: o arquivo de registros não existe!\n");
        else if(AVL_vazia(registros)) printf("O arquivo de registros está vazio.\n");
    }
}

void mostrar_fila(HEAP* fila){
    // Verificação
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

void dar_alta(HEAP* fila){
    // Tira o paciente da fila de espera
    if(fila != NULL && !HEAP_vazia(fila)){
        PACIENTE* p = HEAP_remover(fila);
        printf("Paciente \"%s\" (ID: %d) chamado(a) para atendimento.\n", PACIENTE_get_nome(p), PACIENTE_get_ID(p));
        PACIENTE_set_chegada(p, -1);
        PACIENTE_set_prioridade(p, -1);
    }

    // Reporta se fila de espera não existir ou estiver vazia
    else{
        if(fila == NULL) printf("Erro: fila de espera não existe!\n");
        else if(HEAP_vazia(fila)) printf("Erro: fila de espera está vazia!\n");
    }
}


int main(){
    // Declara os registros (AVL) e fila (HEAP)
    AVL* registros = NULL;
    HEAP* fila = NULL;
    contador = 0;

    // Cria as estruturas vazias para carregar o conteudo do save file delas ou para iniciá-las vazias caso ainda não exista save file
    registros = AVL_criar();
    fila = HEAP_criar();

    /*
    // Tenta abrir o save file
    FILE* arquivo_savefile = fopen("arquivo.bin", "rb");

    // Se existir save file
    if(arquivo_savefile != NULL){
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
    */

    // -------------------------------------------------

    printf("Sistema do pronto-socorro iniciado. Selecione uma das opções:\n");
    menu();
    bool flag = 0;
    while(!flag){
        printf("\nDigite uma ação de 1 a 8: ");
        int acao;
        if(scanf("%d", &acao) == 1){
            printf("\n");
            switch(acao){
                case 1: registrar(registros, fila); break;
                case 2: remover(registros, fila); break;
                case 3: listar(registros); break;
                case 4: buscar(registros); break;
                case 5: mostrar_fila(fila); break;
                case 6: dar_alta(fila); break;
                case 7: menu(); break;
                case 8: flag = 1; break;
                default: printf("Comando não encontrado, digite um número de 1 a 8.\n");
            }
        }
        else{
            printf("Entrada inválida. Digite apenas números no menu.\n");
            while(getchar() != '\n');
        }
    }

    // -------------------------------------------------

    // Chama função SAVE para salvar os dados em disco
    //SAVE(registros, fila, contador);

    // Limpa memória do programa
    AVL_apagar(&registros);
    HEAP_apagar(&fila);

    printf("Fim do programa.\n");
    return 0;
}