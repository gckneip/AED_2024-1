#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
################################ FUNÇÕES ######################################
*/
void AdicionarPessoa();
void RemoverPessoa();
void BuscarPessoa();
void ListarTodos();
void Sair();


//Auxiliares
void MostraMenu(int* pEscolha);
void *CriaNodo(char *pNome, char *pEmail, int *pIdade);
void Push( void **pFirst, void **pLast, void *pNovoNodo,void *pCurrent, void *pPrev );
void *Pop( void **pFirst, void **pLast, void *pTemp );


/*
################################ DEFINES ######################################
*/
//Defines de aritmetica no buffer
#define TAM_PONTEIRO (sizeof(void**))
#define TAM_STRING (sizeof(char*)*50)
#define TAM_INTEIRO (sizeof(int))
#define TAM_INICIAL (2*TAM_PONTEIRO)

//Defines de aritmetica nos nodos
#define NOME_NODO + (0)
#define EMAIL_NODO + (TAM_STRING)
#define IDADE_NODO + (2*TAM_STRING)
#define PROX_NODO + (2*TAM_STRING + TAM_INTEIRO)
#define ANT_NODO + (2*TAM_STRING + TAM_INTEIRO + TAM_PONTEIRO)


/*
################################ MAIN ######################################
*/
void *pBuffer = NULL;

void main(int){

    //Criando First e Last para manter track da fila
    if( ( pBuffer = ( void *)calloc( 1, TAM_INICIAL ) ) == NULL ) {
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    void **pFirst = ( void ** )( pBuffer );
    void **pLast = ( void ** )( pBuffer + TAM_PONTEIRO );
    *pFirst = NULL;
    *pLast = NULL;

    while ( 1 ){
        
        //Criando o escolha para pegar o input do usuário:
        if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL + TAM_INTEIRO ) ) == NULL ){
            printf("Erro ao alocar memória\n");
            exit(EXIT_FAILURE);
        }
        int *pEscolha = ( int* )( pBuffer + TAM_INICIAL );
        
        MostraMenu(pEscolha);
        
        switch (*pEscolha)
        {
            case 1:
                //Realocando buffer
                if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL ) ) == NULL ){
                    printf("Erro ao alocar memoria\n");
                    exit(EXIT_FAILURE);
                }
                AdicionarPessoa();
            break;
            case 2:
                //Realocando buffer
                if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL ) ) == NULL ){
                    printf("Erro ao alocar memoria\n");
                    exit(EXIT_FAILURE);
                }
                RemoverPessoa(pFirst,pLast);
            break;
            case 3:   
                //Realocando buffer
                if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL ) ) == NULL ){
                    printf("Erro ao alocar memoria\n");
                    exit(EXIT_FAILURE);
                }
                BuscarPessoa();
            break;
            case 4:
                //Realocando buffer
                if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL ) ) == NULL ){
                    printf("Erro ao alocar memoria\n");
                    exit(EXIT_FAILURE);
                }
                ListarTodos(pFirst, pLast);
            break;
            case 5:
                //Realocando buffer
                if( ( pBuffer = ( void *)realloc( pBuffer, TAM_INICIAL ) ) == NULL ){
                    printf("Erro ao alocar memoria\n");
                    exit(EXIT_FAILURE);
                }
                Sair();
            return;
            default:
                printf("Opção inválida!\n");
            break;
        }
    }

}

/*
################################ FUNÇÕES PRINCIPAIS ######################################
*/

/* ====================================================================================== 
AdicionarPessoa
    Recebe as informações do usuário;
    Aloca espaço no buffer para armazenar essa infos;
    Aloca espaço e cria um nodo com as informações;
    Chama a função Push para adicionar o novo contato na agenda em ordem alfabética
====================================================================================== */
void AdicionarPessoa() {
    
    // Alocando memoria para armazenar o nome, email e idade temporáriamente;
    if( ( pBuffer = ( void * )realloc( pBuffer, TAM_INICIAL + TAM_PONTEIRO + TAM_STRING + TAM_STRING + TAM_INTEIRO ) ) == NULL ){
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    
    // Lendo o nome
    char *pNomeTemp = ( char * )( pBuffer + TAM_INICIAL + TAM_PONTEIRO );
    printf( "\nDigite o nome: " );
    fgets( pNomeTemp, 50, stdin );
    pNomeTemp[ strcspn( pNomeTemp, "\n" ) ] = '\0';

    // Lendo o email
    char *pEmailTemp = ( char * )( pBuffer + TAM_INICIAL + TAM_PONTEIRO + TAM_STRING );
    printf( "Digite o email: " );
    fgets( pEmailTemp, 50, stdin );
    pEmailTemp[ strcspn( pEmailTemp, "\n" ) ] = '\0';

    int *pIdadeTemp = ( int * )( pBuffer + TAM_INICIAL + TAM_PONTEIRO + TAM_STRING + TAM_STRING );
    printf( "Digite a idade: " );
    scanf( "%d", pIdadeTemp );
    getchar(); // Tira o ultimo \n

    printf( "############# ADICIONADO ############\n");
    printf( "Nome: %s\n", pNomeTemp );
    printf( "Email: %s\n", pEmailTemp );
    printf( "Idade: %d\n", *pIdadeTemp );
    printf( "##################################\n");

    void **pNovoNodo = (void**)(pBuffer + TAM_INICIAL);
    *pNovoNodo = CriaNodo( pNomeTemp, pEmailTemp, pIdadeTemp );

    //Realocando buffer
    if( ( pBuffer = (void *)realloc(pBuffer, TAM_INICIAL + 3 * TAM_PONTEIRO) ) == NULL ) {
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    };

    pNovoNodo = (void **)(pBuffer + TAM_INICIAL);
    void **pCurrent = (void **)(pBuffer + TAM_INICIAL + TAM_PONTEIRO);
    void **pPrev = (void **)(pBuffer + TAM_INICIAL + 2 * TAM_PONTEIRO);

    *pCurrent = NULL;
    *pPrev = NULL;

    void **pFirst = ( void ** )( pBuffer );
    void **pLast = ( void ** )( pBuffer + TAM_PONTEIRO );

    Push( pFirst, pLast, *pNovoNodo, *pCurrent, *pPrev );
}

/* ====================================================================================== 
RemoverPessoa
    Remove uma pessoa da agenda;
    Itera pela agenda como uma heap (apenas tem acesso ao Primeiro), dando Pop
    na heap Principal e Push para a auxiliar, até encontrar o contato desejado;
    Quando encontrado, o contato e excluido (free);
    Passa os contatos da auxiliar de volta para a principal;
====================================================================================== */
void RemoverPessoa() {

    if( ( pBuffer = ( void * )realloc( pBuffer, TAM_INICIAL + 6 * TAM_PONTEIRO + TAM_STRING + TAM_INTEIRO) ) == NULL ){
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    void **pFirst = ( void** )( char* )( pBuffer);
    void **pLast = ( void** )( char* )( pBuffer + TAM_PONTEIRO );
    void **auxHeap = ( void** )( char* )( pBuffer + TAM_INICIAL );
    void **auxFirst = ( void** )( pBuffer + TAM_INICIAL + TAM_PONTEIRO );
    void **auxLast = ( void** )( pBuffer + TAM_INICIAL + 2 * TAM_PONTEIRO );
    void **pCurrent = ( void** )( pBuffer + TAM_INICIAL + 3 * TAM_PONTEIRO );
    void **pPrev = ( void** )( pBuffer + TAM_INICIAL + 4 * TAM_PONTEIRO );
    void **pTemp = ( void** )( pBuffer + TAM_INICIAL + 5 * TAM_PONTEIRO );
    char *pNomeTemp = ( char * )( pBuffer + TAM_INICIAL + 6 * TAM_PONTEIRO );
    int *achou = ( int * )( pBuffer + TAM_INICIAL + 6 * TAM_PONTEIRO + TAM_STRING );

    *achou = 0;

    // Lendo o nome
    printf( "\nDigite o nome: " );
    fgets( pNomeTemp, 50, stdin );
    pNomeTemp[ strcspn( pNomeTemp, "\n" ) ] = '\0';

    if(*pFirst == NULL){
        printf("############## LISTA VAZIA ###################\n");
        return;
    }
    *auxHeap = NULL;
    *auxFirst = *auxHeap;
    *auxLast = *auxHeap;

    while ( *pFirst != NULL ) {
        pCurrent = NULL;
        pPrev = NULL;

        *pTemp = Pop( pFirst, pLast,*pTemp );
        
        if ( *pTemp == NULL ) {
            break;
        }
        if( strcmp( ( ( char * )*pTemp NOME_NODO ), pNomeTemp) == 0){
            printf( "############ REMOVIDO ##########\n");
            printf( "Nome: %s\n", ( ( char * )*pTemp NOME_NODO ) );
            printf( "Email: %s\n",( char * )( *pTemp EMAIL_NODO ) );
            printf( "Idade: %d\n",*( int * )( *pTemp IDADE_NODO ) );
            printf( "##################################\n");
            free(*pTemp);
            *achou = 1;
        } else {
            Push( auxFirst, auxLast, *pTemp, pCurrent, pPrev );
        }

    }

    while ( *auxFirst != NULL ) {
        *pTemp = Pop( auxFirst, auxLast,*pTemp );
        Push( pFirst, pLast, *pTemp, pCurrent, pPrev );
    }

    if( *achou == 0 ){
        printf("############## NAO ENCONTRADO ###################\n");
    }
}

/* ====================================================================================== 
BuscarPessoa
    Busca um contato na agenda e o printa na tela;
    Itera pela agenda como uma heap (apenas tem acesso ao Primeiro), dando Pop
    na heap Principal e Push para a auxiliar, até encontrar o contato desejado;
    Passa os contatos da auxiliar de volta para a principal;
====================================================================================== */
void BuscarPessoa(){
    if( ( pBuffer = ( void * )realloc( pBuffer, TAM_INICIAL + 6 * TAM_PONTEIRO + TAM_STRING + TAM_INTEIRO) ) == NULL ) {
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    void **pFirst = ( void** )( char* )( pBuffer);
    void **pLast = ( void** )( char* )( pBuffer + TAM_PONTEIRO );
    void **auxHeap = ( void** )( char* )( pBuffer + TAM_INICIAL );
    void **auxFirst = ( void** )( pBuffer + TAM_INICIAL + TAM_PONTEIRO );
    void **auxLast = ( void** )( pBuffer + TAM_INICIAL + 2 * TAM_PONTEIRO );
    void **pCurrent = ( void** )( pBuffer + TAM_INICIAL + 3 * TAM_PONTEIRO );
    void **pPrev = ( void** )( pBuffer + TAM_INICIAL + 4 * TAM_PONTEIRO );
    void **pTemp = ( void** )( pBuffer + TAM_INICIAL + 5 * TAM_PONTEIRO );
    char *pNomeTemp = ( char * )( pBuffer + TAM_INICIAL + 6 * TAM_PONTEIRO );
    int *achou = ( int * )( pBuffer + TAM_INICIAL + 6 * TAM_PONTEIRO + TAM_STRING );

    *achou = 0;
    // Lendo o nome
    printf( "\nDigite o nome: " );
    fgets( pNomeTemp, 50, stdin );
    pNomeTemp[ strcspn( pNomeTemp, "\n" ) ] = '\0';

    if(*pFirst == NULL){
        printf("############## LISTA VAZIA ###################\n");
        return;
    }
    *auxHeap = NULL;
    *auxFirst = *auxHeap;
    *auxLast = *auxHeap;

    while ( *pFirst != NULL ) {
        pCurrent = NULL;
        pPrev = NULL;

        *pTemp = Pop( pFirst, pLast,*pTemp );
        
        if ( *pTemp == NULL ) {
            break;
        }
        if( strcmp( ( ( char * )*pTemp NOME_NODO ), pNomeTemp) == 0){
            printf( "############# BUSCA ############\n");
            printf( "Nome: %s\n", ( ( char * )*pTemp NOME_NODO ) );
            printf( "Email: %s\n",( char * )( *pTemp EMAIL_NODO ) );
            printf( "Idade: %d\n",*( int * )( *pTemp IDADE_NODO ) );
            printf( "##################################\n");
            *achou = 1;
        }

        Push( auxFirst, auxLast, *pTemp, pCurrent, pPrev );
    }

    while ( *auxFirst != NULL ) {
        *pTemp = Pop( auxFirst, auxLast,*pTemp );
        Push( pFirst, pLast, *pTemp, pCurrent, pPrev );
    }

    if( *achou == 0 ){
        printf("############## NAO ENCONTRADO ###################\n");
    }
}

/* ====================================================================================== 
ListarTodos
    Lista todos os contatos na agenda;
    Itera pela agenda como uma heap (apenas tem acesso ao Primeiro), dando Pop
    na heap Principal e Push para a auxiliar, printando os contatos na tela durante o processo;
    Passa os contatos da auxiliar de volta para a principal;
====================================================================================== */
void ListarTodos() {
    if ( ( pBuffer = ( void * )realloc( pBuffer, TAM_INICIAL + 6 * TAM_PONTEIRO ) ) == NULL ){
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    void **pFirst = ( void** )( char* )( pBuffer);
    void **pLast = ( void** )( char* )( pBuffer + TAM_PONTEIRO );
    void **auxHeap = ( void** )( char* )( pBuffer + TAM_INICIAL );
    void **auxFirst = ( void** )( pBuffer + TAM_INICIAL + TAM_PONTEIRO );
    void **auxLast = ( void** )( pBuffer + TAM_INICIAL + 2 * TAM_PONTEIRO );
    void **pCurrent = ( void** )( pBuffer + TAM_INICIAL + 3 * TAM_PONTEIRO );
    void **pPrev = ( void** )( pBuffer + TAM_INICIAL + 4 * TAM_PONTEIRO );
    void **pTemp = ( void** )( pBuffer + TAM_INICIAL + 5 * TAM_PONTEIRO );

    if(*pFirst == NULL){
        printf("############## LISTA VAZIA ###################\n");
        return;
    }
    *auxHeap = NULL;
    *auxFirst = *auxHeap;
    *auxLast = *auxHeap;
    printf("############ COMEÇO AGENDA ############\n");

    while ( *pFirst != NULL ) {
        pCurrent = NULL;
        pPrev = NULL;

        *pTemp = Pop( pFirst, pLast,*pTemp );
        
        if ( *pTemp == NULL ) {
            break;
        }

        printf( "##################################\n");
        printf( "Nome: %s\n", ( ( char * )*pTemp NOME_NODO ) );
        printf( "Email: %s\n",( char * )( *pTemp EMAIL_NODO ) );
        printf( "Idade: %d\n",*( int * )( *pTemp IDADE_NODO ) );
        printf( "##################################\n");
        Push( auxFirst, auxLast, *pTemp, pCurrent, pPrev );
    }

    printf("############ FIM AGENDA ############\n");

    while ( *auxFirst != NULL ) {
        *pTemp = Pop( auxFirst, auxLast,*pTemp );
        Push( pFirst, pLast, *pTemp, pCurrent, pPrev );
    }
}

/* ====================================================================================== 
Sair
    Desaloca o buffer e toda a agenda;
====================================================================================== */
void Sair(){
    if( ( pBuffer =  realloc(pBuffer, TAM_INICIAL + 3* TAM_PONTEIRO) ) == NULL ){
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    void **pFirst = ( void** )( char* )( pBuffer);
    void **pLast = ( void** )( char* )( pBuffer + TAM_PONTEIRO );
    void **pTemp = (void ** )( char* )( pBuffer + 2* TAM_PONTEIRO);
    while ( *pFirst != NULL ) {

        *pTemp = Pop( pFirst, pLast,*pTemp );
        
        if ( *pTemp == NULL ) {
            break;
        }

        free(*pTemp);
    }
    free(pBuffer);
    printf("############## SAINDO ###################\n");
}



/*
################################ FUNÇÕES AUXILIARES ######################################
*/

/* ====================================================================================== 
MostraMenu
    Mostra o menu para o usuário e recebe o inteiro (escolha) 
    que decidirá qual função irá rodar;
====================================================================================== */
void MostraMenu(int *pEscolha){
        printf("############## MENU ###################\n");
        printf( "1- Adicionar Pessoa\n" );
        printf( "2- Remover Pessoa\n" );
        printf( "3- Buscar Pessoa\n" );
        printf( "4- Listar todos\n" );
        printf( "5- Sair\n" );
        printf("#################################\n");


        // Coloca a escolha do usuário no endereço de memória da escolha
        scanf( "%d", pEscolha);

        //Pra tirar o /n
        getchar();
}

/* ====================================================================================== 
CriaNodo
    Aloca espaço na memória para armazenar as informações de cada contato 
    (nome,email,idade);
    Retorna um ponteiro para o nodo alocado;
    Utilizada na função AdicionarPessoa;
====================================================================================== */
void *CriaNodo( char *pNome, char *pEmail, int *pIdade ){
    void *pNovoNodo = ( void * )calloc( 1,2*TAM_STRING + TAM_INTEIRO + 2*TAM_PONTEIRO );
    if(pNovoNodo == NULL){
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    strcpy( ( char* )( pNovoNodo NOME_NODO ),pNome );

    strcpy( ( char* )( pNovoNodo EMAIL_NODO ),pEmail );

    *( int* )( char* )( pNovoNodo IDADE_NODO ) = *pIdade;

    *( void** )( char* )( pNovoNodo PROX_NODO ) = NULL;
    *( void** )( char* )( pNovoNodo ANT_NODO ) =  NULL; 

    return pNovoNodo;
}


/* ====================================================================================== 
Push
    Recebe um first, last e novoNodo aleatórios;
    Pode ser utilizado pela heap princial e pela auxiliar, a idéia era fazer uma função bem dinâmica;
    Adiciona um nodo na heap em ordem alfabética;
    Utilizada no AdicionarPessoa, no RemoverPessoa, no ListarPessoa e no BuscarPessoa;
====================================================================================== */
void Push( void **pFirst, void **pLast, void *pNovoNodo,void *pCurrent, void *pPrev ) {
    pCurrent = *pFirst;
    pPrev = NULL;

    while ( pCurrent != NULL && strcmp( ( char * )pCurrent, ( char * )pNovoNodo ) < 0 ) {
        pPrev = pCurrent;
        pCurrent = *( void **)( ( char *)pPrev PROX_NODO) ;
    }

    if(*pFirst == NULL){
        *pFirst = pNovoNodo;
        *pLast = pNovoNodo;
        *( void** )( ( char* )pNovoNodo PROX_NODO ) = NULL;
        *( void** )( ( char* )pNovoNodo ANT_NODO ) =  NULL; 
        return;
    }

    if ( pPrev == NULL ) {
        *( void ** )( ( char* )pNovoNodo PROX_NODO ) = *pFirst;
        *( void ** )( ( char* )pCurrent ANT_NODO ) = pNovoNodo;
        *pFirst = pNovoNodo;
        *( void** )( ( char* )pNovoNodo ANT_NODO ) =  NULL; 
    } else if (pCurrent != NULL) {
        *( void ** )( ( char* )pPrev PROX_NODO ) = pNovoNodo; //Proximo do anterior do atual vira o novo
        *( void ** )( ( char* )pNovoNodo ANT_NODO ) = pPrev; // Anterior do novo vira o anterior do atual
        *( void ** )( ( char* )pNovoNodo PROX_NODO ) = pCurrent;
        *( void ** )( ( char* )pCurrent ANT_NODO ) = pNovoNodo; // Anterior do atual vira o novo
    } else {
        *( void ** )( ( char* )pPrev PROX_NODO ) = pNovoNodo; //Proximo do anterior do atual vira o novo
        *( void ** )( ( char* )pNovoNodo ANT_NODO ) = pPrev; // Anterior do novo vira o anterior do atual
        *pLast = pNovoNodo;
        *( void** )( ( char* )pNovoNodo PROX_NODO ) = NULL;
    }
}

/* ====================================================================================== 
Pop
    Recebe um first, last e pTemp aleatórios;
    Pode ser utilizado pela heap princial e pela auxiliar, a idéia era fazer uma função bem dinâmica;
    Remove o primeiro nodo da heap;
    Utilizada no RemoverPessoa, no ListarPessoa e no BuscarPessoa;
====================================================================================== */
void *Pop( void **pFirst, void **pLast, void *pTemp ) {
    if ( *pFirst == NULL ) {
        printf("Nenhuma pessoa para remover.\n");
        return NULL;
    }

    pTemp = *pFirst;
    *pFirst = *( void ** )( char* )( pTemp + PROX_NODO);
    
    if (*pFirst == NULL) {
        *pLast = NULL;
    }

    *( void** )( char* )( pTemp PROX_NODO) = NULL;
    *( void** )( char* ) (pTemp ANT_NODO ) = NULL;

    return pTemp;
}