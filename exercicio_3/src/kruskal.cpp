#include "kruskal.h"
#include <algorithm>
#include <numeric>

// Implementação já com union_by_rank

struct UnionFind {
    std::vector<int> pai, rank;

    UnionFind(int n) {
        pai.resize(n);
        rank.assign(n, 0);
        std::iota(pai.begin(), pai.end(), 0);
    }

    int find(int i) {
        if (pai[i] == i)
            return i;
        return pai[i] = find(pai[i]);
    }

    bool unite(int i, int j) {
        int raiz_i = find(i);
        int raiz_j = find(j);

        if (raiz_i != raiz_j) {
            if (rank[raiz_i] < rank[raiz_j]) {
                pai[raiz_i] = raiz_j;
            } else if (rank[raiz_i] > rank[raiz_j]) {
                pai[raiz_j] = raiz_i;
            } else {
                pai[raiz_j] = raiz_i;
                rank[raiz_i]++;
            }
            return true;
        }
        return false;
    }
};

int execKruskal(int n, std::vector<Aresta>& arestas) {
    std::sort(arestas.begin(), arestas.end());
    
    UnionFind uf(n);
    int custo_mst = 0;
    int arestas_adicionadas = 0;

    for (const auto& aresta : arestas) {
        if (uf.unite(aresta.u, aresta.v)) {
            custo_mst += aresta.peso;
            arestas_adicionadas++;
            
            if (arestas_adicionadas == n - 1) {
                break;
            }
        }
    }
    
    return custo_mst;
}