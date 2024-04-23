#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void MostraMenu( void );
void AdicionarNome( char **string );
void RemoverNome( char **string );
void Listar( char *string );
void FlushBuffer();


int main( void ){
	int escolha;
	char *string = NULL;
	do
	{
		escolha = 0;
		MostraMenu();
		scanf( "%i", &escolha );
		switch ( escolha ) {
			case 1:
				AdicionarNome( &string );
				break;
			case 2:
				RemoverNome( &string );
				break;
			case 3:
				Listar( string );
				break;
			case 4:
				printf( "Adeus!\n" );
				break;
			default:
				printf( "Erro, insira um numero valido.\n" );
				FlushBuffer();
				continue;
		} 
	} while( escolha != 4 );
}

void MostraMenu( void ){
	/*
		====================
			MostrarMenu
			Essa função exibe o menu de decisão para o usuário, ele serve para
			diminuir o codigo na main
		====================
	*/

	printf( "==============================\n1) Adicionar Nome\n2) Remover Nome\n3) Listar\n4) Sair \n==============================\n");
	printf("Selecione uma opcao da lista: ");
}

void AdicionarNome( char **string ){
	/*
		====================
			AdicionarNome
			Essa função adiciona um nome na lista de nomes;
		====================
	*/

	char c = '\0';
	char *nome = NULL, *novaString = NULL, *temp = NULL;
	int i = 0, tamanhoString =0, tamanhoNovaString =0;

	printf( "Digite o nome: " );

	FlushBuffer();

	do {
		c = getchar();
		if( ( nome = ( char* )realloc( nome, ( sizeof( char )*( i + 1 ) ) + 1 )) == NULL ){
			printf( "Erro ao re-alocar memoria" );
			exit( EXIT_FAILURE );
		}
		nome[i++] = c;
	} while ( c != '\n' );
	nome[i] = '\0';

	tamanhoNovaString = sizeof( char )*i;

	if( *string != NULL ){
		tamanhoString = sizeof( char )*strlen( *string );	
		if( ( temp = ( char* )malloc( sizeof( char )*( tamanhoString + 1) ) ) == NULL ){
			printf( "Erro ao alocar memoria para a temp!\n" );
			free( nome );
			exit( EXIT_FAILURE );
		}
		strcpy( temp,*string );
	} else{
		if( ( temp = ( char* )malloc( sizeof( char ) ) ) == NULL ){
			printf( "Erro ao alocar memoria para a temp!\n" );
			free( nome );
			exit( EXIT_FAILURE );
		}
		temp[0]='\0';
	}


	if( ( *string = ( char* )realloc( *string,tamanhoNovaString + tamanhoString + 1 ) ) == NULL ){
		printf( "Erro ao alocar memoria para a string!\n" );
		free( nome );
		free( temp );
		exit( EXIT_FAILURE );
	}

	strcpy( *string,temp );
	strcat( *string,nome );

	free( temp );
	free( nome );

	printf( "Nome adicionado com sucesso!\n" );
}

void RemoverNome( char **string ){
	/*
		====================
			RemoverNome
			Essa função remove um nome da lista de nomes;
		====================
	*/	

	char c = '\0';
	char *nome = NULL, *deletaString = NULL, *tempParte1 = NULL, *tempParte2 = NULL;
	int i = 0, tamanhoString =0, tamanhoDeletaString =0, j=0, k=0;
	int achouNome = 0;
	

	printf( "Digite o nome para remover: " );

	FlushBuffer();

	do {
		c = getchar();
		if( ( nome = ( char* )realloc( nome, ( sizeof( char )*( i + 1 ) ) + 1 )) == NULL ){
			printf( "Erro ao re-alocar memoria!\n" );
			exit( EXIT_FAILURE );
		}
		nome[i++] = c;
	} while ( c != '\n' );
	nome[i] = '\0';

	i = 0;

	while( ( *string )[i] != '\0' ){
		if( ( *string )[i] == nome[j] ){
			j++;
		} else {
			j = 0;
		}
		i++;

		if( j == strlen( nome ) ){ 
            
			if( ( tempParte1 = ( char * )malloc( sizeof( char )*( i - strlen( nome ) + 1 ) ) ) == NULL){
				printf( "Erro ao alocar memoria para a temp!\n" );
				free( nome );
				exit( EXIT_FAILURE );
			}

            strncpy( tempParte1, *string, i - strlen( nome ) ); 
            tempParte1[i - strlen( nome )] = '\0'; 

            if( ( tempParte2 = ( char * )malloc( sizeof( char )*( strlen( *string ) - i + 1 ) ) ) == NULL ){
				printf( "Erro ao alocar memoria para a temp!\n" );
				free( nome );
				exit( EXIT_FAILURE );
			}

            strcpy( tempParte2, *string + i ); 

            if( ( *string = ( char * )realloc( *string, strlen( tempParte1 ) + strlen( tempParte2 ) + 1 ) ) == NULL ){
				printf( "Erro ao alocar memoria para a string!\n" );
				free( nome );
				exit( EXIT_FAILURE );
			}

            strcpy( *string, tempParte1 ); 
            strcat( *string, tempParte2 ); 

            free( nome );
            free( tempParte1 );
            free( tempParte2 );
			achouNome = 1;
        }
	}

	if( achouNome == 0){
		printf( "Nome nao encontrado!\n" );
	} else {
		printf( "Nome removido com sucesso!\n" );
	}
}

void Listar( char *string ){
	/*
		====================
			Listar
			Essa função lista os nomes armazenados;
		====================
	*/

	if( strlen( string ) <= 0 ){
		printf( "Nao ha nomes na lista!\n" );
	} else {
		printf( "Lista de nomes: \n%s",string );
	}
}

void FlushBuffer() {
	/*
		====================
			FlushBuffer
			Essa função serve para limpar o buffer, limpar a sujeira que estava 
			nele, o getchar estava dando erro sem isso;
		====================
	*/

    int c;
    while ( ( c = getchar() ) != '\n' );
}