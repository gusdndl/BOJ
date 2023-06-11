#include<bits/stdc++.h>
using namespace std;

#define MAXN 100001
#define MAXK 21

vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXK][MAXN];

void dfs(int node, int par){
    depth[node] = depth[par] + 1;
    parent[0][node] = par;
    for(int next : adj[node]){
        if(next == par) continue;
        dfs(next, node);
    }
}

void fillParent(int n){
    for(int i = 1; i < MAXK; i++){
        for(int j = 1; j <= n; j++){
            parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }
}

int lca(int u, int v){
    if(depth[u] < depth[v]) swap(u, v);
    int log = 1;
    for(; (1<<log) <= depth[u]; log++);
    log -= 1;

    for(int i = log; i >= 0; i--){
        if(depth[u] - (1<<i) >= depth[v]){
            u = parent[i][u];
        }
    }

    if(u == v) return u;

    for(int i = log; i >= 0; i--){
        if(parent[i][u] != parent[i][v]){
            u = parent[i][u];
            v = parent[i][v];
        }
    }
    return parent[0][u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[0] = -1;
    dfs(1, 0);
    fillParent(n);

    int m; cin >> m;
    while(m--){
        int u, v; cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
