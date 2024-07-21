# Trabalho Agenda pBuffer
## Gustavo Cunha Kneip - AED_2024-1 - 23/06/2024
## Problema:
Faça uma agenda com o seguinte menu:
1. Adicionar Pessoa (Nome, Idade, email)
2. Remover Pessoa
3. Buscar Pessoa
4. Listar todos
5. Sair

O desafio é não poder criar variáveis e sim um buffer de memória (void *pBuffer). Nisso vocês terão que fazer o trabalho que o Sistema Operacional faz para vocês ao organizar a memória.

**Regras:**

1. Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.

   1.1 Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.

   1.2 Exemplo do que não pode: `int c; char a; int v[10]; void Funcao(int parametro)`

3. Não pode usar struct em todo o programa.

4. Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.

   3.1 Implementar a base de dados da agenda usando lista duplamente ligada.

   3.2 Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um `malloc` para cada nodo.

## Soluçã0
- [Trabalho Agenda pBuffer](./trabalhoAgendaGustavoCunha.c);
## Testes:
Foram realizados testes com as intruçẽos abaixo:
### Teste 1:
```
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  1
  
  Digite o nome: Gustavo
  Digite o email: gustavo
  Digite a idade: 35
  ############# ADICIONADO ############
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  4
  ############ COMEÇO AGENDA ############
  ##################################
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############ FIM AGENDA ############
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  1
  
  Digite o nome: Antonio
  Digite o email: antonio
  Digite a idade: 45
  ############# ADICIONADO ############
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  4
  ############ COMEÇO AGENDA ############
  ##################################
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ##################################
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############ FIM AGENDA ############
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  1
  
  Digite o nome: Duda
  Digite o email: mederios
  Digite a idade: 45
  ############# ADICIONADO ############
  Nome: Duda
  Email: mederios
  Idade: 45
  ##################################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  4
  ############ COMEÇO AGENDA ############
  ##################################
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ##################################
  Nome: Duda
  Email: mederios
  Idade: 45
  ##################################
  ##################################
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############ FIM AGENDA ############
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  2
  
  Digite o nome: Duda
  ############ REMOVIDO ##########
  Nome: Duda
  Email: mederios
  Idade: 45
  ##################################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  4
  ############ COMEÇO AGENDA ############
  ##################################
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ##################################
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############ FIM AGENDA ############
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  3
  
  Digite o nome: Antonio
  ############# BUSCA ############
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  3
  
  Digite o nome: Duda
  ############## NAO ENCONTRADO ###################
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  4
  ############ COMEÇO AGENDA ############
  ##################################
  Nome: Antonio
  Email: antonio
  Idade: 45
  ##################################
  ##################################
  Nome: Gustavo
  Email: gustavo
  Idade: 35
  ##################################
  ############ FIM AGENDA ############
  ############## MENU ###################
  1- Adicionar Pessoa
  2- Remover Pessoa
  3- Buscar Pessoa
  4- Listar todos
  5- Sair
  #################################
  5
  ############## SAINDO ###################
```
## O que funcionou:
O código segue todas as especificações do enunciado, sem nenhum erro de memória;
As funções Push e Pop tratam a agenda como uma heap, e são utilizadas para passar os dados entre
ela e a heap auxiliar, mantendo assim a consistência da fila ordenada (FIFO);
## O que melhorar:
Possivel problemas com varios contatos (10+), não foi testado devido ao prazo de entrega;
Uso de memória pode ser melhorado, alguns alocamentos de memórias são feitos antes do necessário;
Tanto email quanto nome sempre ocuparão 50 bytes, possivel implementar alocação dinâmica de strings;

## [Vídeo explicativo](https://youtu.be/eDySrfGXwfk)

