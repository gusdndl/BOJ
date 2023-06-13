#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1e18

using namespace std;
typedef pair<long long, pair<int, int>> plii;
vector<pair<int, int>> adj[10001];
long long dist[10001][21];
int N, M, K;

void dijkstra() {
    priority_queue<plii, vector<plii>, greater<plii>> pq;
    pq.push({0, {1, 0}});
    dist[1][0] = 0;
    
    while(!pq.empty()) {
        long long d = pq.top().first;
        int v = pq.top().second.first;
        int k = pq.top().second.second;
        pq.pop();
        
        if(dist[v][k] < d) continue;
        
        for(auto i : adj[v]) {
            int nxt = i.first;
            int cost = i.second;
            if(dist[nxt][k] > dist[v][k] + cost) {
                dist[nxt][k] = dist[v][k] + cost;
                pq.push({dist[nxt][k], {nxt, k}});
            }
            if(k < K && dist[nxt][k+1] > dist[v][k]) {
                dist[nxt][k+1] = dist[v][k];
                pq.push({dist[nxt][k+1], {nxt, k+1}});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K;
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    
    for(int i=1; i<=N; i++)
        for(int j=0; j<=K; j++)
            dist[i][j] = INF;
    
    dijkstra();
    
    long long res = INF;
    for(int i=0; i<=K; i++)
        res = min(res, dist[N][i]);
    
    cout << res;
    
    return 0;
}
