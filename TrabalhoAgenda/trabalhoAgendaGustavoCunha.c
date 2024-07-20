#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AdicionarPessoa(void **pFirst, void **pLast);
void RemoverPessoa(void **pFirst, void **pLast);
void BuscarPessoa();
void ListarTodos(void **pFirst);
void Sair();


//Auxiliares
void MostraMenu(int* pEscolha);
void *CriaNodo(char *pNome, char *pEmail, int *pIdade);
void Push( void **pFirst, void **pLast, void *pNovoNodo,void **pCurrent, void **pPrev );
void *Pop( void **pFirst, void **pLast, void **pTemp );
#define TAM_PONTEIRO (sizeof(void**))
#define TAM_STRING (sizeof(char*)*50)
#define TAM_INTEIRO (sizeof(int))
#define TAM_INICIAL (2*TAM_PONTEIRO)

void *pBuffer = NULL;

void main(int){

    //Criando First e Last para manter track da fila
    pBuffer = ( void *)calloc( 1, TAM_INICIAL ) ;
    void **pFirst = ( void ** )( pBuffer );
    void **pLast = ( void ** )( pBuffer + TAM_PONTEIRO );
    *pFirst = NULL;
    *pLast = NULL;

    while ( 1 ){
        
        //Criando o escolha para pegar o input do usuário:
        pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL + TAM_INTEIRO ) ;
        int *pEscolha = ( int* )( pBuffer + TAM_INICIAL );
        
        MostraMenu(pEscolha);
        
        switch (*pEscolha)
        {
            case 1:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                AdicionarPessoa(pFirst,pLast);
            break;
            case 2:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                RemoverPessoa(pFirst,pLast);
            break;
            case 3:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                BuscarPessoa();
            break;
            case 4:
                pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL );
                ListarTodos(pFirst);
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

void AdicionarPessoa(void **pFirst, void **pLast){

    //Alocando memoria para armazenar o nome temporáriamente;
    pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL + TAM_STRING );
    char *pNomeTemp = ( char* )( pBuffer + TAM_INICIAL );

    //Lendo o nome
    printf("\nDigite o nome: ");
    fgets( pNomeTemp, 50, stdin );

    //Removendo o \n
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_INTEIRO );
    int *pTamNomeTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING );
    *pTamNomeTemp = strlen( pNomeTemp );

    if (pNomeTemp[*pTamNomeTemp - 1] == '\n') 
    {
        pNomeTemp[*pTamNomeTemp - 1] = '\0';    
    }

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING );

    //Alocando memoria para armazenar o email temporáriamente;
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING );
    char *pEmailTemp = ( char* )( pBuffer + TAM_INICIAL + TAM_STRING);

    //Lendo o email
    printf("\nDigite o email: ");
    fgets( pEmailTemp, 50, stdin );

    //Removendo o \n
    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO );
    int *pTamEmailTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING );
    *pTamEmailTemp = strlen( pEmailTemp );

    if (pEmailTemp[*pTamEmailTemp - 1] == '\n') 
    {
        pEmailTemp[*pTamEmailTemp - 1] = '\0';    
    }

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING );

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO );
    int *pIdadeTemp = ( int *)(pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING );

    printf("\nDigite a idade: ");
    scanf("%d",pIdadeTemp);

    pBuffer = ( void *)realloc( pBuffer ,TAM_INICIAL + 
                                         TAM_STRING + 
                                         TAM_STRING + 
                                         TAM_INTEIRO +
                                         TAM_PONTEIRO +
                                         TAM_PONTEIRO  +
                                         TAM_PONTEIRO);

    void ** pNovoNodo = (void**)( pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO);
    void **pCurrent = ( void** )( pBuffer + TAM_INICIAL );
    void **pPrev = ( void** )( pBuffer + TAM_INICIAL + TAM_PONTEIRO );

    pNovoNodo = CriaNodo(pNomeTemp,pEmailTemp,pIdadeTemp);
    *pCurrent = NULL;
    *pPrev = NULL;

    Push( pFirst, pLast, pNovoNodo, pCurrent, pPrev );


    printf("Adicionando.....");
}

void *CriaNodo(char *pNome, char *pEmail, int *pIdade){
    void *pNovoNodo = ( void *)malloc( TAM_STRING + 
                                      TAM_STRING + 
                                      TAM_INTEIRO + 
                                      TAM_PONTEIRO + 
                                      TAM_PONTEIRO );

    strcpy( ( char* )pNovoNodo,pNome );

    strcpy( ( char* )( pBuffer + TAM_STRING ),pEmail );

    *( int* )( pBuffer + TAM_STRING + TAM_STRING ) = *pIdade;

    *( void ** )( pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO) = NULL;
    *( void ** )( pBuffer + TAM_INICIAL + TAM_STRING + TAM_STRING + TAM_INTEIRO + TAM_PONTEIRO) = NULL;

    return pNovoNodo;
}

void Push( void **pFirst, void **pLast, void *pNovoNodo,void **pCurrent, void **pPrev ) {
    *pCurrent = pFirst;
    *pPrev = NULL;

    while ( *pCurrent != NULL && strcmp( ( char * )*pCurrent, ( char * )pNovoNodo ) < 0 ) {
        pPrev = pCurrent;
        pCurrent = ( void ** )( *pCurrent + 2 * TAM_STRING + TAM_INTEIRO) ;
    }

    if ( pPrev == NULL ) {
        *pFirst = pNovoNodo;
    } else {
        *( void ** )( *pPrev + 2 * TAM_STRING + TAM_INTEIRO ) = pNovoNodo;
    }

    *( void ** )( pNovoNodo + 2 * TAM_STRING + TAM_INTEIRO ) = *pCurrent;

    if ( *pCurrent == NULL ) {
        *pLast = pNovoNodo;
    }
}


void *Pop( void **pFirst, void **pLast, void **pTemp ) {
    if ( *pFirst == NULL ) {
        printf("Nenhuma pessoa para remover.\n");
        return NULL;
    }

    pTemp = pFirst;
    *pFirst = *(void **)(*pTemp+ 2 * TAM_STRING + TAM_INTEIRO);
    if (*pFirst == NULL) {
        *pLast = NULL;
    }
    return *pTemp;
}

void RemoverPessoa(void **pFirst, void **pLast){
    pBuffer = ( void *)realloc(pBuffer, TAM_INICIAL + TAM_PONTEIRO);
    void **pTemp = (void**)(pBuffer + TAM_INICIAL);
    pTemp = Pop(pFirst,pLast,pTemp);

    free(pTemp);

    printf("removendo.....");
}

void BuscarPessoa(){
    printf("BUscar.....");
}

void ListarTodos(void **pFirst) {
    void *pCurrent = *pFirst;
    while (pCurrent != NULL) {
        printf("Nome: %s, Email: %s, Idade: %d\n", (char *)pCurrent, 
               (char *)(pCurrent + TAM_STRING), *(int *)(pCurrent + 2 * TAM_STRING));
        pCurrent = *(void **)(pCurrent + 2 * TAM_STRING + TAM_INTEIRO);
    }
}

void Sair(){
    free(pBuffer);
    printf("Saindo.....");
}