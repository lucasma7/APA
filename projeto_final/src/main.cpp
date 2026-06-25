#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <unordered_map>
#include "gcp.h"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

int main() {
    string dirInstances = "instances";
    string dirResults = "results";

    // Mapa dos Melhores Resultados Conhecidos (BKS) da Literatura
    unordered_map<string, int> bks_map = {
        {"mulsol.i.1", 49}, {"mulsol.i.2", 31}, {"mulsol.i.3", 31},
        {"mulsol.i.4", 31}, {"mulsol.i.5", 31}, {"fpsol2.i.1", 65},
        {"fpsol2.i.2", 30}, {"fpsol2.i.3", 30}, {"le450_15c", 15},
        {"DSJC500.5.col", 48}
    };

    if (!fs::exists(dirResults)) fs::create_directory(dirResults);
    if (!fs::exists(dirInstances) || fs::is_empty(dirInstances)) {
        cerr << "Erro: Pasta 'instances' nao encontrada." << endl;
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(dirInstances)) {
        if (!entry.is_regular_file()) continue;

        string filePath = entry.path().string();
        string instanceName = entry.path().stem().string(); 
        
        // Define a meta (Se a instância não estiver no mapa, o default é 1, forçando o ILS a rodar tudo)
        int targetColors = bks_map.count(instanceName) ? bks_map[instanceName] : 1;

        cout << "Processando: " << instanceName << " [Target: " << targetColors << "] ... ";

        Graph g = readDIMACSInstance(filePath);
        if (g.numVertices == 0) continue;

        auto startTime = high_resolution_clock::now();
        
        vector<int> solution = dsaturHeuristic(g);
        int initialColors = evaluateSolution(solution, g.numVertices).first;

        solution = executeTabuCOL(g, solution, targetColors); 
        int finalColors = evaluateSolution(solution, g.numVertices).first;

        auto endTime = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(endTime - startTime).count();

        string resultPath = dirResults + "/" + instanceName + "_result.txt";
        ofstream resultFile(resultPath);

        if (resultFile.is_open()) {
            resultFile << "Instancia: " << instanceName << "\n";
            resultFile << "Vertices: " << g.numVertices << "\n";
            resultFile << "Arestas: " << g.numEdges << "\n";
            resultFile << "Cores Solucao Inicial (DSatur): " << initialColors << "\n";
            resultFile << "Cores Solucao Final (Apos ILS+VND): " << finalColors << "\n";
            resultFile << "Target BKS: " << targetColors << "\n";
            resultFile << "Tempo Computacional (ms): " << duration << "\n";
            resultFile.close();
            
            cout << "Concluido! (" << duration << " ms) -> " << finalColors << " cores" << endl;
        }
    }
    return 0;
}