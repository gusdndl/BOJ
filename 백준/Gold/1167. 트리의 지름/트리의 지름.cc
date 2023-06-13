#include<bits/stdc++.h>
using namespace std;

const int MAX = 100000;
vector<pair<int, int>> tree[MAX + 1];
bool visited[MAX + 1];
int furthestNode = 0, diameter = 0;

void dfs(int node, int cost) {
    visited[node] = true;

    if(diameter < cost) {
        diameter = cost;
        furthestNode = node;
    }

    for(int i = 0; i < tree[node].size(); i++) {
        int nextNode = tree[node][i].first;
        int nextCost = tree[node][i].second;
        if(!visited[nextNode]) {
            dfs(nextNode, cost + nextCost);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V;
    cin >> V;

    for(int i = 1; i <= V; i++) {
        int node;
        cin >> node;
        while(true) {
            int a, b;
            cin >> a;
            if(a == -1) break;
            cin >> b;
            tree[node].push_back({a, b});
        }
    }

    dfs(1, 0);
    memset(visited, false, sizeof(visited));
    diameter = 0;
    dfs(furthestNode, 0);

    cout << diameter << "\n";

    return 0;
}
