#include <iostream>
#include <map>
#include <cstring>
#define MAX 200010
using namespace std;

int parent[MAX], friends[MAX];

int find(int u) {
    if(u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    parent[u] = v;
    friends[v] += friends[u];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while(T--) {
        int F;
        cin >> F;
        for(int i=1; i<=2*F; i++) {
            parent[i] = i;
            friends[i] = 1;
        }
        map<string, int> m;
        int idx = 1;
        for(int i=0; i<F; i++) {
            string u, v;
            cin >> u >> v;
            if(m.count(u) == 0) m[u] = idx++;
            if(m.count(v) == 0) m[v] = idx++;
            merge(m[u], m[v]);
            cout << friends[find(m[u])] << '\n';
        }
    }
    return 0;
}
