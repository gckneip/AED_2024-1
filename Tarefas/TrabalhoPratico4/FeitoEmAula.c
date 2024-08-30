#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int difficulty;
    int profit;
} job;


int maxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize );
void swap(job *jobs,int pi,int valor);
void organizaDic(job *jobs, int low, int pi, int high);
int procuraJob(int worker, job *jobs);

int main(void){

    //teste 1:
    int difficulty[5] = {2,4,6,8,10};
    int difficultySize = 5;
    int profit[5] = {10,20,30,40,50};
    int profitSize = 5;
    int workers[4] = {4,5,6,7};
    int workersSize = 4;

    int teste1 = maxProfitAssignment(difficulty,difficultySize,profit,profitSize,workers,workersSize);
    printf("Teste1: %d\n",teste1);

    //teste 2:
    int difficulty2[3] = {85,47,57};
    int difficultySize2 = 3;
    int profit2[3] = {24,66,99};
    int profitSize2 = 3;
    int workers2[3] = {40,25,25};
    int workersSize2 = 3;

    int teste2 = maxProfitAssignment(difficulty2,difficultySize2,profit2,profitSize2,workers2,workersSize2);
    printf("Teste2: %d\n",teste2);

    return 1;
}

int maxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize ) {
    int i = 0, soma;
    
    // CUIDADO, a dificuldade deve manter-se no mesmo indice do seu profit equivalente

    //Talvez criar um array temporario como um dicionario? Armazenando o valor dificuldade + profit?
    job *jobs = ( job * )malloc( difficultySize*sizeof( job ) );

    for( i = 0; i < difficultySize; i++ ){
        jobs[i].difficulty = difficulty[i];
        jobs[i].profit = profit[i];
    }

    for( i = 0; i < difficultySize; i++ ){
        printf( "Dificuldade do job %d: %d\n",i,jobs[i].difficulty );
        printf( "Profit do job %d: %d\n",i,jobs[i].profit );
    }

    //Organizar o dataset de Profit+Difficulty, baseado na Difficuldade
    //Se o dataset não estiver organizado, o binary search não funcionará
    organizaDic( jobs, 0, difficultySize/2, difficultySize );

    //executar a busca binaria, baseado no valor de cada worker, procurar o job com uma dificuldade aceitavel e com maior profit
    for(i = 0; i < workerSize; i++){
        soma += procuraJob(worker[i],jobs);
    }

    return profitSize;
}

// Função usada no quick sort para trocar o pivo pelo valor menor/maior que ele
void swap(job *jobs,int pi,int valor){
    job temp = jobs[pi];
    jobs[pi] = jobs[valor];
    jobs[valor] = temp;
}

//tentar implementar um quick sort pro novo dic
void organizaDic(job *jobs, int low, int pi, int high){
    
}

//com o dic ordenado, fazer um binary search pra pegar o job com o maior profit
int procuraJob(int worker, job *jobs){
    
}