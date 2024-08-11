#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function prototypes
void getHighestDepth(struct TreeNode* root, int altura, int* maiorAltura);
void getDeepestNodes(struct TreeNode* root, int altura, int maiorAltura, int caminho[], int*** caminhosDosNodosMaisProfundos, int* quantidadeDeNodosProfundos);
int findCommonAncestor(int** caminhos, int quantidadeDeCaminhos, int profundidadeMaxima);
struct TreeNode* getNode(struct TreeNode* root, int val);
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root);
void runTests();

// Function to get the highest depth of the tree
void getHighestDepth(struct TreeNode* root, int altura, int* maiorAltura) {
    if (root == NULL) return;

    altura++;
    getHighestDepth(root->left, altura, maiorAltura);
    getHighestDepth(root->right, altura, maiorAltura);

    if (altura > *maiorAltura) {
        *maiorAltura = altura;
    }
}

// Function to get all deepest nodes and their paths
void getDeepestNodes(struct TreeNode* root, int altura, int maiorAltura, int caminho[], int*** caminhosDosNodosMaisProfundos, int* quantidadeDeNodosProfundos) {
    if (root == NULL) return;

    caminho[altura] = root->val;
    altura++;
    getDeepestNodes(root->left, altura, maiorAltura, caminho, caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos);
    getDeepestNodes(root->right, altura, maiorAltura, caminho, caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos);

    if (altura == maiorAltura) {
        (*caminhosDosNodosMaisProfundos)[*quantidadeDeNodosProfundos] = (int*)malloc(sizeof(int) * altura);
        for (int i = 0; i < altura; i++) {
            (*caminhosDosNodosMaisProfundos)[*quantidadeDeNodosProfundos][i] = caminho[i];
        }
        (*quantidadeDeNodosProfundos)++;
    }
}

// Function to find the common ancestor of all deepest nodes
int findCommonAncestor(int** caminhos, int quantidadeDeCaminhos, int profundidadeMaxima) {
    int ancestor = -1;
    
    for (int i = 0; i < profundidadeMaxima; i++) {
        int currentVal = caminhos[0][i];
        int j;
        for (j = 1; j < quantidadeDeCaminhos; j++) {
            if (caminhos[j][i] != currentVal) {
                break;
            }
        }
        if (j == quantidadeDeCaminhos) {
            ancestor = currentVal;
        } else {
            break;
        }
    }
    
    return ancestor;
}

// Function to get a node by its value
struct TreeNode* getNode(struct TreeNode* root, int val) {
    if (root == NULL) return NULL;

    if (root->val == val) return root;

    struct TreeNode* leftNode = getNode(root->left, val);
    struct TreeNode* rightNode = getNode(root->right, val);

    if (leftNode && rightNode) return root;

    return leftNode != NULL ? leftNode : rightNode;
}

// Function to get the subtree containing all deepest nodes
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    int altura = 0;
    int quantidadeDeNodosProfundos = 0;
    int caminho[500];
    int** caminhosDosNodosMaisProfundos = (int**)calloc(500, sizeof(int*));
    int* maiorAltura = (int*)malloc(sizeof(int));
    *maiorAltura = 0;

    getHighestDepth(root, altura, maiorAltura);
    printf("Highest depth: %d\n", *maiorAltura);

    getDeepestNodes(root, altura, *maiorAltura, caminho, &caminhosDosNodosMaisProfundos, &quantidadeDeNodosProfundos);

    int common_val = findCommonAncestor(caminhosDosNodosMaisProfundos, quantidadeDeNodosProfundos, *maiorAltura);

    struct TreeNode* commonAncestor = getNode(root, common_val);

    for (int i = 0; i < quantidadeDeNodosProfundos; i++) {
        free(caminhosDosNodosMaisProfundos[i]);
    }

    free(caminhosDosNodosMaisProfundos);
    free(maiorAltura);

    return commonAncestor;
}

// Function to run test cases
void runTests() {
    // Test case 1: Simple tree
    struct TreeNode node3 = {3, NULL, NULL};
    struct TreeNode node4 = {4, NULL, NULL};
    struct TreeNode node2 = {2, &node3, &node4};
    struct TreeNode node1 = {1, &node2, NULL};

    struct TreeNode* result = subtreeWithAllDeepest(&node1);
    if (result != NULL) {
        printf("Test case 1: The value of the subtree with all deepest nodes is %d\n", result->val);
    } else {
        printf("Test case 1: No subtree found\n");
    }

    // Test case 2: More complex tree
    struct TreeNode node7 = {7, NULL, NULL};
    struct TreeNode node6 = {6, NULL, NULL};
    struct TreeNode node5 = {5, NULL, NULL};
    struct TreeNode node4_2 = {4, &node7, NULL};
    struct TreeNode node3_2 = {3, &node5, &node6};
    struct TreeNode node2_2 = {2, &node3_2, &node4_2};
    struct TreeNode node1_2 = {1, &node2_2, NULL};

    result = subtreeWithAllDeepest(&node1_2);
    if (result != NULL) {
        printf("Test case 2: The value of the subtree with all deepest nodes is %d\n", result->val);
    } else {
        printf("Test case 2: No subtree found\n");
    }

    // Test case 3: Empty tree
    result = subtreeWithAllDeepest(NULL);
    if (result != NULL) {
        printf("Test case 3: The value of the subtree with all deepest nodes is %d\n", result->val);
    } else {
        printf("Test case 3: No subtree found\n");
    }
}

int main() {
    runTests();
    strcmp("a", "b");
    return 0;
}
