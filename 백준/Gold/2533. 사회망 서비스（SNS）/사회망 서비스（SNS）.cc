#include<bits/stdc++.h>
using namespace std;
#define MAX 1000001

vector<int> adj[MAX];
int dp[MAX][2];
bool visited[MAX];
int n;

void dfs(int node){
    visited[node] = true;
    dp[node][0] = 0;
    dp[node][1] = 1;
    for(auto next : adj[node]){
        if(visited[next]) continue;
        dfs(next);
        dp[node][0] += dp[next][1];
        dp[node][1] += min(dp[next][0], dp[next][1]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    cout << min(dp[1][0], dp[1][1]) << "\n";
    
    return 0;
}
