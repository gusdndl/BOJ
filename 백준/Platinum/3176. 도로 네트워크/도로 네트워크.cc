#include<bits/stdc++.h>
using namespace std;
#define MAXN 100010
#define MAXK 20

int N, depth[MAXN], parent[MAXK][MAXN], mini[MAXK][MAXN], maxi[MAXK][MAXN];
vector<pair<int,int>> adj[MAXN];

void dfs(int u, int p, int d, int w){
    depth[u] = d;
    parent[0][u] = p;
    mini[0][u] = maxi[0][u] = w;
    for(auto& e : adj[u]){
        int v = e.first;
        int wv = e.second;
        if(v != p) dfs(v, u, d + 1, wv);
    }
}

void build(){
    dfs(1, 0, 1, 0);
    for(int k = 1; k < MAXK; k++){
        for(int i = 1; i <= N; i++){
            parent[k][i] = parent[k-1][parent[k-1][i]];
            mini[k][i] = min(mini[k-1][i], mini[k-1][parent[k-1][i]]);
            maxi[k][i] = max(maxi[k-1][i], maxi[k-1][parent[k-1][i]]);
        }
    }
}

pair<int,int> query(int u, int v){
    int minRes = INT_MAX, maxRes = INT_MIN;
    if(depth[u] < depth[v]) swap(u, v);
    for(int k = MAXK - 1; k >= 0; k--){
        if(depth[u] - (1 << k) >= depth[v]){
            minRes = min(minRes, mini[k][u]);
            maxRes = max(maxRes, maxi[k][u]);
            u = parent[k][u];
        }
    }
    if(u == v) return {minRes, maxRes};
    for(int k = MAXK - 1; k >= 0; k--){
        if(parent[k][u] != parent[k][v]){
            minRes = min({minRes, mini[k][u], mini[k][v]});
            maxRes = max({maxRes, maxi[k][u], maxi[k][v]});
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    minRes = min({minRes, mini[0][u], mini[0][v]});
    maxRes = max({maxRes, maxi[0][u], maxi[0][v]});
    return {minRes, maxRes};
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    for(int i = 0; i < N - 1; i++){
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    build();
    int Q; cin >> Q;
    while(Q--){
        int u, v;
        cin >> u >> v;
        pair<int,int> res = query(u, v);
        cout << res.first << " " << res.second << "\n";
    }
    return 0;
}
