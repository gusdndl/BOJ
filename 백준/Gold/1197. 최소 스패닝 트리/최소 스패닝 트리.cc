#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int parent[10001];

struct Edge {
    int from, to, cost;
};

bool compare(Edge a, Edge b) {
    return a.cost < b.cost;
}

int find(int x) {
    if(x == parent[x]) {
        return x;
    } else {
        return parent[x] = find(parent[x]);
    }
}

void union_set(int x, int y) {
    x = find(x);
    y = find(y);
    if(x != y) {
        parent[y] = x;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<Edge> edges(E);
    
    for(int i=0; i<E; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }
    
    for(int i=1; i<=V; i++) {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end(), compare);
    
    int answer = 0;
    for(int i=0; i<E; i++) {
        if(find(edges[i].from) != find(edges[i].to)) {
            union_set(edges[i].from, edges[i].to);
            answer += edges[i].cost;
        }
    }

    cout << answer;
    return 0;
}
