#ifndef GCP_H
#define GCP_H

#include <vector>
#include <string>
#include <utility>

// Estrutura representativa do Grafo (Lista de Adjacencia)
struct Graph {
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> adj;
    std::vector<int> degree;
};


Graph readDIMACSInstance(const std::string& filePath);
std::vector<int> welshPowellHeuristic(const Graph& g);
std::pair<int, long long> evaluateSolution(const std::vector<int>& colors, int numVertices);
void executeVND(const Graph& g, std::vector<int>& colors, int targetColors);
std::vector<int> executeTabuCOL(const Graph& g, std::vector<int> initialColors, int targetColors);
std::vector<int> executeILS(const Graph& g, std::vector<int> initialSolution, int maxIters, int targetColors);
std::vector<int> dsaturHeuristic(const Graph& g);


#endif // GCP_H