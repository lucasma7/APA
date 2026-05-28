#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>

struct Aresta {
    int u, v, peso;

    bool operator<(const Aresta& outra) const {
        return peso < outra.peso;
    }
};

int execKruskal(int n, std::vector<Aresta>& arestas);

#endif