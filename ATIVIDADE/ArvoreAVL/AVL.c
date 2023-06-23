#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
};

// Função auxiliar para criar um novo nó
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para obter a altura de um nó
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para realizar a rotação simples à direita
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Função para realizar a rotação simples à esquerda
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Função para verificar o fator de balanceamento de um nó
int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Função para inserir um novo nó na árvore AVL
struct Node* insertNode(struct Node* node, int value) {
    // Realiza a inserção normal de um nó de árvore binária
    if (node == NULL)
        return newNode(value);

    if (value < node->value)
        node->left = insertNode(node->left, value);
    else if (value > node->value)
        node->right = insertNode(node->right, value);
    else // Não permitir valores duplicados
        return node;

    // Atualiza a altura do nó atual
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Verifica o fator de balanceamento do nó
    int balanceFactor = getBalanceFactor(node);

    // Caso 1: Rotação à esquerda
    if (balanceFactor > 1 && value < node->left->value)
        return rightRotate(node);

    // Caso 2: Rotação à direita
    if (balanceFactor < -1 && value > node->right->value)
        return leftRotate(node);

    // Caso 3: Rotação dupla à esquerda
    if (balanceFactor > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Rotação dupla à direita
    if (balanceFactor < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para percorrer a árvore em ordem (inorder traversal)
void inorderTraversal(struct Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->value);
        inorderTraversal(node->right);
    }
}

// Função principal
int main() {
    struct Node* root = NULL;

    // Inserção dos elementos na árvore AVL
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 60);
    root = insertNode(root, 70);

    // Imprime a árvore em ordem (inorder traversal)
    printf("Árvore AVL resultante: ");
    inorderTraversal(root);

    return 0;
}
