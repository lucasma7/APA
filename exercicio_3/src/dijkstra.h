#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>

std::vector<int> execDijkstra(int n, int origem, const std::vector<std::vector<std::pair<int, int>>>& adj);

#endif