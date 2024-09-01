#include <stdio.h>
#include <stdlib.h>

typedef struct { 
    int difficulty;
    int profit;
} job;

int compareJobs( const void* a, const void* b );
int maxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize );
int procuraJob( int *worker, job *jobs, int difficultySize, int workerSize );

/* ==================== Main
    Function called when you run the program. Calls other functions.
==================== */
int main( void ) { 
    int difficulty[ 5 ] =  { 2, 4, 6, 8, 10 };
    int profit[ 5 ] =  { 10, 20, 30, 40, 50 };
    int workers[ 4 ] =  { 4, 5, 6, 7 };

    int result1 = maxProfitAssignment( difficulty, 5, profit, 5, workers, 4 );
    printf( "Test 1: %d\n", result1 );

    int difficulty2[ 3 ] =  { 85, 47, 57 };
    int profit2[ 3 ] =  { 24, 66, 99 };
    int workers2[ 3 ] =  { 40, 25, 25 };

    int result2 = maxProfitAssignment( difficulty2, 3, profit2, 3, workers2, 3 );
    printf( "Test 2: %d\n", result2 ); 

    return 0;
}

/* ==================== maxProfitAssignment
    Function to get the maximum profit of a job assignment
    @param difficulty: the difficulty of each job
    @param difficultySize: the number of jobs
    @param profit: the profit of each job
    @param profitSize: the number of profits
    @param worker: the ability of each worker
    @param workerSize: the number of workers
    @return: the maximum profit
*/
int maxProfitAssignment( int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize ) { 
    int totalProfit = 0;
    job* jobs = ( job* )malloc( difficultySize * sizeof( job ) );

    for ( int i = 0; i < difficultySize; i++ ) { 
        jobs[ i ].difficulty = difficulty[ i ];
        jobs[ i ].profit = profit[ i ];
    }

    qsort( jobs, difficultySize, sizeof( job ), compareJobs );

    for ( int i = 1; i < difficultySize; i++ ) { 
        if ( jobs[ i ].profit < jobs[ i - 1 ].profit ) { 
            jobs[ i ].profit = jobs[ i - 1 ].profit;
        }
    }

    totalProfit = procuraJob( worker, jobs, difficultySize, workerSize );

    free( jobs );

    return totalProfit;
}

/* ==================== procuraJob
    Function to find the job with the highest profit
    also, the difficulty of the job must be less than or equal to the worker's ability.
    The function returns the total profit of the jobs
    @param worker: the ability of each worker
    @param jobs: the array of jobs
    @param difficultySize: the number of jobs
    @param workerSize: the number of workers
    @return: the total profit
*/
int procuraJob( int *worker, job *jobs, int difficultySize, int workerSize ) { 
    int totalProfit = 0;

    for ( int i = 0; i < workerSize; i++ ) { 
        int left = 0, right = difficultySize - 1;
        int maxProfit = 0;

        while ( left <= right ) { 
            int mid = left + ( right - left ) / 2;
            if ( jobs[ mid ].difficulty <= worker[ i ] ) { 
                maxProfit = jobs[ mid ].profit;  
                left = mid + 1;  
            } else { 
                right = mid - 1;  
            }
        }
        totalProfit += maxProfit; 
    }

    return totalProfit;
}

/* ==================== compareJobs
    Function to compare two jobs by their difficulty
    @param a: the first job
    @param b: the second job
    @return: the difference between the two jobs' difficulties
*/
int compareJobs( const void* a, const void* b ) { 
    return ( ( job* )a )->difficulty - ( ( job* )b )->difficulty;
}
