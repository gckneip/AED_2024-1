#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AdicionarPessoa();
void RemoverPessoa();
void BuscarPessoa();
void ListarTodos();
void Sair();


//Auxiliares
void InitBuffer();
void MostraMenu(int* pEscolha);
void *CriaNodo(char *pNome, char *pEmail, int *pIdade);
void Push( void **pFirst, void **pLast, void *pNovoNodo);
void *Pop( void *pFirst, void *pLast, void *pTemp );

//Defines de tamanhos fixos
#define TAM_PONTEIRO (sizeof(void**))
#define TAM_STRING (sizeof(char*)*50)
#define TAM_INTEIRO (sizeof(int))

//Defines de aritmetica de ponteiros
#define FIRST_NODE ( void ** )( char* )( pBuffer )
#define LAST_NODE ( void ** )( char* )( pBuffer + TAM_PONTEIRO )
#define ESCOLHA ( int* )( char* )( pBuffer + TAM_PONTEIRO + TAM_INTEIRO )
#define NOME_TEMP ( char* )( char* )( pBuffer +( 2*TAM_PONTEIRO + TAM_INTEIRO ) )
#define EMAIL_TEMP ( char* )( char* )( pBuffer +( 2*TAM_PONTEIRO + TAM_STRING + TAM_INTEIRO ) )
#define IDADE_TEMP ( int* )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + TAM_INTEIRO ) )
#define CURRENT_NODE ( void ** )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + 2*TAM_INTEIRO ) )
#define PREVIOUS_NODE ( void ** )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + 2*TAM_INTEIRO + TAM_PONTEIRO ) )
#define FIRST_AUX ( void ** )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + 2*TAM_INTEIRO + 2*TAM_PONTEIRO ) )
#define LAST_AUX ( void ** )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + 2*TAM_INTEIRO + 3*TAM_PONTEIRO ) )
#define TEMP_NODE ( void ** )( char* )( pBuffer +( 2*TAM_PONTEIRO + 2*TAM_STRING  + 2*TAM_INTEIRO + 4*TAM_PONTEIRO ) )

//Defines de aritmetica nos nodos
#define NOME_NODO + (0)
#define EMAIL_NODO + (TAM_STRING)
#define IDADE_NODO + (2*TAM_STRING)
#define PROX_NODO + (2*TAM_STRING + TAM_INTEIRO)
#define ANT_NODO + (2*TAM_STRING + TAM_INTEIRO + TAM_PONTEIRO)

void *pBuffer = NULL;

void main(int){

    while ( 1 ){
        
        //Criando o escolha para pegar o input do usuário:
        InitBuffer();
        int *pEscolha =  ESCOLHA;
        
        MostraMenu(pEscolha);
        
        switch (*pEscolha)
        {
            case 1:
                AdicionarPessoa();
            break;
            case 2:
                RemoverPessoa();
            break;
            case 3:   
                BuscarPessoa();
            break;
            case 4:
                ListarTodos();
            break;
            case 5:
                Sair();
            return;
            default:
                printf("Opção inválida!");
            break;
        }
    }

}


void InitBuffer(){
        pBuffer = ( void *)calloc( 1, 7*TAM_PONTEIRO + TAM_INTEIRO + 2*TAM_STRING ) ;

        *FIRST_NODE = NULL;
        *LAST_NODE = NULL;
        *ESCOLHA = 0;
        *NOME_TEMP = '\0';
        *EMAIL_TEMP = '\0';
        *IDADE_TEMP = 0;
        *CURRENT_NODE = NULL;
        *PREVIOUS_NODE = NULL;
        *FIRST_AUX = NULL;
        *LAST_AUX = NULL;
        *TEMP_NODE = NULL;


}
void MostraMenu(int *pEscolha){
        printf( "1- Adicionar Pessoa\n" );
        printf( "2- Remover Pessoa\n" );
        printf( "3- Buscar Pessoa\n" );
        printf( "4- Listar todos\n" );
        printf( "5- Sair\n" );

        // Coloca a escolha do usuário no endereço de memória da escolha
        scanf( "%d", pEscolha);

        //Pra tirar o /n
        getchar();
}

void AdicionarPessoa() {
    
    char *pNomeTemp = NOME_TEMP;

    // Lendo o nome
    printf( "\nDigite o nome: " );
    fgets( pNomeTemp, 50, stdin );
    pNomeTemp[ strcspn( pNomeTemp, "\n" ) ] = '\0';

    char *pEmailTemp = EMAIL_TEMP;

    // Lendo o email
    printf( "\nDigite o email: " );
    fgets( pEmailTemp, 50, stdin );
    pEmailTemp[ strcspn( pEmailTemp, "\n" ) ] = '\0';

    int *pIdadeTemp = IDADE_TEMP;

    printf( "\nDigite a idade: " );
    scanf( "%d", pIdadeTemp );
    getchar(); // Tira o ultimo \n

    void *pNovoNodo = CriaNodo( pNomeTemp, pEmailTemp, pIdadeTemp );

    Push( FIRST_NODE, LAST_NODE, pNovoNodo );

    printf( "Adicionando...\n" );
}

void *CriaNodo( char *pNome, char *pEmail, int *pIdade ){
    void *pNovoNodo = ( void * )calloc( 1,2*TAM_STRING + TAM_INTEIRO + 2*TAM_PONTEIRO );

    strcpy( ( char* )( pNovoNodo NOME_NODO ),pNome );

    strcpy( ( char* )( pNovoNodo EMAIL_NODO ),pEmail );

    *( int* )( char* )( pNovoNodo IDADE_NODO ) = *pIdade;

    *( void** )( char* )( pNovoNodo PROX_NODO ) = NULL;
    *( void** )( char* )( pNovoNodo ANT_NODO ) =  NULL; 

    return pNovoNodo;
}

void Push(void **pFirst, void **pLast, void *pNovoNodo) {
    void **pCurrent = CURRENT_NODE;
    void **pPrev = PREVIOUS_NODE;

    *pCurrent = *pFirst; 
    *pPrev = NULL;       

    while (*pCurrent != NULL && strcmp((char *)*pCurrent, (char *)pNovoNodo) < 0) {
        *pPrev = *pCurrent;
        *pCurrent = *(void **)((char *)*pCurrent + PROX_NODO); 
    }

    if (*pFirst == NULL) {
        *pFirst = pNovoNodo;
        *pLast = pNovoNodo;
        *(void **)((char *)pNovoNodo + PROX_NODO) = NULL;
        *(void **)((char *)pNovoNodo + ANT_NODO) = NULL;
    }
    else if (*pPrev == NULL) {
        *(void **)((char *)pNovoNodo + PROX_NODO) = *pFirst;
        *(void **)((char *)*pFirst + ANT_NODO) = pNovoNodo;
        *(void **)((char *)pNovoNodo + ANT_NODO) = NULL;
        *pFirst = pNovoNodo;
    }
    else if (*pCurrent != NULL) {
        *(void **)((char *)*pPrev + PROX_NODO) = pNovoNodo;
        *(void **)((char *)pNovoNodo + ANT_NODO) = *pPrev;
        *(void **)((char *)pNovoNodo + PROX_NODO) = *pCurrent;
        *(void **)((char *)*pCurrent + ANT_NODO) = pNovoNodo;
    }
    else {
        *(void **)((char *)*pPrev + PROX_NODO) = pNovoNodo;
        *(void **)((char *)pNovoNodo + ANT_NODO) = *pPrev;
        *(void **)((char *)pNovoNodo + PROX_NODO) = NULL;
        *pLast = pNovoNodo;
    }
}


void *Pop( void *pFirst, void *pLast, void *pTemp ) {
    if ( pFirst == NULL ) {
        printf("Nenhuma pessoa para remover.\n");
        return NULL;
    }

    pTemp = pFirst;
    pFirst = *( void ** )( char* )( pTemp + PROX_NODO);
    
    if (pFirst == NULL) {
        pLast = NULL;
    }

    *( void** )( char* )( pTemp PROX_NODO) = NULL;
    *( void** )( char* ) (pTemp ANT_NODO ) = NULL;

    return pTemp;
}


void RemoverPessoa() {
    printf("Pessoa removida.\n");
}

void BuscarPessoa(){
    printf("BUscar.....");
}

void ListarTodos() {    
    void *auxFirst = FIRST_AUX;
    void *auxLast = LAST_AUX;
    void *pCurrent = CURRENT_NODE;
    void *pPrev = PREVIOUS_NODE;
    void *pTemp = TEMP_NODE;
    
    auxFirst = NULL;
    auxLast = NULL;


    while ( FIRST_NODE != NULL ) {
        pCurrent = NULL;
        pPrev = NULL;

        pTemp = Pop( FIRST_NODE, LAST_NODE,pTemp );
        
        if ( pTemp == NULL ) {
            break;
        }

        printf( "Nome: %s, Email: %s, Idade: %d\n", ( ( char * )pTemp NOME_NODO ), 
                                                    ( char * )( pTemp EMAIL_NODO ), 
                                                    *( int * )( pTemp IDADE_NODO ) );

        Push( auxFirst, auxLast, pTemp);
    }

    while ( auxFirst != NULL ) {
        pTemp = Pop( auxFirst, auxLast,pTemp );
        Push( FIRST_NODE, LAST_NODE, pTemp );
    }
}


void Sair(){
    free(pBuffer);
    printf("Saindo.....");
}