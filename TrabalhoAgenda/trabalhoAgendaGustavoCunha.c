#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AlocaBuffer();
void MostraMenu();
void AdicionaPessoa();
void RemovePessoa();
void BuscarPessoa();
void ListarPessoas();

//Como eu vou ter que ficar acessando pBuffer por referência em todas funções, vou fazer ela um ponteiro global;
void *pBuffer;
// buffer[0] => escolha do menu;
// buffer[1] => numero de pessoas;
// buffer[2] => 0 ou 1 para bolleanos;
// buffer[3] => i, usado em loops;
// buffer[4] => j, usado em loops;

//Banco de dados:
void *pAgenda;

int main() {
    AlocaBuffer();
    pAgenda = ( char * )calloc(1, ( sizeof( char ) *50 ) * 100 );

    while ( 1 ) {
        
        MostraMenu();
        
        switch ( ( ( int * ) pBuffer )[ 0 ] ) {
            case 1:
                AdicionaPessoa();
                break;
            case 2:
                RemovePessoa();
                break;
            case 3:
                BuscarPessoa();
                break;
            case 4:
                ListarPessoas();
                break;
            case 5:
                free(pBuffer);
                return 0;
            default:
                printf("Opção inválida\n");
        }
    }

    return 0;
}

void MostraMenu(){
        printf( "1- Adicionar Pessoa\n" );
        printf( "2- Remover Pessoa\n" );
        printf( "3- Buscar Pessoa\n" );
        printf( "4- Listar todos\n" );
        printf( "5- Sair\n" );

        // Coloca a escolha do usuário no endereço de memória da escolha
        scanf( "%d",( ( int * ) pBuffer ));

        //Pra tirar o /n
        getchar();
}

void AlocaBuffer() {
    //Implicitamente, o tamanho de cada pessoas é 50, e o máximo de pessoas é 100
    if ( ( pBuffer = ( void* )calloc( 1,
        ( sizeof( int ) ) + //Escolha do usuário; 
        ( sizeof( int ) ) + // Contador de pessoas;
        ( sizeof( int ) ) + // 0 ou 1 para bolleanos;
        ( sizeof( int ) ) + // i, usado em loops;
        ( sizeof( int ) ) + // j, usado em loops;
        (sizeof( char ) * 5000) // espaço pra armazenar pessoas por um curto periodo de tempo;
    ) ) == NULL ) { 
        printf( "Erro ao alocar memória\n" );
        exit( EXIT_FAILURE );
    }

}

void AdicionaPessoa() {
    if ( ( ( int * )pBuffer )[ 1 ] >= 100 ) {
        printf( "Agenda cheia!\n" );
        return;
    }

    printf( "Digite o nome da pessoa: " );
    
    // Usa o fgets para pegar uma palavra de 50 char e armazenar na agenda usando o contador (buffer[1]) para controlar qual pessoa é;
    fgets( ( char * )pAgenda + ( ( ( int * ) pBuffer )[ 1 ] * 50 ), 50, stdin ); 

    //Cuida do \n; Caso achar o \n troca ele por \0;
    if (*( ( char * ) pAgenda + ( ( ( int * ) pBuffer )[ 1 ] * 50 ) + 
        strlen( ( char * )pAgenda + ( ( ( int * ) pBuffer )[ 1 ] * 50 ) ) - 1 ) == '\n' ) 
    {
        *( ( char * ) pAgenda + ( ( ( int * )pBuffer )[ 1 ] * 50 ) + 
        strlen( ( char * ) pAgenda + ( ( ( int * )pBuffer )[ 1 ] * 50 ) ) - 1 ) = '\0';
    }

    ( ( int * ) pBuffer )[ 1 ]++; //Incrementa o número de pessoas;
    printf( "Pessoa adicionada\n" );
}


void RemovePessoa() {
    //Checa pra ver se o contador de pessoas é 0 (agenda vazia)
    if ( ( ( int * ) pBuffer )[ 1 ] <= 0 ) {
        printf( "Não há pessoas para remover\n" );
        return;
    }

    printf( "Digite o nome da pessoa a remover: " );
    
    fgets( ( char * ) pBuffer + sizeof( int ) * 4, 50, stdin );

    ( ( int * ) pBuffer )[ 2 ] = 0;

    // For para iterar pela agenda
    for ( ( ( int * ) pBuffer )[ 3 ] = 0; 
          ( ( int * ) pBuffer )[ 3 ] < ( ( int * ) pBuffer )[ 1 ]; 
          ( ( int * ) pBuffer )[ 3 ]++ ) 
    {
        //Comparação pra ver se achou o nome
        if ( strcmp( ( char * ) pAgenda + ( ( ( int * ) pBuffer )[ 3 ] * 50 ), 
                     ( char * ) pBuffer + sizeof( int ) * 2 ) == 0 ) 
        {
            ( ( int * ) pBuffer )[ 2 ] = 1;
            break;
        }
    }

    // Caso não encontrar a pessoa
    if ( !( ( int * ) pBuffer )[ 2 ] ) {
        printf( "Pessoa não encontrada\n" );
        return;
    }

    // For para iterar pela agenda até a pessoas que foi removida;
    for ( ( ( int * ) pBuffer )[ 4 ] = ( ( int * ) pBuffer )[ 3 ]; // j = i
          ( ( int * ) pBuffer )[ 4 ] < ( ( int * ) pBuffer )[ 1 ] - 1; // j < numero de pessoas
          ( ( int * ) pBuffer )[ 4 ]++) // j++
    {
        strcpy( ( char * ) pAgenda + ( ( ( int * ) pBuffer )[ 4 ] * 50 ), //
                ( char * ) pAgenda + ( ( ( ( int * ) pBuffer )[ 4 ] + 1 ) * 50 ) );
    }

    ( ( int * ) pBuffer )[ 1 ]--; // Decrementa o numero de pessoas

    printf( "Pessoa removida!\n" );
}

void BuscarPessoa() {
    // Implementar a função de buscar pessoa
    printf( "Função de buscar pessoa ainda não implementada\n" );
}

void ListarPessoas() {
    // Implementar a função de listar pessoas
    printf( "Função de listar pessoas ainda não implementada\n" );
}

