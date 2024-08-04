#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the Red-Black Tree
typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int color; // 0 for black, 1 for red
} Node;

// Structure for the Red-Black Tree
typedef struct RedBlackTree {
    Node* root;
    Node* nil; // Sentinel node
} RedBlackTree;




// Function prototypes
Node* createNode(int data);
RedBlackTree* initializeTree();
void leftRotate(RedBlackTree* tree, Node* x);
void rightRotate(RedBlackTree* tree, Node* y);
void insertNode(RedBlackTree* tree, int data);
void insertFixup(RedBlackTree* tree, Node* z);
void inorderTraversal(Node* node);

int main() {
    RedBlackTree* tree = initializeTree();

    // Insert nodes into the Red-Black Tree
    insertNode(tree, 10);
    insertNode(tree, 40);
    insertNode(tree, 30);
    insertNode(tree, 50);
    insertNode(tree, 20);

    // Print the Red-Black Tree
    printf("Inorder Traversal: ");
    inorderTraversal(tree->root);

    return 0;
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // New nodes are always red
    return newNode;
}

// Function to initialize a Red-Black Tree
RedBlackTree* initializeTree() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->nil = createNode(0);
    tree->nil->color = 0; // Sentinel node is always black
    tree->root = tree->nil;
    return tree;
}

// Function to perform left rotation

void leftRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(RedBlackTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// Function to insert a node into the Red-Black Tree
void insertNode(RedBlackTree* tree, int data) {
    Node* z = createNode(data);
    Node* y = tree->nil;
    Node* x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = 1; // New nodes are always red
    insertFixup(tree, z);
}

// Function to fix the Red-Black Tree after insertion
void insertFixup(RedBlackTree* tree, Node* z) {
    while (z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = 0; // Root node is always black
}

// Function to print the Red-Black Tree in inorder traversal
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}