#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> tree[40001];
int depth[40001], dist[40001], parent[40001][20];
int N, M;

void dfs(int node, int d, int p, int dis){
    depth[node] = d;
    parent[node][0] = p;
    dist[node] = dis;
    for(auto it : tree[node]){
        if(it.first == p) continue;
        dfs(it.first, d+1, node, dis+it.second);
    }
}

void f(){
    for(int j=1;j<20;j++){
        for(int i=1;i<=N;i++){
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }
}

int lca(int x, int y){
    if(depth[x] > depth[y]) swap(x, y);
    for(int i=19;i>=0;i--){
        if(depth[y] - depth[x] >= (1 << i)){
            y = parent[y][i];
        }
    }
    if(x == y) return x;
    for(int i=19;i>=0;i--){
        if(parent[x][i] != parent[y][i]){
            x = parent[x][i];
            y = parent[y][i];
        }
    }
    return parent[x][0];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    for(int i=1;i<N;i++){
        int a, b, c; cin>>a>>b>>c;
        tree[a].push_back({b, c});
        tree[b].push_back({a, c});
    }
    dfs(1, 0, 0, 0);
    f();
    cin>>M;
    while(M--){
        int a, b; cin>>a>>b;
        int LCA = lca(a, b);
        cout<<dist[a] + dist[b] - 2*dist[LCA]<<'\n';
    }
    return 0;
}
