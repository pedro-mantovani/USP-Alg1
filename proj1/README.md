# Introdução
O projeto consiste na criação de um sistema para o pronto socorro.

Para isso usaremos 3 estruturas de dados principais:
1. Lista para a registro dos pacientes
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
8. Mostrar menu
9. Sair

# Tipos Abstratos de Dados

## Pilha - Histórico médico
Para o histórico médico usaremos um TAD pilha. Para esse caso ela é a mais recomendada, pois as operações serão utilizadas no método LIFO - Last-In, First-Out, ou seja o último procedimento realizado será o primeiro a ser modificado/descartado.

Nesse caso, apesar das especificações do problema limitarem os procedimentos a 10, alocar estaticamente esse histórico desperdiçaria muita memória, visto que cada registro de procedimento terá 100 bytes (100 caracteres), assim, o histórico de cada um dos pacientes ocuparia 1000 bytes.

Por outro lado, alocar dinâmicamente, ocupa um pouco mais de memórica para cada procedimento (8 bytes a mais por conta do ponteiro), mas isso representa menos de 10% cada elemento do histórico, ou seja, esse método só gastaria mais memória que a alocação estática nos casos que o paciente realiza 10 procedimentos, o que dificilmente será a maioria dos casos.

## Fila - Triagem
Para construir uma fila de espera para a triagem, foi utilizado um TAD fila (método FIFO - First-In, First-Out) com implementação sequencial e circular.

Esse modelo de fila foi escolhido uma vez que, além da fila ser limitada, o que pode ser facilmente controlado com uma implementação não encadeada, o modelo sequencial circular garante uma implementação muito mais simplificada, eficiente e econômica do que uma encadeada não circular. Isso porque, por mais que a fila receba os pacientes diretamente da lista, não sendo necessário alocar memória para eles novamente, em uma fila encadeada, seria necessário alocar memória para cada nó. Utilizando a fila sequencial, isso não se faz mais necessário, economizando memória. Além disso, em uma implementação linear, todos os integrantes da fila são deslocados após uma operação de remoção para preencher o espaço vazio. A implementação circular evita que isso aconteça, deslocando apenas os indicadores "início" e "fim" e utilizando operações de resto para caso o indicador "fim" ultrapasse o último índice.

## Item - Paciente
O TAD item, para este projeto, foi adaptado para armazenar um paciente e realizar operações sobre ele. Na struct, são guardados o ID, o nome e a pilha que corresponde ao seu histórico médico. As operações também estão devidamente adaptadas para lidar com todos esses dados.

## Item - Histórico
Outro TAD de um tipo genérico de item implementado foi um TAD histórico (hist), ele consiste em uma string de 100 caracteres que representam um procedimento, sendo que uma pilha de hist forma um histórico completo do paciente.

# Interface
A interface foi feita de maneira amigável, sempre reportando erros, entradas inválidas e outros usos inválidos comuns como remover um paciente que já não existe ou cadastrar um paciente que já está na fila de espera.

# Autores
Pedro Otavio Mantovani - 16896987
Clara Santos de Melo - 16860650
Maria Fernanda Maia de Souza Pinto - 16889342
