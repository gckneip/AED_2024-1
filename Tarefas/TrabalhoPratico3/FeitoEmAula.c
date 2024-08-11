/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void getHighestDepth(struct TreeNode* root,int altura,int* maiorAltura);
void getDeepestNodes(struct TreeNode* root,int altura,int maiorAltura, int caminho[]);
struct TreeNode* getNode(struct TreeNode* root,int val);

int** caminhosDosNodosMaisProfundos = NULL;
int quantidadeDeNodosProfundos;

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    int* maiorAltura = NULL;
    int* raizEmComum = NULL;
    int altura = 0;
    quantidadeDeNodosProfundos = 0;
    int caminho[500];

    caminhosDosNodosMaisProfundos = (int**)calloc(1,sizeof(int**)*500);
    maiorAltura = (int*)malloc(sizeof(int));
    raizEmComum = (int*)calloc(1,sizeof(int));

    *maiorAltura = 0;

    getHighestDepth(root,altura,maiorAltura); //Pega a maior profundidade

    printf("Highest depth: %d\n",*maiorAltura);
    printf("Deepest Nodes: \n");
    getDeepestNodes(root,altura,*maiorAltura,caminho); //Pega os nodos mais profundos e o caminho ate eles
    printf("Caminhos: [");

    for(int i = 0; i < quantidadeDeNodosProfundos; i++){
        printf("[");
        for(int j = 0; j < *maiorAltura; j++){
            printf("%d,",caminhosDosNodosMaisProfundos[i][j]);
        }
        printf("],");
    }
    printf("]");


    //A ideia agora é comparar os caminhos de todos os nodos mais profundos, ver quais raizes eles possuem em comum e retornar a subarvore a partir do primeira nodo em comum entre eles;
    if(quantidadeDeNodosProfundos == 1 ){
        int val = caminhosDosNodosMaisProfundos[0][*maiorAltura-1];
        return getNode(root,val);
    }

    return root;
}


void getHighestDepth(struct TreeNode* root,int altura,int* maiorAltura){
    if (root == NULL) return;

    altura++;
    getHighestDepth(root->left,altura,maiorAltura);
    getHighestDepth(root->right,altura,maiorAltura);

    if(altura > *maiorAltura){
        *maiorAltura = altura;
    }
}

void getDeepestNodes(struct TreeNode* root,int altura, int maiorAltura, int caminho[]){
    if (root == NULL) return;

    caminho[altura] = root->val;
    altura++;
    getDeepestNodes(root->left,altura,maiorAltura,caminho);
    getDeepestNodes(root->right,altura,maiorAltura,caminho);

    if(altura == maiorAltura){
        printf("    Node: %d \n    Depth: %d\n    Caminho: [",root->val,altura);
        caminhosDosNodosMaisProfundos[quantidadeDeNodosProfundos] = (int*)(malloc(sizeof(int)*altura));
        for(int i = 0; i < altura; i++){
            caminhosDosNodosMaisProfundos[quantidadeDeNodosProfundos][i] = caminho[i];
            printf("%d,",caminhosDosNodosMaisProfundos[quantidadeDeNodosProfundos][i]);
        }
        printf("]\n##########\n");
        quantidadeDeNodosProfundos++;
    }
}

struct TreeNode* getNode(struct TreeNode* root, int val){
    if(root == NULL) return NULL;

    if(root->val < val){
        return getNode(root->left,val);
    } else if (root->val > val) {
        return getNode(root->right,val);
    } else if (root->val == val){
        return root;
    }

    // Não da certo porque a arvore não é AVL ;-;
    
    return NULL;
}

