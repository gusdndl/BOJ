#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_NODES = 200000;
const int MAX_WEIGHT = 1000000;
const int INF = 1e9;

vector<int> subtreeSize(MAX_NODES + 5);
bool visited[MAX_NODES + 5];
vector<int> minDepth(MAX_WEIGHT + 5);
vector<vector<pair<int, int>>> graph(MAX_NODES + 5);
int numNodes, maxDistance;

int getSize(int cur, int par) {
    subtreeSize[cur] = 1;
    for (const auto& [next, _] : graph[cur]) {
        if (next == par || visited[next]) continue;
        subtreeSize[cur] += getSize(next, cur);
    }
    return subtreeSize[cur];
}

int getCentroid(int cur, int par, int threshold) {
    for (const auto& [next, _] : graph[cur]) {
        if (next == par || visited[next]) continue;
        if (subtreeSize[next] > threshold) return getCentroid(next, cur, threshold);
    }
    return cur;
}

int solve(int cur, int par, int distance, int depth) {
    int result = INF;
    if (distance > maxDistance) return result;
    result = min(result, minDepth[maxDistance - distance] + depth);
    for (const auto& [next, weight] : graph[cur]) {
        if (next == par || visited[next]) continue;
        result = min(result, solve(next, cur, distance + weight, depth + 1));
    }
    return result;
}

void update(int cur, int par, int distance, int depth) {
    if (distance > maxDistance) return;
    minDepth[distance] = min(minDepth[distance], depth);
    for (const auto& [next, weight] : graph[cur]) {
        if (next == par || visited[next]) continue;
        update(next, cur, distance + weight, depth + 1);
    }
}

int divideAndConquer(int cur) {
    int threshold = getSize(cur, -1);
    int centroid = getCentroid(cur, -1, threshold / 2);
    visited[centroid] = true;
    int result = INF;
    fill(minDepth.begin(), minDepth.end(), INF);
    minDepth[0] = 0;
    for (const auto& [next, weight] : graph[centroid]) {
        if (!visited[next]) {
            result = min(result, solve(next, centroid, weight, 1));
            update(next, centroid, weight, 1);
        }
    }
    for (const auto& [next, _] : graph[centroid]) {
        if (visited[next]) continue;
        result = min(result, divideAndConquer(next));
    }
    return result;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> numNodes >> maxDistance;
    for (int i = 0; i < numNodes - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    int answer = divideAndConquer(0);
    cout << (answer == INF ? -1 : answer) << '\n';
    return 0;
}
