#include "prim.h"
#include <queue>

const int INF = 1e8;

int execPrim(int n, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<int> chave(n, INF);
    std::vector<bool> naMST(n, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int custo_mst = 0;
    chave[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int peso_atual = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (naMST[u]) continue;

        naMST[u] = true;
        custo_mst += peso_atual;

        for (const auto& vizinho : adj[u]) {
            int v = vizinho.first;
            int peso = vizinho.second;

            if (!naMST[v] && peso < chave[v]) {
                chave[v] = peso;
                pq.push({chave[v], v});
            }
        }
    }

    return custo_mst;
}