#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack_t {
    char *palavra;
    char topo;
    int limite;
    int capacidade;
} Stack_t;

bool Push( Stack_t *pilha, char letra );
void Pop( Stack_t *pilha );
void ComecaPilha( Stack_t *pilha );
void FreePilha( Stack_t *pilha );
int MaximumGain( char* s, int x, int y );

/* 
==================== 
main

    Função principal do código, responsável
    por chamar as outras funções. Chama
    MaximumGain e printa o resultado;
==================== 
*/
int main() {
    char s[] = "aabbaaxybbaabb";
    int x = 4;
    int y = 5;

    int result = MaximumGain( s, x, y );

    printf( "%d\n", result );

    return 0;
}

/* 
==================== 
MaximunGain
        
    Recebe uma string e retorna o maior valor
    possivel após realizar as operações
    de aliminar AB ou BA; 
==================== 
*/
int MaximumGain( char* s, int x, int y ) {
    int i = 0;
    Stack_t pilha, outraPilha;
    int soma = 0;

    ComecaPilha( &pilha );
    ComecaPilha( &outraPilha );

    if ( y > x ) {
        while ( s[i] != '\0' ) {
            if ( pilha.limite > 0 && pilha.topo == 'b' && s[i] == 'a' ) {
                Pop( &pilha );
                soma += y;
            } else {
                Push( &pilha, s[i] );
            }
            i++;
        }

        i = 0;

        while ( i < pilha.limite ) {
            if ( outraPilha.topo == 'a' && pilha.palavra[i] == 'b' ) {
                Pop( &outraPilha );
                soma += x;
            } else {
                Push( &outraPilha, pilha.palavra[i] );
            }
            i++;
        }
    } else {
        while ( s[i] != '\0' ) {
            if ( pilha.topo == 'a' && s[i] == 'b' ) {
                Pop( &pilha );
                soma += x;
            } else {
                Push( &pilha, s[i] );
            }
            i++;
        }

        i = 0;

        while ( i < pilha.limite ) {
            if ( outraPilha.topo == 'b' && pilha.palavra[i] == 'a' ) {
                Pop( &outraPilha );
                soma += y;
            } else {
                Push( &outraPilha, pilha.palavra[i] );
            }
            i++;
        }
    }

    FreePilha( &pilha );
    FreePilha( &outraPilha );

    return soma;
}

/* 
==================== 
ComecaPilha

    Receve uma endereço para uma variavel do tipo pilha
    e coloca os valores iniciais nela; 
==================== 
*/
void ComecaPilha( Stack_t *pilha ) {
    pilha->limite = 0;
    pilha->capacidade = 10;
    if( ( pilha->palavra = ( char * )malloc( sizeof( char ) * pilha->capacidade ) ) == NULL ){
        exit(EXIT_FAILURE);
    }
    pilha->topo = '\0';
}

/* 
==================== 
FreePilha
        
    Receve um endereço de pilha, verifica se  
    é NULL, caso não seja da free na lista 
    de char (palavra) dentro dela;
==================== 
*/
void FreePilha( Stack_t *pilha ) {
    if( pilha == NULL ) {
        return;
    }
    free( pilha->palavra );
}

/* 
==================== 
Push

    Função padrão de pilha, coloca um char
    para o topo da lista de chars (palavra)
    da pilha. Realoca memoria apena se necessário
    (alocação feita em lotes) 
==================== 
*/
bool Push( Stack_t *pilha, char letra ) {
    char *nova_palavra = NULL;
    if ( pilha->limite >= pilha->capacidade ) {
        pilha->capacidade *= 2;
        if( ( nova_palavra = realloc( pilha->palavra, sizeof( char ) * pilha->capacidade ) ) == NULL){
            exit(EXIT_FAILURE);
        }
        pilha->palavra = nova_palavra;
    }

    pilha->palavra[ pilha->limite ] = letra;
    pilha->limite++;
    pilha->topo = letra;

    return true;
}


/* 
==================== 
Pop

    Função padrão de pilha, deleta o char 
    que esta no topo da lista de chars (palavra)
    da pilha. Realoca memoria apena se necessário
    (alocação feita em lotes) 
==================== 
*/
void Pop( Stack_t *pilha ) {
    if ( pilha->limite == 0 ) {
        pilha->topo = '\0';
        return;
    }

    pilha->limite--;

    if ( pilha->limite > 0 ) {
        pilha->topo = pilha->palavra[ pilha->limite - 1 ];
    } else {
        pilha->topo = '\0';
    }

    if ( pilha->limite <= pilha->capacidade / 2 && pilha->capacidade > 10 ) {
        char * nova_palavra = NULL;
        pilha->capacidade /= 2;

        if ( ( nova_palavra = realloc( pilha->palavra, sizeof( char ) * pilha->capacidade ) ) == NULL ){
            exit(EXIT_FAILURE);
        }

        if ( nova_palavra != NULL || pilha->limite == 0 ) {
            pilha->palavra = nova_palavra;
        }
    }
}