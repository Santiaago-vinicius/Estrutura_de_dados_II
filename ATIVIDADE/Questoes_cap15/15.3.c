#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura de um nó da lista de adjacências
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Definindo a estrutura de uma lista de adjacências
struct AdjList {
    struct AdjListNode* head;
};

// Definindo a estrutura do grafo
struct Graph {
    int V;
    struct AdjList* array;
};

// Função para criar um novo nó da lista de adjacências
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com V vértices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    
    // Alocando memória para o array de listas de adjacências
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    // Inicializando cada lista de adjacências como vazia
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Função para adicionar uma aresta ao grafo direcionado
void addEdge(struct Graph* graph, int src, int dest) {
    // Adicionando uma aresta de src para dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Para um grafo não direcionado, é necessário adicionar também uma aresta de dest para src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Função auxiliar recursiva para exibir todos os caminhos possíveis entre src e dest
void printAllPathsUtil(struct Graph* graph, int src, int dest, int* visited, int* path, int pathIndex) {
    // Marcar o vértice atual como visitado e adicioná-lo ao caminho
    visited[src] = 1;
    path[pathIndex] = src;
    pathIndex++;

    // Se o vértice atual é o destino, imprimir o caminho
    if (src == dest) {
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        // Recursivamente encontrar todos os caminhos possíveis a partir dos vértices adjacentes não visitados
        struct AdjListNode* currentNode = graph->array[src].head;
        while (currentNode != NULL) {
            int adjacentVertex = currentNode->dest;
            if (!visited[adjacentVertex]) {
                printAllPathsUtil(graph, adjacentVertex, dest, visited, path, pathIndex);
            }
            currentNode = currentNode->next;
        }
    }

    // Marcar o vértice atual como não visitado e remover do caminho
    visited[src] = 0;
    pathIndex--;
}

// Função para exibir todos os caminhos possíveis entre src e dest
void printAllPaths(struct Graph* graph, int src, int dest) {
    // Array para marcar os vértices visitados
    int* visited = (int*)calloc(graph->V, sizeof(int));

    // Array para armazenar o caminho atual
    int* path = (int*)malloc(graph->V * sizeof(int));
    int pathIndex = 0;

    // Chamar a função auxiliar recursiva para exibir todos os caminhos possíveis
    printAllPathsUtil(graph, src, dest, visited, path, pathIndex);

    free(visited);
    free(path);
}

int main() {
    int V = 6; // Número de vértices

    struct Graph* graph = createGraph(V);

    // Adicionando as arestas do grafo
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);

    // Exibindo todos os caminhos do vértice 0 ao vértice 5
    printf("Todos os caminhos do vértice 0 ao vértice 5:\n");
    printAllPaths(graph, 0, 5);

    return 0;
}
