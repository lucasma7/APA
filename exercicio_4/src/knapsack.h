#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

struct backtracking {
    int solValue;
    std::vector<int> itens;
};

backtracking execKnapsack(int n, int M, const std::vector<int>& weights, const std::vector<int>& values);

#endif