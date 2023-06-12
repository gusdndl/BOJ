#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct Edge {
    int from, to;
    double weight;
};

struct DisjointSet {
    vector<int> parent;
    DisjointSet(int n) : parent(n) {
        for(int i=0; i<n; i++) 
            parent[i] = i;
    }
    int find(int u) {
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v) {
        u = find(u); v = find(v);
        parent[u] = v;
    }
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout<<fixed;
    cout.precision(2);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> gods(N+1);
    for(int i=1; i<=N; i++) 
        cin >> gods[i].first >> gods[i].second;
    
    vector<Edge> edges;
    for(int i=1; i<=N; i++)
        for(int j=i+1; j<=N; j++)
            edges.push_back({i, j, sqrt(pow(gods[i].first-gods[j].first, 2) + pow(gods[i].second-gods[j].second, 2))});
    sort(edges.begin(), edges.end(), compare);
    
    DisjointSet sets(N+1);
    for(int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        sets.merge(a, b);
    }

    double result = 0.0;
    for(auto &e: edges) {
        if(sets.find(e.from) == sets.find(e.to)) continue;
        result += e.weight;
        sets.merge(e.from, e.to);
    }
    
    cout << result << '\n';

    return 0;
}
