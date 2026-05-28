#include <iostream>
#include <vector>
#include <chrono>
#include "kruskal.h"
#include "prim.h"
#include "dijkstra.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n;

    if (!(cin >> n)) {
        return 1;
    }

    vector<vector<pair<int, int>>> adjLista(n);
    vector<Aresta> arestas;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int peso;
            cin >> peso;
            
            if (peso > 0) {
                arestas.push_back({i, j, peso});
                adjLista[i].push_back({j, peso});
                adjLista[j].push_back({i, peso});
            }
        }
    }

    // --- KRUSKAL ---
    auto inicioK = high_resolution_clock::now();
    int custoKruskal = execKruskal(n, arestas);
    auto fimK = high_resolution_clock::now();
    auto duracaoK = duration_cast<microseconds>(fimK - inicioK);

    // --- PRIM ---
    auto inicioP = high_resolution_clock::now();
    int custoPrim = execPrim(n, adjLista);
    auto fimP = high_resolution_clock::now();
    auto duracaoP = duration_cast<microseconds>(fimP - inicioP);

    // --- DIJKSTRA ---
    auto inicioD = high_resolution_clock::now();
    vector<int> distancias = execDijkstra(n, 0, adjLista);
    auto fimD = high_resolution_clock::now();
    auto duracaoD = duration_cast<microseconds>(fimD - inicioD);

    // Formatação de saída limpa para o relatório
    cout << "MST: " << custoKruskal 
         << " | Caminho Minimo (0->" << n-1 << "): " << distancias[n-1] 
         << " | (Kruskal: " << duracaoK.count() << " us"
         << " | Prim: " << duracaoP.count() << " us"
         << " | Dijkstra: " << duracaoD.count() << " us)";

    return 0;
}