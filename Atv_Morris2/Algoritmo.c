#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct TreeNode {
    int valor;
    struct TreeNode* esquerda;
    struct TreeNode* direita;
};

// Função para criar um novo nó da árvore
struct TreeNode* criarNo(int valor) {
    struct TreeNode* no = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função para percurso pré-order utilizando pilha
void percursoPreOrder(struct TreeNode* raiz) {
    if (raiz == NULL) {
        return;
    }

    struct TreeNode* pilha[100]; // Tamanho máximo da pilha
    int topo = -1;

    pilha[++topo] = raiz;

    while (topo >= 0) {
        struct TreeNode* no = pilha[topo--];
        printf("%d ", no->valor);

        if (no->direita) {
            pilha[++topo] = no->direita;
        }

        if (no->esquerda) {
            pilha[++topo] = no->esquerda;
        }
    }
}

// Função principal para testar o percurso pré-order
int main() {
    // Construindo a árvore fornecida
    struct TreeNode* raiz = criarNo(10);
    raiz->esquerda = criarNo(5);
    raiz->direita = criarNo(20);
    raiz->esquerda->esquerda = criarNo(3);
    raiz->esquerda->direita = criarNo(7);
    raiz->direita->esquerda = criarNo(15);
    raiz->direita->direita = criarNo(24);

    // Realizando o percurso pré-order
    printf("Percurso Pré-Order: ");
    percursoPreOrder(raiz);
    printf("\n");

    return 0;
}
