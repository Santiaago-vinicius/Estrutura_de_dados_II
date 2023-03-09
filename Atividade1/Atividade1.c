#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char valor;
    struct no* esq;
    struct no* dir;
} No;

No* criarNo(char valor){
    No* newNo = (No*) malloc(sizeof(No));
    newNo -> valor = valor;
    newNo -> esq = NULL;
    newNo -> dir = NULL;
    return newNo;
}

No* inserirNo(No *raiz, char valor){
    if (raiz == NULL){
        return criarNo(valor);
    }
    if (valor < raiz -> valor){
        raiz -> esq = inserirNo(raiz -> esq, valor);
    } else {
        raiz -> dir = inserirNo(raiz -> dir, valor);
    }
    return raiz;
}

void printarArvore(No *raiz){
    if(raiz == NULL){
        return;
    }
    printf("<%d>", raiz-> valor);
    printarArvore(raiz -> esq);
    printarArvore(raiz -> dir);
}

int main(){
    No *raiz = NULL;
    raiz = inserirNo(raiz, 'A');
    inserirNo(raiz, 'B');
    inserirNo(raiz, 'C');
    printarArvore(raiz);
    return 0;
}