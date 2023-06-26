#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Grafo {
private:
    unordered_map<string, int> indices;
    vector<string> disciplinas;
    vector<vector<int>> adjacencias;
    vector<int> grauEntrada;

public:
    void adicionarAresta(string origem, string destino) {
        // Verifica se o vértice já foi adicionado
        if (indices.count(origem) == 0) {
            indices[origem] = disciplinas.size();
            disciplinas.push_back(origem);
            adjacencias.emplace_back();
            grauEntrada.push_back(0);
        }
        if (indices.count(destino) == 0) {
            indices[destino] = disciplinas.size();
            disciplinas.push_back(destino);
            adjacencias.emplace_back();
            grauEntrada.push_back(0);
        }

        // Adiciona a aresta no grafo
        int origemIndex = indices[origem];
        int destinoIndex = indices[destino];
        adjacencias[origemIndex].push_back(destinoIndex);
        grauEntrada[destinoIndex]++;
    }

    vector<int> ordenacaoTopologica() {
        queue<int> fila;
        vector<int> ordemTopologica;

        // Encontra os vértices iniciais com grau de entrada zero
        for (int i = 0; i < disciplinas.size(); i++) {
            if (grauEntrada[i] == 0) {
                fila.push(i);
            }
        }

        // Realiza a ordenação topológica
        while (!fila.empty()) {
            int vertice = fila.front();
            fila.pop();
            ordemTopologica.push_back(vertice);

            for (int vizinho : adjacencias[vertice]) {
                grauEntrada[vizinho]--;
                if (grauEntrada[vizinho] == 0) {
                    fila.push(vizinho);
                }
            }
        }

        // Verifica se todos os vértices foram visitados
        if (ordemTopologica.size() != disciplinas.size()) {
            ordemTopologica.clear(); // Retorna um vetor vazio em caso de ciclo
        }

        return ordemTopologica;
    }

    void imprimirOrdemTopologica() {
        vector<int> ordem = ordenacaoTopologica();

        if (!ordem.empty()) {
            cout << "Ordem topológica das disciplinas:" << endl;
            for (int i : ordem) {
                cout << i << ": " << disciplinas[i] << endl;
            }
        }
    }
};

int main() {
    Grafo grafo;

    // Adiciona as arestas com os pré-requisitos
    grafo.adicionarAresta("Arquitetura de Computadores", "Algoritmos");
    grafo.adicionarAresta("Matematica Discreta", "Algoritmos");
    grafo.adicionarAresta("Algoritmos", "Linguagem de Programacao");
    grafo.adicionarAresta("Linguagem de Programacao", "Estrutura de Dados");
    grafo.adicionarAresta("Linguagem de Programacao", "Programacao Orientada a Objetos");
    grafo.adicionarAresta("Estrutura de Dados", "Calculo Numerico Computacional");
    grafo.adicionarAresta("Estrutura de Dados", "Banco de Dados");
    grafo.adicionarAresta("Matematica Discreta", "Calculo 1");
    grafo.adicionarAresta("Calculo 1", "Calculo II");
    grafo.adicionarAresta("Calculo II", "Calculo Numerico Computacional");

    grafo.imprimirOrdemTopologica();

    return 0;
}



// 1 passo
//     Grafo:
//     - Arquitetura de Computadores -> Algoritmos
//     - Algoritmos -> Linguagem de Programação
//     - Linguagem de Programação -> Estrutura de Dados
//     - Linguagem de Programação -> Programação Orientada a Objetos
//     - Estrutura de Dados -> Cálculo Numérico Computacional
//     - Estrutura de Dados -> Banco de Dados
//     - Matemática Discreta -> Algoritmos
//     - Matemática Discreta -> Cálculo 1
//     - Cálculo 1 -> Cálculo II
//     - Cálculo II -> Cálculo Numérico Computacional

//     Ordem Topológica: Arquitetura de Computadores, Matemática Discreta pois são os vértices 0

// 2 passo
//     Grafo:
//     - Algoritmos -> Linguagem de Programação
//     - Linguagem de Programação -> Estrutura de Dados
//     - Linguagem de Programação -> Programação Orientada a Objetos
//     - Estrutura de Dados -> Cálculo Numérico Computacional
//     - Estrutura de Dados -> Banco de Dados
//     - Matemática Discreta -> Algoritmos
//     - Cálculo 1 -> Cálculo II
//     - Cálculo II -> Cálculo Numérico Computacional

// Ordem Topológica: Arquitetura de Computadores, Matemática Discreta

// 3 passo 
//     Grafo:
//     - Algoritmos -> Linguagem de Programação
//     - Linguagem de Programação -> Estrutura de Dados
//     - Linguagem de Programação -> Programação Orientada a Objetos
//     - Estrutura de Dados -> Cálculo Numérico Computacional
//     - Estrutura de Dados -> Banco de Dados
//     - Cálculo 1 -> Cálculo II
//     - Cálculo II -> Cálculo Numérico Computacional

//     Ordem Topológica: Arquitetura de Computadores, Matemática Discreta, Algoritmos, Cálculo 1
//     OBS: Algoritmos e Cálculo 1 são os vértices 1

// 4 passo 
//     Grafo:
//     Ordem Topológica Final: "Matemática Discreta", "Arquitetura de Computadores", "Cálculo 1", 
//     "Algoritmos", "Linguagem de Programação", "Estrutura de Dados", "Cálculo II", 
//     "Cálculo Numérico Computacional", "Banco de Dados", "Programação Orientada a Objetos"