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

// Função para imprimir o grafo
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("Adjacências do vértice %d: ", v);
        while (pCrawl) {
            printf("%d ", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
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
    
    // Imprimindo o grafo
    printGraph(graph);
    
    return 0;
}
