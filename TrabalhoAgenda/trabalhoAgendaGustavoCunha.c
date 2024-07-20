#include <stdio.h>
#include <stdlib.h>

void AdicionarPessoa(void **First, void **Last);
void RemoverPessoa();
void BuscarPessoa();
void ListarTodos();
void Sair();


//Auxiliares
void MostraMenu(int* escolha);
void *CriaNodo(char *Nome, char *Email, int *idade);
void Push(void **First, void **Last, void **NovoNodo);

#define TAM_PONTEIRO (sizeof(void*))
#define TAM_STRING (sizeof(char*)*50)
#define TAM_INTEIRO (sizeof(int))
#define TAM_INICIAL (2*TAM_PONTEIRO)

void *pBuffer = NULL;

void main(int){

    //Criando First e Last para manter track da fila
    pBuffer = ( void *)calloc( 1, TAM_INICIAL ) ;
    void **First = ( void ** )( pBuffer );
    void **Last = ( void ** )( pBuffer + TAM_PONTEIRO );
    *First = NULL;
    *Last = NULL;

    while ( 1 ){
        
        //Criando o escolha para pegar o input do usuário:
        pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL + TAM_INTEIRO ) ;
        int *escolha = ( int* )( pBuffer + TAM_INICIAL );
        
        MostraMenu(escolha);
        
        switch (*escolha)
        {
            case 1:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                AdicionarPessoa(First,Last);
            break;
            case 2:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                RemoverPessoa();
            break;
            case 3:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                BuscarPessoa();
            break;
            case 4:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                ListarTodos();
            break;
            case 5:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                Sair();
            return;
            default:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                printf("Opção inválida!");
            break;
        }
    }

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

void AdicionarPessoa(void **First, void **Last){

    //Alocando memoria para armazenar o nome temporáriamente;
    pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL + TAM_STRING );
    char *nomeTemp = ( char* )( pBuffer + TAM_INICIAL );

    //Lendo o nome
    fgets( nomeTemp, 50, stdin );

    //Removendo o \n
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_INTEIRO );
    int *tamNomeTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING );
    *tamNomeTemp = strlen( *nomeTemp );

    if (nomeTemp[*tamNomeTemp - 1] == '\n') 
    {
        nomeTemp[*tamNomeTemp - 1] = '\0';    
    }

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING );

    //Alocando memoria para armazenar o email temporáriamente;
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING );
    char *emailTemp = ( char* )( pBuffer + TAM_INICIAL + TAM_STRING);

    //Lendo o email
    fgets( emailTemp, 50, stdin );

    //Removendo o \n
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO );
    int *tamEmailTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING );
    *tamEmailTemp = strlen( *emailTemp );

    if (emailTemp[*tamEmailTemp - 1] == '\n') 
    {
        emailTemp[*tamEmailTemp - 1] = '\0';    
    }

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING );

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO );
    int *idadeTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING );
    scanf("%d",idadeTemp);


    void * novoNodo = CriaNodo(nomeTemp,emailTemp,idadeTemp);
    pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );

    Push( First, Last, novoNodo );


    printf("Adicionando.....");
}

void *CriaNodo(char *nome, char *email, int *idade){
    void *novoNodo = ( void *)malloc( TAM_STRING + TAM_STRING + TAM_INTEIRO );

    strcpy( ( char* )novoNodo,nome );

    strcpy( ( char* )( pBuffer + TAM_STRING ),email );

    *( int* )( pBuffer + TAM_STRING + TAM_STRING ) = *idade;

    return novoNodo;
}

void Push(void **First, void **Last, void **NovoNodo){

    
}


void RemoverPessoa(){
    printf("removendo.....");
}

void BuscarPessoa(){
    printf("BUscar.....");
}

void ListarTodos(){
    printf("Listando.....");
}

void Sair(){
    free(pBuffer);
    printf("Saindo.....");
}