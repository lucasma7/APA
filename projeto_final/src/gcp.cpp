#include "gcp.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <cstdlib> // para rand()

using namespace std;

Graph readDIMACSInstance(const string& filePath) {
    ifstream file(filePath);
    string line;
    Graph g = {0, 0, {}, {}};

    if (!file.is_open()) return g;

    while (getline(file, line)) {
        if (line.empty() || line[0] == 'c') continue; // Ignora comentarios

        if (line[0] == 'p') {
            string temp, type;
            stringstream ss(line);
            ss >> temp >> type >> g.numVertices >> g.numEdges;
            g.adj.resize(g.numVertices + 1);
            g.degree.assign(g.numVertices + 1, 0);
        } 
        else if (line[0] == 'e') {
            char e;
            int u, v;
            stringstream ss(line);
            ss >> e >> u >> v;
            g.adj[u].push_back(v);
            g.adj[v].push_back(u);
            g.degree[u]++;
            g.degree[v]++;
        }
    }
    return g;
}

vector<int> welshPowellHeuristic(const Graph& g) {
    vector<int> colors(g.numVertices + 1, 0);
    vector<int> order(g.numVertices);
    
    // Inicializa a ordem com os indices dos vertices
    for (int i = 0; i < g.numVertices; i++) order[i] = i + 1;
    
    // Ordena os vertices por grau decrescente
    sort(order.begin(), order.end(), [&](int a, int b) {
        return g.degree[a] > g.degree[b];
    });

    for (int v : order) {
        vector<bool> forbiddenColor(g.numVertices + 1, false);
        for (int neighbor : g.adj[v]) {
            if (colors[neighbor] != 0) forbiddenColor[colors[neighbor]] = true;
        }

        int chosenColor = 1;
        while (forbiddenColor[chosenColor]) chosenColor++;
        
        colors[v] = chosenColor;
    }
    return colors;
}

vector<int> dsaturHeuristic(const Graph& g) {
    vector<int> colors(g.numVertices + 1, 0);
    vector<set<int>> adjColors(g.numVertices + 1); 
    vector<bool> uncolored(g.numVertices + 1, true);
    
    int coloredCount = 0;

    
    int maxDegree = -1;
    int firstVertex = -1;
    for (int v = 1; v <= g.numVertices; v++) {
        if (g.degree[v] > maxDegree) {
            maxDegree = g.degree[v];
            firstVertex = v;
        }
    }

   
    colors[firstVertex] = 1;
    uncolored[firstVertex] = false;
    coloredCount++;
    for (int neighbor : g.adj[firstVertex]) {
        adjColors[neighbor].insert(1);
    }

   
    while (coloredCount < g.numVertices) {
        int maxSat = -1;
        int maxDeg = -1;
        int chosenVertex = -1;

        
        for (int v = 1; v <= g.numVertices; v++) {
            if (uncolored[v]) {
                int sat = adjColors[v].size();
                if (sat > maxSat || (sat == maxSat && g.degree[v] > maxDeg)) {
                    maxSat = sat;
                    maxDeg = g.degree[v];
                    chosenVertex = v;
                }
            }
        }

        vector<bool> forbidden(g.numVertices + 1, false);
        for (int neighbor : g.adj[chosenVertex]) {
            if (colors[neighbor] != 0) {
                forbidden[colors[neighbor]] = true;
            }
        }

        int c = 1;
        while (forbidden[c]) c++;

        colors[chosenVertex] = c;
        uncolored[chosenVertex] = false;
        coloredCount++;

        for (int neighbor : g.adj[chosenVertex]) {
            if (uncolored[neighbor]) {
                adjColors[neighbor].insert(c);
            }
        }
    }

    return colors;
}

pair<int, long long> evaluateSolution(const vector<int>& colors, int numVertices) {
    vector<int> classSize(numVertices + 1, 0);
    for (int v = 1; v <= numVertices; v++) {
        classSize[colors[v]]++;
    }

    int colorCount = 0;
    long long sumOfSquares = 0;
    for (int c = 1; c <= numVertices; c++) {
        if (classSize[c] > 0) {
            colorCount++;
            sumOfSquares += (long long)classSize[c] * classSize[c];
        }
    }
    return {colorCount, sumOfSquares};
}


static bool isValidColor(const Graph& g, const vector<int>& colors, int v, int newColor) {
    for (int neighbor : g.adj[v]) {
        if (colors[neighbor] == newColor) return false;
    }
    return true;
}

static bool n1_changeColor(const Graph& g, vector<int>& colors, long long& bestSumSquares) {
    for (int v = 1; v <= g.numVertices; v++) {
        int originalColor = colors[v];
        for (int c = 1; c <= g.numVertices; c++) {
            if (c == originalColor) continue;

            if (isValidColor(g, colors, v, c)) {
                colors[v] = c;
                auto [newColorCount, newSum] = evaluateSolution(colors, g.numVertices);
                
                // Estrategia First Improvement
                if (newSum > bestSumSquares) {
                    bestSumSquares = newSum;
                    return true;
                }
                colors[v] = originalColor; // Desfaz o movimento
            }
        }
    }
    return false;
}

static bool n2_swapColors(const Graph& g, vector<int>& colors, long long& bestSumSquares) {
    for (int u = 1; u <= g.numVertices; u++) {
        for (int v = u + 1; v <= g.numVertices; v++) {
            if (colors[u] == colors[v]) continue;

            // Verifica se os vertices nao sao vizinhos entre si
            bool areNeighbors = false;
            for (int neighbor : g.adj[u]) {
                if (neighbor == v) { areNeighbors = true; break; }
            }
            if (areNeighbors) continue;

            int colorU = colors[u];
            int colorV = colors[v];

            // Verifica se a troca nao gera conflitos
            bool isValidSwap = true;
            for (int neighbor : g.adj[u]) if (colors[neighbor] == colorV && neighbor != v) isValidSwap = false;
            for (int neighbor : g.adj[v]) if (colors[neighbor] == colorU && neighbor != u) isValidSwap = false;

            if (isValidSwap) {
                colors[u] = colorV;
                colors[v] = colorU;
                
                auto [newColorCount, newSum] = evaluateSolution(colors, g.numVertices);
                
                if (newSum > bestSumSquares) {
                    bestSumSquares = newSum;
                    return true;
                }
                
                // Desfaz o movimento
                colors[u] = colorU;
                colors[v] = colorV;
            }
        }
    }
    return false;

}
static bool n3_kempeChain(const Graph& g, vector<int>& colors, long long& bestSumSquares) {
    // ALOCAÇÃO ÚNICA: Alocamos o vetor de visitados fora dos loops para poupar a RAM!
    vector<bool> visited(g.numVertices + 1, false);

    for (int u = 1; u <= g.numVertices; u++) {
        int colorU = colors[u];
        
        for (int neighbor : g.adj[u]) {
            int colorV = colors[neighbor];
            if (colorU == colorV) continue;

            vector<int> kempeChain;
            queue<int> q;
            
            q.push(u);
            visited[u] = true;

            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                kempeChain.push_back(curr);

                for (int adjVertex : g.adj[curr]) {
                    if (!visited[adjVertex] && (colors[adjVertex] == colorU || colors[adjVertex] == colorV)) {
                        visited[adjVertex] = true;
                        q.push(adjVertex);
                    }
                }
            }

            // Inverte as cores da cadeia e FAZ O RESET RÁPIDO do visited
            for (int vertex : kempeChain) {
                colors[vertex] = (colors[vertex] == colorU) ? colorV : colorU;
                visited[vertex] = false; // Reset O(k) ao invés de O(V)! Isso muda tudo!
            }

            auto [newColorCount, newSum] = evaluateSolution(colors, g.numVertices);
            
            if (newSum > bestSumSquares) {
                bestSumSquares = newSum;
                return true;
            }

            // Desfaz o movimento
            for (int vertex : kempeChain) {
                colors[vertex] = (colors[vertex] == colorU) ? colorV : colorU;
            }
        }
    }
    return false;
}

void executeVND(const Graph& g, vector<int>& colors, int targetColors) {
    auto evaluation = evaluateSolution(colors, g.numVertices);
    long long bestSumSquares = evaluation.second;

    int k = 1;
    while (k <= 3) {
        // EARLY STOP: Se já bateu na meta durante o VND, para imediatamente!
        if (evaluateSolution(colors, g.numVertices).first <= targetColors) return;

        bool improved = false;
        if (k == 1) improved = n1_changeColor(g, colors, bestSumSquares);
        else if (k == 2) improved = n2_swapColors(g, colors, bestSumSquares);
        else if (k == 3) improved = n3_kempeChain(g, colors, bestSumSquares);

        if (improved) k = 1;
        else k++;
    }
}

/*vector<int> executeILS(const Graph& g, vector<int> initialSolution, int maxIters, int targetColors) {
    srand(42); 
    vector<int> currentSolution = initialSolution;
    vector<int> bestSolution = initialSolution;
    
    // 1. Otimiza a solução inicial com VND
    executeVND(g, currentSolution, targetColors); 
    
    auto bestEval = evaluateSolution(currentSolution, g.numVertices);
    int bestColorCount = bestEval.first;
    long long bestSumSquares = bestEval.second;
    bestSolution = currentSolution;

    // EARLY STOP: Se o DSatur + 1º VND já resolveu (ex: grafos fpsol), nem entra no loop pesado do ILS!
    if (bestColorCount <= targetColors) return bestSolution;

    for (int iter = 0; iter < maxIters; iter++) {
        vector<int> perturbedSolution = currentSolution;
        
        // PERTURBAÇÃO: Altera 10% do grafo
        int numPerturbations = max(1, g.numVertices / 10);
        for (int p = 0; p < numPerturbations; p++) {
            int randomVertex = (rand() % g.numVertices) + 1;
            vector<bool> forbidden(g.numVertices + 1, false);
            for (int neighbor : g.adj[randomVertex]) forbidden[perturbedSolution[neighbor]] = true;
            
            int randomColor = 1;
            while (forbidden[randomColor] || randomColor == perturbedSolution[randomVertex]) randomColor++;
            perturbedSolution[randomVertex] = randomColor;
        }

        // BUSCA LOCAL
        executeVND(g, perturbedSolution, targetColors);
        
        auto newEval = evaluateSolution(perturbedSolution, g.numVertices);
        int newColorCount = newEval.first;
        long long newSumSquares = newEval.second;

        if (newColorCount < bestColorCount || (newColorCount == bestColorCount && newSumSquares > bestSumSquares)) {
            currentSolution = perturbedSolution;
            bestSolution = perturbedSolution;
            bestColorCount = newColorCount;
            bestSumSquares = newSumSquares;
        }

        // EARLY STOP: Se achou o ótimo no meio do loop, sai!
        if (bestColorCount <= targetColors) break;
    }
    
    return bestSolution;
}*/


bool solveTabuCOLForK(const Graph& g, int k, int maxIters, vector<int>& outColors) {
    vector<int> colors(g.numVertices + 1);
    
    vector<vector<int>> gamma(g.numVertices + 1, vector<int>(k + 1, 0));
    int totalConflicts = 0;

    
    for (int i = 1; i <= g.numVertices; i++) {
        colors[i] = (rand() % k) + 1;
    }

    
    for (int i = 1; i <= g.numVertices; i++) {
        for (int adj : g.adj[i]) {
            gamma[i][colors[adj]]++;
            if (i < adj && colors[i] == colors[adj]) totalConflicts++;
        }
    }

    // tabu[v][c] = iteração até a qual é proibido atribuir a cor 'c' ao vértice 'v'
    vector<vector<int>> tabu(g.numVertices + 1, vector<int>(k + 1, 0));

    int bestConflicts = totalConflicts;
    vector<int> bestColors = colors;
    int iter = 0;

    while (iter < maxIters && bestConflicts > 0) {
        int bestDelta = 1e9;
        vector<pair<int, int>> bestMoves; 

        for (int v = 1; v <= g.numVertices; v++) {
            if (gamma[v][colors[v]] > 0) {
                for (int c = 1; c <= k; c++) {
                    if (c == colors[v]) continue;

                    int delta = gamma[v][c] - gamma[v][colors[v]];
                    bool isTabu = tabu[v][c] > iter;

    
                    if (!isTabu || (totalConflicts + delta < bestConflicts)) {
                        if (delta < bestDelta) {
                            bestDelta = delta;
                            bestMoves.clear();
                            bestMoves.push_back({v, c});
                        } else if (delta == bestDelta) {
                            bestMoves.push_back({v, c});
                        }
                    }
                }
            }
        }

        if (bestMoves.empty()) {
            iter++;
            continue;
        }

        auto move = bestMoves[rand() % bestMoves.size()];
        int v = move.first;
        int newColor = move.second;
        int oldColor = colors[v];


        colors[v] = newColor;
        totalConflicts += bestDelta;


        for (int adj : g.adj[v]) {
            gamma[adj][oldColor]--;
            gamma[adj][newColor]++;
        }

        // Atualiza a Lista Tabu: Proíbe voltar para a cor antiga.
        // O tempo de punição é dinâmico (randômico + proporcional aos conflitos)
        int tenure = (rand() % 10) + (totalConflicts * 0.6); 
        tabu[v][oldColor] = iter + tenure;

        if (totalConflicts < bestConflicts) {
            bestConflicts = totalConflicts;
            bestColors = colors;
        }

        iter++;
    }

    outColors = bestColors;
    return bestConflicts == 0; // Sucesso se zerou os conflitos!
}

vector<int> executeTabuCOL(const Graph& g, vector<int> initialColors, int targetColors) {
    int currentK = evaluateSolution(initialColors, g.numVertices).first;
    vector<int> bestValidColoring = initialColors;

    
    while (currentK > targetColors) {
        int testK = currentK - 1;
        vector<int> candidateColors;
        
        bool success = solveTabuCOLForK(g, testK, 100000, candidateColors);

        if (success) {
            bestValidColoring = candidateColors;
            currentK = testK;           
        } else {
            // Se bateu na barreira e não conseguiu achar com testK, interrompe.
            break; 
        }
    }
    
    return bestValidColoring;
}