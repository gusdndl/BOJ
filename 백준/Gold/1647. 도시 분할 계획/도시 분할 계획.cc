#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
    int u, v, w;
    bool operator<(const edge &a) const {
        return w < a.w;
    }
};

int p[100001];
vector<edge> e;

int find(int u) {
    if(u == p[u]) return u;
    return p[u] = find(p[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    p[u] = v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for(int i=1; i<=n; i++) {
        p[i] = i;
    }

    for(int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({u, v, w});
    }

    sort(e.begin(), e.end());

    int sum = 0, maxEdge = 0;
    for(auto &i : e) {
        if(find(i.u) != find(i.v)) {
            sum += i.w;
            maxEdge = max(maxEdge, i.w);
            merge(i.u, i.v);
        }
    }

    cout << sum - maxEdge;

    return 0;
}
