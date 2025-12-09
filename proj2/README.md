# Projeto 2: Sistema de Pronto Socorro (Versão 2.0)

## Introdução
Este projeto consiste na evolução do sistema de gerenciamento para um pronto socorro. Diferente da versão anterior, o foco agora é a eficiência computacional.

Para isso, utilizamos as seguintes estruturas de dados:
1.  **Árvore AVL** para o registro e busca de pacientes (substituindo a Lista Encadeada).
2.  **Heap** para a fila de espera com prioridade (substituindo a Fila).
3.  **Pilha Dinâmica** para o histórico médico (mantida).

## Interface do Sistema
Agora o sistema possui as seguintes opções:

1.  **Registrar paciente:** Insere na base de dados e na fila de espera (se aplicável).
2.  **Remover paciente:** Remove permanentemente do registro (apenas se não estiver na fila).
3.  **Listar pacientes:** Exibe todos os registros ordenados por ID.
4.  **Buscar paciente por ID:** Busca otimizada ($O(\log n)$) para exibir dados e status.
5.  **Mostrar fila de espera:** Exibe a fila ordenada por prioridade (e ordem de chegada como desempate).
6.  **Dar alta ao paciente:** Retira o paciente da fila de espera, mantendo seu registro e histórico médico.
7.  **Adicionar procedimento ao histórico médico.**
8.  **Desfazer procedimento do histórico médico.**
9.  **Mostrar menu.**
10. **Sair:** Salva os dados em disco e encerra.

---

# Tipos Abstratos de Dados (TADs)

## 1. Árvore AVL - Registro de Pacientes
Para armazenar os registros dos pacientes, substituímos a lista encadeada por uma Árvore AVL.

### Comparação de Eficiência (Pior Caso)

| Operação | Lista Encadeada (Não Ordenada) | Árvore AVL (Balanceada) |
| :--- | :--- | :--- |
| **Busca** | $O(n)$ | $O(\log n)$ |
| **Inserção** | $O(1)$ | $O(\log n)$ |
| **Remoção** | $O(n)$ | $O(\log n)$ |
| **Espaço** | $O(n)$ | $O(n)$ |

* **Funcionamento:** A AVL garante que a altura da árvore seja sempre logarítmica em relação ao número de nós. Isso assegura que as operações de busca, inserção e remoção ocorram em tempo **$O(\log n)$**. A ordenação é feita pelo ID do paciente.

## 2. Heap (Fila de Prioridade)
A triagem não segue mais a ordem puramente de chegada (FIFO). O atendimento agora é baseado em gravidade clínica. Para isso, utilizamos uma **Min-Heap**.

* **Critérios de Prioridade:**
    1.  **Emergência**
    2.  **Muito Urgente**
    3.  **Urgente**
    4.  **Pouco Urgente**
    5.  **Não Urgente**
* **Desempate:** Ordem de chegada
* **Eficiência:** A inserção e a remoção do topo da Heap ocorrem em $O(\log n)$, e o acesso ao próximo paciente a ser atendido é imediato ($O(1)$).

## 3. Pilha - Histórico Médico
Foi mantida pois as operações são $O(1)$

## 4. Módulo I/O - Persistência
O módulo foi adaptado para salvar também a ordem de chegada e receber os dados de uma AVL ao invés de uma lista.

---

# Estruturas Auxiliares

## Item - Paciente
A struct do paciente foi expandida para suportar as novas regras. Além de `ID`, `Nome` e `Histórico`, agora armazena:
* `Prioridade`: Inteiro de 1 a 5.
* `Chegada`: Contador sequencial para desempate na fila.

## Item - Histórico (Hist)
Um TAD simples que encapsula uma string de até 100 caracteres, representando um procedimento médico. O mesmo do projeto passado.

---

# Instruções de compilação

Utilize o comando `make` para compilar, ou compile manualmente com:
```bash
    gcc main.c IO.c paciente.c AVL.c heap.c hist.c pilha.c -o main -Wall
```

Para executar utilize `make run` ou `./main`

# Autores
**Pedro Otavio Mantovani - 16896987**  
**Clara Santos de Melo - 16860650**  
**Maria Fernanda Maia de Souza Pinto - 16889342**