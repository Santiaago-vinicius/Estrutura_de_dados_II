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

// Função para percurso in-order utilizando o algoritmo de Morris
void percursoInOrderMorris(struct TreeNode* raiz) {
    struct TreeNode* atual = raiz;
    while (atual != NULL) {
        if (atual->esquerda == NULL) {
            printf("%d ", atual->valor);
            atual = atual->direita;
        } else {
            // Encontre o predecessor do nó atual
            struct TreeNode* predecessor = atual->esquerda;
            while (predecessor->direita != NULL && predecessor->direita != atual) {
                predecessor = predecessor->direita;
            }

            if (predecessor->direita == NULL) {
                // Crie um link do predecessor para o nó atual
                predecessor->direita = atual;
                atual = atual->esquerda;
            } else {
                // Remova o link do predecessor para o nó atual
                predecessor->direita = NULL;
                printf("%d ", atual->valor);
                atual = atual->direita;
            }
        }
    }
}

// Função principal para testar o percurso in-order
int main() {
    // Construindo a árvore fornecida
    struct TreeNode* raiz = criarNo(10);
    raiz->esquerda = criarNo(5);
    raiz->direita = criarNo(20);
    raiz->esquerda->esquerda = criarNo(3);
    raiz->esquerda->direita = criarNo(7);
    raiz->direita->esquerda = criarNo(15);
    raiz->direita->direita = criarNo(24);

    // Realizando o percurso in-order utilizando o algoritmo de Morris
    printf("Percurso In-Order (Morris): ");
    percursoInOrderMorris(raiz);
    printf("\n");

    return 0;
}
