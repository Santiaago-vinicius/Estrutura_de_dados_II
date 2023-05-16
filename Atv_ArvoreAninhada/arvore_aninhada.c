#include <stdio.h>
#include <stdlib.h>

typedef struct arv {
    int info;
    struct arv *prox;
} Arv;

// Função para incluir um nó em uma árvore alinhada
void incluirNo(Arv **raiz, int valor) {
    Arv *novo = (Arv *)malloc(sizeof(Arv));
    novo->info = valor;
    novo->prox = NULL;

    if (*raiz == NULL) {
        *raiz = novo;
    } else {
        Arv *atual = *raiz;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Função para percurso in-order em uma árvore alinhada
void percursoInOrder(Arv *no) {
    if (no != NULL) {
        percursoInOrder(no->prox);
        printf("%d ", no->info);
    }
}

// Função para percurso pre-order em uma árvore alinhada
void percursoPreOrder(Arv *no) {
    if (no != NULL) {
        printf("%d ", no->info);
        percursoPreOrder(no->prox);
    }
}

int main() {
    Arv *arvore = NULL;

    // Inclusão de nós na árvore alinhada
    incluirNo(&arvore, 4);
    incluirNo(&arvore, 2);
    incluirNo(&arvore, 7);
    incluirNo(&arvore, 5);
    incluirNo(&arvore, 1);
    incluirNo(&arvore, 3);
    incluirNo(&arvore, 6);

    printf("Percurso In-Order: ");
    percursoInOrder(arvore);
    printf("\n");

    printf("Percurso Pre-Order: ");
    percursoPreOrder(arvore);
    printf("\n");

    return 0;
}
