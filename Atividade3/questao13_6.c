#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura de um nó da árvore binária
typedef struct Node {
    int value;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Função que cria um novo nó com um determinado valor
Node* createNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

// Função que verifica se a árvore binária é estritamente binária
int estritamente_binaria(Node* node) {
    // Se a árvore estiver vazia, ela é estritamente binária
    if (node == NULL) {
        return 1;
    }
    // Se o nó for uma folha, ele é estritamente binário
    if (node->esquerda == NULL && node->direita == NULL) {
        return 1;
    }
    // Se o nó tiver apenas um filho, a árvore não é estritamente binária
    if (node->esquerda == NULL || node->direita == NULL) {
        return 0;
    }
    // Verifica se os filhos do nó são estritamente binários
    return estritamente_binaria(node->esquerda) && estritamente_binaria(node->direita);
}

int main() {
    // Criando a árvore binária de exemplo
    Node* root = createNode(1);
    root->esquerda = createNode(2);
    root->direita = createNode(3);
    root->esquerda->esquerda = createNode(4);
    root->esquerda->direita = createNode(5);
    root->direita->esquerda = createNode(6);
    root->direita->direita = createNode(7);
    root->direita->direita->esquerda = createNode(8);

    // Verificando se a árvore é estritamente binária
    if (estritamente_binaria(root)) {
        printf("A arvore e estritamente binaria.\n");
    } else {
        printf("A arvore nao e estritamente binaria.\n");
    }

    return 0;
}
