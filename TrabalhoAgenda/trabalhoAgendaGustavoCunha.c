#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AlocaBuffer();
void MostraMenu(int *escolha);

void Push(void **pFirst, void **pLast);
void Pop(void **pFirst, void **pLast);

void AdicionaPessoa(void **pTemp);
void RemovePessoa();
void BuscarPessoa();

void ListarPessoas(void *current);
void Printar(void *temp);

void FreeMemory(void *temp, void *pFirst);

//Como eu vou ter que ficar acessando pBuffer por referência em todas funções, vou fazer ela um ponteiro global;
void *pBuffer;
//escolha: *( ( int* )pBuffer + ( sizeof( int ) * 0 ) );
//i: *( (int * ) pBuffer + ( sizeof( int ) * 1 ) ) ;
//temp_idade: *( ( int * ) pBuffer + ( sizeof(int) * 2 ) );
//First: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) );
//Last: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) ) );
//FirstTemp: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + 2*(sizeof( void*)) );
//LastTemp: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + 3*( sizeof( void* ) ) );
//temp_node: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + 4*( sizeof( void* ) ) );
//temp_node2: *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + 5*( sizeof( void* ) ) );
//temp_nome: *( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + 6 * ( sizeof( void* ) ) );
//temp_email: *( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + 6 * ( sizeof(void* ) ) + ( sizeof( char ) * 50 ) ) ;


//Banco de dados:
//nome: *( char * ) ( *( ( void ** )( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) ) )
//email: *( char * ) *( ( ( void ** )( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) + ( sizeof( char ) * 50 ) ) )
//idade: *( int * ) * ( ( ( void ** )( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) + ( sizeof( char ) * 50 ) * 2 ) )
//prox: ( void * ) * ( ( ( void ** )( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) + ( sizeof( char ) * 50 ) * 2 + sizeof( int ) ) )
//ant: ( void * ) * ( ( ( void ** )( ( char* ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) + ( sizeof( char ) * 50 ) * 2 + sizeof( int ) + sizeof( void* ) ) )


int main() {
    AlocaBuffer();

    int* escolha = (int*)pBuffer;
    int* i = (int*)((char*)pBuffer + sizeof(int));
    int* temp_idade = (int*)((char*)pBuffer + 2 * sizeof(int));
    void** First = (void**)((char*)pBuffer + 3 * sizeof(int));
    void** Last = (void**)((char*)pBuffer + 3 * sizeof(int) + sizeof(void*));
    void** temp_node = (void**)((char*)pBuffer + 3 * sizeof(int) + 2 * sizeof(void*));
    void** temp_node2 = (void**)((char*)pBuffer + 3 * sizeof(int) + 3 * sizeof(void*));
    char* temp_nome = (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*));
    char* temp_email = (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50);

    while ( 1 ) {
        
        MostraMenu(escolha);
        switch ( ( ( int * ) pBuffer )[ 0 ] ) {
            case 1:
                AdicionaPessoa((void**)((char*)pBuffer + 3 * sizeof(int) + 2 * sizeof(void*)));
                break;
            case 2:
                RemovePessoa();
                break;
            case 3:
                BuscarPessoa();
                break;
            case 4:
                ListarPessoas( *( void** )( ( char* ) pBuffer + 3 * sizeof( int ) ) );
                break;
            case 5:
                FreeMemory( *( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) + ( sizeof( void* ) * 2 ) ) ,*( ( void ** ) pBuffer + ( sizeof( int ) * 3 ) ) );
                free( pBuffer );
                return 0;
            default:
                printf( "Opção inválida\n" );
        }
    }

    return 0;
}

void MostraMenu(int *escolha){
        printf( "1- Adicionar Pessoa\n" );
        printf( "2- Remover Pessoa\n" );
        printf( "3- Buscar Pessoa\n" );
        printf( "4- Listar todos\n" );
        printf( "5- Sair\n" );

        // Coloca a escolha do usuário no endereço de memória da escolha
        scanf( "%d", escolha);

        //Pra tirar o /n
        getchar();
}

void AlocaBuffer() {

    //Implicitamente, o tamanho de cada pessoas é 50, e o máximo de pessoas é 100
    if ( ( pBuffer = ( void* )calloc( 1,
        (
        3 * sizeof(int) + //(escolha,i,idade)
        4 * sizeof(void*) + //(first, last, temp, temp2)
        2 * 50 * sizeof(char) //(temp_nome, temp_email, temp_idade)
        )
    ) ) == NULL ) { 
        printf( "Erro ao alocar memória\n" );
        exit( EXIT_FAILURE );
    }

    //Alocando os inteiros:
    ( ( int* ) pBuffer )[0] = 0; //escolha
    ( ( int* ) pBuffer )[1] = 0; // i
    ( ( int* )pBuffer )[2] = 0; // temp_idade


    //Alocando os pointers:
    ( ( void** )( ( ( int* ) pBuffer ) + 3 ) )[0] = NULL; //First
    ( ( void** )( ( ( int* ) pBuffer ) + 3 ) )[1] = NULL;// Last
    ( ( void** )( ( ( int* ) pBuffer ) + 3 ) )[2] = NULL; // Temp
    ( ( void** )( ( ( int* ) pBuffer ) + 3 ) )[3] = NULL; // Temp2

    //Alocando strings
    memset( ( char* )( ( ( void** )( ( ( int* ) pBuffer ) + 3 ) ) + 4), 0, 50 ); // temp nome
    memset( ( char* )( ( ( void** )( ( ( int* ) pBuffer ) + 3 ) ) + 4) + 50, 0, 50 ); // temp email
}

void Push(void** head, void** praAdicionar) {

    if (*head == NULL) { // Se esta vazia
        *head = *praAdicionar;
        *pLast = *pTemp;
        printf("LIsta vazia");
    } else { // se nao esta vazia
        void** current = pFirst;
        while (*current != NULL && strcmp((char*)*pTemp, (char*)*current) <= 0) {
            current = *(void**)((char*)*current + 100 + sizeof(int) + sizeof(void*));
        }

        if(current == NULL){ 
            //Nao percorreu a lista porque vinha antes de todos
            printf("Vem antes de todos");
            *(void **)(((char*)*pTemp) + 100 + sizeof(int))  = *pFirst;
            *(void **)(((char*)*pTemp) + 100 + sizeof(int) + sizeof(void*)) 
            *pFirst = *pTemp;
        } else if( current == pLast) { 
            // Percorreu toda a lista ate o final
            printf("Ultimo da lista");
            *(void **)(((char*)*pTemp) + 100 + sizeof(int)) = NULL;
            *(void **)(((char*)*pTemp) + 100 + sizeof(int) + sizeof(void*)) = *pLast;
            *pLast = *pTemp;
        } else { //Entre os nodos   
            printf("Entre os nodos");
            *(void **)(((char*)*pTemp) + 100 + sizeof(int) + sizeof(void*)) = *(void **)(((char*)current) + 100 + sizeof(int) + sizeof(void*)); //Previous do temp vira previous do current
            *((void**)((char**)(void **)(((char*)current) + 100 + sizeof(int) + sizeof(void*)) +  + 100 + sizeof(int))) = *pTemp; // next do previus do current vira temp
            *(void **)(((char*)*pTemp) + 100 + sizeof(int)) = current; // next do temp vira current
            *(void **)(((char*)current) + 100 + sizeof(int) + sizeof(void*)) = *pTemp; // previous do current vira temp
        }
    }
}


void* Pop(void** pTemp, void** pFirst, void** pLast) {
    *pTemp = *pFirst;

;    *pFirst = *(void**)((char*)*pFirst + 100 * sizeof(char) + sizeof(int) + sizeof(void*));

    if (*pFirst == NULL) {
        *pLast = NULL;
    } else {
        *(void**)((char*)*pFirst + 100 * sizeof(char) + sizeof(int)) = NULL;
    }

    return *pTemp;
}


void AdicionaPessoa(void **pTemp) {
    //Pega o nome
    printf( "Digite o nome a ser inserido: " );
    fgets( (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*)) , 50, stdin );

    *(int*)((char*)pBuffer + sizeof(int)) = strlen( (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*)) );
    if ( ( ( char* )( ( char* ) pBuffer + 3 * sizeof( int ) + 4 * sizeof( void* ) ) )[ *( int* )( ( char* ) pBuffer + sizeof( int ) )- 1] == '\n') 
    {
         ( ( char* )( ( char* ) pBuffer + 3 * sizeof( int ) + 4 * sizeof( void* ) ) )[ *( int* )( ( char* ) pBuffer + sizeof( int ) )- 1] = '\0';
    }

    //Pega o email
    printf( "Digite o email: " );
    fgets( (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50), 50, stdin );

    *(int*)((char*)pBuffer + sizeof(int)) = strlen( (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50) );
    if ( ( ( char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50))[*(int*)((char*)pBuffer + sizeof(int))- 1] == '\n') 
    {
        ((char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50))[*(int*)((char*)pBuffer + sizeof(int)) - 1] = '\0';
    }

    // Pega a idade
    printf( "Digite a idade: " );
    scanf( "%d", (int*)((char*)pBuffer + 2 * sizeof(int)) );

    while ( getchar() != '\n' );

    printf("Nome armazenado: %s\n", (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*)));
    printf("Email armazenado: %s\n", (char*)((char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50));
    printf("Idade armazenada: %d\n", *(int*)((char*)pBuffer + 2 * sizeof(int)) );

    *pTemp = malloc(50 * sizeof(char) + 50 * sizeof(char) + sizeof(int) + 2 * sizeof(void*));
    if (*pTemp == NULL) {
        printf("Erro ao alocar memória para o novo nodo\n");
        exit(EXIT_FAILURE);
    }

    strcpy((char*)*pTemp, (char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*));
    strcpy((char*)*pTemp + 50 * sizeof(char), (char*)pBuffer + 3 * sizeof(int) + 4 * sizeof(void*) + 50 * sizeof(char)); 
    *(int*)((char*)*pTemp + 100 * sizeof(char)) = *(int*)((char*)pBuffer + 2 * sizeof(int)); 

    *(void**)((char*)*pTemp + 100 * sizeof(char) + sizeof(int)) = NULL; // proximo
    *(void**)((char*)*pTemp + 100 * sizeof(char) + sizeof(int) + sizeof(void*)) = NULL; // anterior
    //Chamando a push para mandar para a agenda
    Push(
        *pTemp,
         // Last node
    );
}


void RemovePessoa() {
    if (*(void**)((char*)pBuffer + 3 * sizeof(int)) == NULL) {
        printf("A lista está vazia\n");
        return;
    }
    Pop(
        (void**)((char*)pBuffer + 3 * sizeof(int) + 2 * sizeof(void*)), // Temporary node
        (void**)((char*)pBuffer + 3 * sizeof(int)), // First node
        (void**)((char*)pBuffer + 3 * sizeof(int) + sizeof(void*)) // Last node
    );
}

void BuscarPessoa() {
    // Implementar a função de buscar pessoa
    printf( "Função de buscar pessoa ainda não implementada\n" );
}

void ListarPessoas(void* current) {
    if(current == NULL){
        printf("Agenda vazia");
        return;
    }

    while (current != NULL) {
        *(void**)((char*)pBuffer + 3 * sizeof(int) + 2 * sizeof(void*)) = current;
        Printar(*(void**)((char*)pBuffer + 3 * sizeof(int) + 2 * sizeof(void*)));
        current = *(void**)((char*)current + 100 * sizeof(char) + sizeof(int) + sizeof(void*));
    }
}

void Printar(void* temp) {
    printf("########################\n");
    printf("Nome: %s\n", (char*)temp);
    printf("Email: %s\n", (char*)temp + 50 * sizeof(char));
    printf("Idade: %d\n", *(int*)((char*)temp + 100 * sizeof(char)));
    printf("########################\n");
}

void FreeMemory(void *temp, void *pFirst) {
    while (pFirst != NULL) {
        temp = *(void**)((char*)pFirst + 100 * sizeof(char) + sizeof(int) + sizeof(void*));
        free(pFirst);
        pFirst = temp;
    }
}

