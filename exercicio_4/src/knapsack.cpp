#include "knapsack.h"
#include <vector>
#include <algorithm>

using namespace std;

backtracking execKnapsack(int n, int M, const vector<int>& weights, const vector<int>& values) {
    vector<vector<int>> K(n + 1, vector<int>(M + 1, 0));

    // Aqui está sendo executada a PD
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= M; w++) {
            if (weights[i - 1] <= w) {
                K[i][w] = max(values[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    //  Backtracking
    vector<int> itens;
    int rest_cost = M;
    

    for (int i = n; i > 0 && rest_cost > 0; i--) {
        if (K[i][rest_cost] != K[i - 1][rest_cost]) {
            itens.push_back(i);
            rest_cost -= weights[i - 1];
        }
    }
    reverse(itens.begin(), itens.end());

    return {K[n][M], itens};
}