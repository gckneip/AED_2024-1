#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

void getHighestDepth( struct TreeNode* root, int altura, int* maiorAltura );
void getDeepestNodes( struct TreeNode* root, int altura, int maiorAltura, int caminho[], int*** caminhosDosNodosMaisProfundos, int* quantidadeDeNodosProfundos );
int findCommonAncestor( int** caminhos, int quantidadeDeCaminhos, int profundidadeMaxima );
struct TreeNode* getNode( struct TreeNode* root, int val );
struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root );
void runTests();


/* ==================== Main
    Function called when you run the program. Calls other functions.
==================== */
int main() {
    runTests();
    strcmp( "a", "b" );
    return 0;
}


/* ==================== getHighestDepth
    Function to get the highest depth of a binary tree
    @param root: the root of the binary tree
    @param altura: the current depth of the tree
    @param maiorAltura: the highest depth found so far
    @return: void
==================== */
void getHighestDepth( struct TreeNode* root, int altura, int* maiorAltura ) {
    if ( root == NULL ) return;

    altura++;
    getHighestDepth( root->left, altura, maiorAltura );
    getHighestDepth( root->right, altura, maiorAltura );

    if ( altura > *maiorAltura ) {
        *maiorAltura = altura;
    }
}

/* ==================== getDeepestNodes
    Function to get the deepest nodes of a binary tree
    @param root: the root of the binary tree
    @param altura: the current depth of the tree
    @param maiorAltura: the highest depth found so far
    @param caminho: the path to the current node
    @param caminhosDosNodosMaisProfundos: the paths to the deepest nodes
    @param quantidadeDeNodosProfundos: the number of deepest nodes found
    @return: void
==================== */
void getDeepestNodes( struct TreeNode* root, int altura, int maiorAltura, int caminho[], int*** caminhosDosNodosMaisProfundos, int* quantidadeDeNodosProfundos ) {
    if ( root == NULL ) {
        return;
    }

    caminho[altura] = root->val;
    altura++;
    getDeepestNodes( root->left, altura, maiorAltura, caminho, caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos );
    getDeepestNodes( root->right, altura, maiorAltura, caminho, caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos );

    if ( altura == maiorAltura ) {
        ( *caminhosDosNodosMaisProfundos )[*quantidadeDeNodosProfundos] = ( int* )malloc( sizeof( int ) * altura );
        for ( int i = 0; i < altura; i++ ) {
            ( *caminhosDosNodosMaisProfundos )[*quantidadeDeNodosProfundos][i] = caminho[i];
        }
        ( *quantidadeDeNodosProfundos )++;
    }
}

/* ==================== findCommonAncestor
    Function to find the common ancestor of the deepest nodes
    @param caminhos: the paths to the deepest nodes
    @param quantidadeDeCaminhos: the number of deepest nodes found
    @param profundidadeMaxima: the highest depth found so far
    @return: the value of the common ancestor
==================== */
int findCommonAncestor( int** caminhos, int quantidadeDeCaminhos, int profundidadeMaxima ) {
    int ancestor = -1;
    
    for ( int i = 0; i < profundidadeMaxima; i++ ) {
        int currentVal = caminhos[0][i];
        int j;
        for ( j = 1; j < quantidadeDeCaminhos; j++ ) {
            if ( caminhos[j][i] != currentVal ) {
                break;
            }
        }
        if ( j == quantidadeDeCaminhos ) {
            ancestor = currentVal;
        } else {
            break;
        }
    }
    
    return ancestor;
}

/* ==================== getNode
    Function to get a node with a specific value
    @param root: the root of the binary tree
    @param val: the value of the node to be found
    @return: the node with the specified value
==================== */
struct TreeNode* getNode( struct TreeNode* root, int val ) {
    if ( root == NULL ) {
        return NULL;
    }
    
    if ( root->val == val ) {
        return root;
    }

    struct TreeNode* leftNode = getNode( root->left, val );
    struct TreeNode* rightNode = getNode( root->right, val );

    if ( leftNode && rightNode ) {
        return root;
    }

    return leftNode != NULL ? leftNode : rightNode;
}

/* ==================== subtreeWithAllDeepest
    Function to find the subtree with all deepest nodes
    @param root: the root of the binary tree
    @return: the root of the subtree with all deepest nodes
==================== */
struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root ) {
    int altura = 0;
    int quantidadeDeNodosProfundos = 0;
    int caminho[500];
    int** caminhosDosNodosMaisProfundos = ( int** )calloc( 500, sizeof( int* ) );
    int* maiorAltura = ( int* )malloc( sizeof( int ) );
    *maiorAltura = 0;

    getHighestDepth( root, altura, maiorAltura );
    printf( "Highest depth: %d\n", *maiorAltura );

    getDeepestNodes( root, altura, *maiorAltura, caminho, &caminhosDosNodosMaisProfundos, &quantidadeDeNodosProfundos );

    int common_val = findCommonAncestor( caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos, *maiorAltura );

    struct TreeNode* commonAncestor = getNode( root, common_val );

    for ( int i = 0; i < quantidadeDeNodosProfundos; i++ ) {
        free( caminhosDosNodosMaisProfundos[i] );
    }

    free( caminhosDosNodosMaisProfundos );
    free( maiorAltura );

    return commonAncestor;
}

/* ==================== runTests
    Function to run the tests
    @return: void
==================== */
void runTests() {
    struct TreeNode node3 = { 3, NULL, NULL };
    struct TreeNode node4 = { 4, NULL, NULL };
    struct TreeNode node2 = { 2, &node3, &node4 };
    struct TreeNode node1 = { 1, &node2, NULL };

    struct TreeNode* result = subtreeWithAllDeepest( &node1 );
    if (result != NULL) {
        printf( "Test case 1: The value of the subtree with all deepest nodes is %d\n", result->val );
    } else {
        printf( "Test case 1: No subtree found\n" );
    }

    struct TreeNode node7 = { 7, NULL, NULL };
    struct TreeNode node6 = { 6, NULL, NULL };
    struct TreeNode node5 = { 5, NULL, NULL };
    struct TreeNode node4_2 = { 4, &node7, NULL };
    struct TreeNode node3_2 = { 3, &node5, &node6 };
    struct TreeNode node2_2 = { 2, &node3_2, &node4_2 };
    struct TreeNode node1_2 = { 1, &node2_2, NULL };

    result = subtreeWithAllDeepest( &node1_2 );
    if ( result != NULL ) {
        printf( "Test case 2: The value of the subtree with all deepest nodes is %d\n", result->val );
    } else {
        printf( "Test case 2: No subtree found\n" );
    }

    result = subtreeWithAllDeepest( NULL );
    if ( result != NULL ) {
        printf( "Test case 3: The value of the subtree with all deepest nodes is %d\n", result->val );
    } else {
        printf( "Test case 3: No subtree found\n" );
    }
}
