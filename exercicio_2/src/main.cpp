#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <filesystem>
#include "sort_algorithms.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./programa <arquivo_entrada> [algoritmo]\n";
        std::cerr << "Algoritmos: insertion | selection\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string algorithm = (argc >= 3) ? argv[2] : "all";

    if (algorithm != "all" && algorithm != "merge" && algorithm != "quick") {
        std::cerr << "Algoritmo inválido\n";
        return 1;
    }
    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir arquivo\n";
        return 1;
    }

    int n;
    input >> n;

    std::vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        input >> numbers[i];
    }

    std::vector<int> original = numbers;

    std::filesystem::path inputPath(inputFile);
    std::string fileName = inputPath.filename().string();

    // Garante que pasta output existe
    std::filesystem::create_directories("output");

    /////////////////////////////////////// INSERTION SORT ///////////////////////////////////////
    if (algorithm == "insertion" || algorithm == "all") {
        std::vector<int> arr = original;

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, n - 1);;
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Tempo (mergeSort): " << duration.count() << " ms\n";

        std::ofstream output("output/" + fileName + "_insertion.output");

        if (!output.is_open()) {
            std::cerr << "Erro ao criar arquivo de saída (insertion)\n";
            return 1;
        }

        for (int i = 0; i < n; i++) {
            output << arr[i] << "\n";
        }

        output << "\nTempo(ms): " << duration.count() << "\n";
    }

    /////////////////////////////////////// SELECTION SORT ///////////////////////////////////////
    if (algorithm == "selection" || algorithm == "all") {
        std::vector<int> arr = original;

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Tempo (quickSort): " << duration.count() << " ms\n";

        std::ofstream output("output/" + fileName + "_selection.output");

        if (!output.is_open()) {
            std::cerr << "Erro ao criar arquivo de saída (selection)\n";
            return 1;
        }

        for (int i = 0; i < n; i++) {
            output << arr[i] << "\n";
        }

        output << "\nTempo(ms): " << duration.count() << "\n";
    }

    return 0;
}