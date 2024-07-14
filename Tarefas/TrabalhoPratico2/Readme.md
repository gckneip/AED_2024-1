# Trabalho Prático 2
## Gustavo Cunha Kneip - AED_2024-1 - 14/07/2024
## Problema:
Criar um programa que ao receber uma string, um valor X e um valor Y, consegue o maior valor possivel realizando as seguintes operações:
- Remover ab e ganhar X pontos;
- Remover ba e ganhar Y pontos;
## Soluções
- [Solução realizada em aula](./CodigoEmAula/Tarefa3-Leetcode1717-GustavoCunhaKneip.c);
- [Solução finalizada em casa](./CodigoFinalizado/Tarefa3-Leetcode1717-GustavoCunhaKneip-Finalizado.c);
## Testes:
Foram realizados testes com os seguintes vetores (utlizando a IDE do Leetcode):
- s= "cdbcbbaaabab", x = 4, y = 5 - Esperado: 19; Resultado: 19;
- s = "aabbaaxybbaabb", x = 5, y = 4 - Esperado: 20; Resultado: 20;
- s = "aaabb...aakabbtz"(string completa no leetcode), x = 3009 , y = 8439 - Esperado: 67206777; Resultado: 67206777;
## O que funcionou:
- **Durante a aula**: Criei uma estrutura de pilhas que funcionava para o que era preciso; Rodou em alguns casos de teste, porém não em todos;
- **Em casa**: Ao chegar em casa consertei as funções de Push e Pop que havia criado para a pilha, aleḿ de acertar a lógica para remover primeiro a sequência com maior valor de toda a palavra e depois ir para a próxima; Todos os testes do leetcode rodaram, embora o runtime tenha sido horrivel; Também criei uma função main no VSCode e testei com Valgrind para possivéis erros de memória (os que foram encontrados foram corrigidos);
## O que não funcionou:
- **Durante a aula**: Durante a aula, apresentei dificuldade em perceber qual estrutura de dados usar. Comecei com uma lista pois achei que facilitaria na remoção da string, porém a complexidade do código me fez pensar que essa não era a solução. Então, tentei implementar uma loógica de pilhas, porém não lembrava exatamente como montar as funções, por isso elas ficaram com algums erros (aleḿ disso não desaloquei a memória da pilha nem da string dentro dela); Em questão de lógica, durante a aula tentei fazer algo que percorria a string enquanto adicionava os char a uma string, a idéia era usar o pop para excluir o caracter anterior ao perceber alguma das sequência AB ou BA; Porém durante a aula minha lógica olhava para os caracteres no momento para ver se era interessante remover AB ou BA, e não na string inteira, o que causou erros no meu resultado;
- **Em casa**: consegui arrumar o que faltava em relação a lógica; Minha única duvida era na possivel criação de uma substring AB após remover BA ou vice-versa, porém uma das resposta do leetcode me explicou que isso não é possível;
## [Vídeo explicativo](https://youtu.be/2ivdoDXYhhU)

