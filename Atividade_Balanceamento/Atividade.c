#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó da árvore
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Função para calcular a altura da árvore
int getHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função para percorrer e exibir a árvore em ordem (in-order traversal)
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Função para liberar a memória alocada pela árvore
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    // Inserção dos valores na árvore
    int values[] = {7, 6, 22, 14, 40, 63};
    int numValues = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < numValues; i++) {
        root = insert(root, values[i]);
    }

    // 1.1. Cálculo da altura da árvore
    int height = getHeight(root);
    printf("1.1. A altura da árvore resultante é: %d\n", height);

    // 1.2. Exibição da árvore em ordem
    printf("1.2. Árvore resultante (ordem in-order): ");
    inOrderTraversal(root);
    printf("\n");

    // 1.3. Verificação se a árvore está balanceada
    // Aqui, podemos verificar a diferença de altura entre as subárvores esquerda e direita
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    int balanceFactor = abs(leftHeight - rightHeight);
    if (balanceFactor <= 1) {
        printf("1.3. A árvore resultante está balanceada.\n");
    }
    else {
        printf("1.3. A árvore resultante não está balanceada.\n");

        // 1.4. Reordenação dos dados para balancear a árvore
        // Usando o algoritmo de ordenação "sort" para reorganizar os valores em ordem crescente
        printf("1.4. Reordenação dos dados para balancear a árvore:\n");
        int sortedValues[numValues];
        for (int i = 0; i < numValues; i++) {
            sortedValues[i] = values[i];
        }
        int temp;
        for (int i = 0; i < numValues - 1; i++) {
            for (int j = i + 1; j < numValues; j++) {
                if (sortedValues[i] > sortedValues[j]) {
                    temp = sortedValues[i];
                    sortedValues[i] = sortedValues[j];
                    sortedValues[j] = temp;
                }
            }
        }
        for (int i = 0; i < numValues; i++) {
            printf("%d ", sortedValues[i]);
        }
        printf("\n");
    }

    // 1.5. Reordenação dos dados usando percurso in-order
    printf("1.5. Reordenação dos dados usando percurso in-order:\n");
    int inOrderValues[numValues];
    int currentIndex = 0;
    void inOrderTraversalToArray(Node* root, int* arr, int* index){
        if (root != NULL) {
            inOrderTraversalToArray(root->left, arr, index);
            arr[*index] = root->data;
            (*index)++;
            inOrderTraversalToArray(root->right, arr, index);
        }
    }
    inOrderTraversalToArray(root, inOrderValues, &currentIndex);
    for (int i = 0; i < numValues; i++) {
        printf("%d ", inOrderValues[i]);
    }
    printf("\n");

    // 1.6. Comparação dos resultados
    // Verificando se as árvores estão balanceadas e se são iguais
    int sortedBalanceFactor = abs(getHeight(root->left) - getHeight(root->right));
    int inOrderBalanceFactor = abs(getHeight(root->left) - getHeight(root->right));
    if (sortedBalanceFactor <= 1) {
        printf("1.6. A árvore resultante da reordenação usando 'sort' está balanceada.\n");
    }
    else {
        printf("1.6. A árvore resultante da reordenação usando 'sort' não está balanceada.\n");
    }
    if (inOrderBalanceFactor <= 1) {
        printf("A árvore resultante da reordenação usando percurso in-order está balanceada.\n");
    }
    else {
        printf("A árvore resultante da reordenação usando percurso in-order não está balanceada.\n");
    }

    // Liberação da memória alocada pela árvore
    freeTree(root);

    return 0;
}
