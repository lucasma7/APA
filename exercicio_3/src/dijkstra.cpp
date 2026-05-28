#include "dijkstra.h"
#include <queue>

const int INF = 1e9;

std::vector<int> execDijkstra(int n, int origem, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<int> dist(n, INF);
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[origem] = 0;
    pq.push({0, origem});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& vizinho : adj[u]) {
            int v = vizinho.first;
            int peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}