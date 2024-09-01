# Trabalho Prático 4
## Gustavo Cunha Kneip - AED_2024-1 - 01/09/2024
## Problema:
Criar um programa que ao receber 3 arrays:
  - Profit: com o valor do lucro de cada trabalho (trabalho = index);
  - Difficulty: com a dificuldade de cada trabalho (trabalho = mesmo index do Profit);
  - WOrkes: Trabalhadores = index, cada valor do trabalhador indica qual trabalho ele pode pegar;
Indique qual é o maximo de lucro que é possível obter;
## Soluções
- [Solução realizada em aula](./FeitoEmAula.c;
- [Solução finalizada em casa (sozinho)](./FeitoEmCasa-sozinho.c);
- [Solução finalizada em casa (ajuda do copilot)](./FeitoEmCasa-ajuda.c);
## Testes:
### Teste 1:
    difficulty[5] = {2, 4, 6, 8, 10};
    profit[5] = {10, 20, 30, 40, 50};
    workers[4] = {4, 5, 6, 7};

    Resultado: 100
### Teste 2:
    difficulty2[3] = {85, 47, 57};
    profit2[3] = {24, 66, 99};
    workers2[3] = {40, 25, 25};

    Resultado: 0

### Teste 3:
  Teste grande demais para colocar aqui, olhar teste 56/60 do leetcode;
## O que funcionou:
- **Durante a aula**: Durante a aula implementei a prate de organizar cada trabalho com seu lucro e sua dificuldade, em uma `struct` chamada `job`; Criei o escopo para as funções de sort e de busca binária, porém não consegui implementar o quick sort como gostaria;
- **Em casa (sozinho)**: Em casa, terminei de implementar o quick sort e o binary search, porém, o código ainda não passava de todos os test cases, pois excedia os limites de tempo;
  **Em casa (ajuda)**: Após ativar o copilot e pedir ajuda, ele me indicou a função pronta do `stdlib.h>`, `qsort`, que otimizou a minha função de sort e fez com que o código passase em todos os teste;
## O que não funcionou:
- **Durante a aula**: Durante a aula, apresentei dificuldade em perceber qual estrutura de dados usar. Comecei com uma lista pois achei que facilitaria na remoção da string, porém a complexidade do código me fez pensar que essa não era a solução. Então, tentei implementar uma loógica de pilhas, porém não lembrava exatamente como montar as funções, por isso elas ficaram com algums erros (aleḿ disso não desaloquei a memória da pilha nem da string dentro dela); Em questão de lógica, durante a aula tentei fazer algo que percorria a string enquanto adicionava os char a uma string, a idéia era usar o pop para excluir o caracter anterior ao perceber alguma das sequência AB ou BA; Porém durante a aula minha lógica olhava para os caracteres no momento para ver se era interessante remover AB ou BA, e não na string inteira, o que causou erros no meu resultado;
- **Em casa**: consegui arrumar o que faltava em relação a lógica; Minha única duvida era na possivel criação de uma substring AB após remover BA ou vice-versa, porém uma das resposta do leetcode me explicou que isso não é possível;
## [Vídeo explicativo](https://youtu.be/2ivdoDXYhhU)

