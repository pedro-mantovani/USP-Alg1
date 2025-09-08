# Introdução
O projeto consiste na criação de um sistema para o pronto socorro.

Para isso usaremos 3 TADs:
1. Lista dinâmica para a listagem dos pacientes
2. Fila para a triagem
3. Pilha para o histórico médico

Esses TADs serão usados em um sitema com a seguinte interface:
1. Registrar paciente
2. Dar alta ao paciente
3. Adicionar procedimento ao histórico médico
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Sair

# Tipos Abstratos de Dados

## Pilha - Histórico médico
Para o histórico médico usaremos um TAD pilha. Para esse caso ela é a mais recomendada, pois as operações serão utilizadas no método LIFO - Last-In, First-Out, ou seja o último procedimento realizado será o primeiro a ser modificado/descartado.

Nesse caso, apesar das especificações do problema limitarem os procedimentos a 10, alocar estaticamente esse histórico desperdiçaria muita memória, visto que cada registro de procedimento terá 100 bytes (100 caracteres), assim, o histórico de cada um dos pacientes ocuparia 1000 bytes.

Por outro lado, alocar dinâmicamente, ocupa um pouco mais de memórica para cada procedimento (8 bytes a mais por conta do ponteiro), mas isso representa menos de 10% cada elemento do histórico, ou seja, esse método só gastaria mais memória que a alocação estática nos casos que o paciente realiza 10 procedimentos, o que dificilmente será a maioria dos casos.

# Interface

# Autores
Pedro Otavio Mantovani
