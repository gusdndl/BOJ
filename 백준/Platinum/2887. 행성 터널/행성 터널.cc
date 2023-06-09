#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Planet {
    int x, y, z, id;
};

struct Edge {
    int u, v, w;
    bool operator <(const Edge& e) {
        return w < e.w;
    }
};

vector<int> parent;

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) parent[u] = v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<Planet> planets(N);
    vector<Edge> edges;
    parent = vector<int>(N);

    for (int i = 0; i < N; ++i) {
        cin >> planets[i].x >> planets[i].y >> planets[i].z;
        planets[i].id = i;
        parent[i] = i;
    }

    for (int i = 0; i < 3; ++i) {
        sort(planets.begin(), planets.end(), [i](Planet& a, Planet& b) {
            return (i == 0 ? a.x < b.x : (i == 1 ? a.y < b.y : a.z < b.z));
        });

        for (int j = 1; j < N; ++j) {
            edges.push_back({planets[j-1].id, planets[j].id,
                             abs((i == 0 ? planets[j-1].x - planets[j].x : (i == 1 ? planets[j-1].y - planets[j].y : planets[j-1].z - planets[j].z)))});
        }
    }

    sort(edges.begin(), edges.end());
    int total_cost = 0;

    for (auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            merge(edge.u, edge.v);
            total_cost += edge.w;
        }
    }

    cout << total_cost;

    return 0;
}
