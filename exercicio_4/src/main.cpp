#include <iostream>
#include <vector>
#include <chrono>
#include "knapsack.h"

using namespace std;
using namespace std::chrono;

int main() {
    int n, M;

    if (!(cin >> n >> M)) {
        return 1;
    }

    vector<int> weights(n);
    vector<int> values(n);

    for (int i = 0; i < n; i++) {
        cin >> weights[i] >> values[i];
    }

    auto start = high_resolution_clock::now();
    backtracking results = execKnapsack(n, M, weights, values);
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);

    cout << results.solValue << " | Itens: [";
    for (size_t i = 0; i < results.itens.size(); i++) {
        cout << results.itens[i];
        if (i < results.itens.size() - 1) cout << ", ";
    }
    cout << "] (" << duration.count() << " us)";

    return 0;
}