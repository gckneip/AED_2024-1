# Trabalho Prático 4
## Gustavo Cunha Kneip - AED_2024-1 - 01/09/2024
## Problema:
Criar um programa que ao receber 3 arrays:
  - Profit: com o valor do lucro de cada trabalho (trabalho = index);
  - Difficulty: com a dificuldade de cada trabalho (trabalho = mesmo index do Profit);
  - Workes: Trabalhadores = index, cada valor do trabalhador indica qual trabalho ele pode pegar;
Indique qual é o maximo de lucro que é possível obter;
## Soluções
- [Solução realizada em aula](./FeitoEmAula.c);
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
  **Em casa (ajuda)**: Após ativar o copilot e pedir ajuda, ele me indicou a função pronta do `stdlib.h`, `qsort`, que otimizou a minha função de sort e fez com que o código passase em todos os teste;
## O que não funcionou:
- **Durante a aula**: Durante a aula, sinto que identifiquei a solução do problema rapidamente, porém, tive dificuldade de implementar as funções de sort de cabeça. Devido o cansaço do fim do semestre, também desisti cedo e decidi terminar em casa;
- **Em casa**: Consegui implementar as funções no sábado, com a cabeça mais fria, porém não consegui passar por todos os teste mesmo assim. NO domingo, decidi pedir ajuda do copilot, para não entregar um código que não funciona. Além disso, meu Valgrind ainda não funciona direito, mesmo com o programa não utilizando nada muito chique em questão de memória (apenas 1 malloc e 1 free);
## [Vídeo explicativo](https://youtu.be/0OswvIWyxjc)

