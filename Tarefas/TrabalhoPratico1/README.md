# Trabalho Prático 1
## Gustavo Cunha Kneip - AED_2024-1 - 23/06/2024

## Problema:
Criar um programa que simula o processo de venda de uma banca de limonada. Ele deve funcionar da seguinte forma:
 - O programa receberá um vetor de inteiros, representando o pagamento de cada cliente como um dos valores do vetor;
 - O cliente pode pagar em notas de $5, $10, $20;
 - O programa deve verificar se o dono da banca de limonada possui notas suficiente para dar o troco aos seus clientes;
## Soluções
- [Solução realizada em aula](./TrabalhoPratico1/CodigoEmAula/Tarefa2-Leetcode860-GustavoCunhaKneip.c);
- [Solução finalizada em casa](./TrabalhoPratico1/CodigoFinalizado/Tarefa2-Leetcode860-GustavoCunhaKneip-Finalizado.c);
## Testes:
Foram realizados testes com os seguintes vetores (utlizando a IDE do Leetcode):
- [5,5,5,10,20] - Esperado: true; Resultado: true;
- [5,5,10,10,20] - Esperado: false; Resultado: false;
- [5,5,5,10,20,10,20] - Esperado: false; Resultado: false;
## O que funcionou:
O código faz tudo o que foi pedido pelo problema, rodou tranquilamente em todos os testes do Leetcode, rodados depois de mandar o programa usando o **SUBMIT**;
## O que não funcionou:
Como comentado anteriormente, o codigo faz o que foi pedido. Uma coisa interessante de se comentar é que se trocar a ordem dos `if's` das linhas **46** e **49** do arquivo 
[`Tarefa2-Leetcode860-GustavoCunhaKneip-Finalizado.c`](./TrabalhoPratico1/CodigoFinalizado/Tarefa2-Leetcode860-GustavoCunhaKneip-Finalizado.c) o programa não roda, pois gastamos mais notas de 5
do que o esperado. Porém essa ainda seria uma solução válida, pois o dono da banca pode escolher das 3 notas de $5 como troco para $20. Acho que isso não foi pensado por quem desenvolveu o problema.
