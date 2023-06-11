#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100001];
int visitOrder[100001];
int order;
vector<pair<int, int>> bridges;

int dfs(int curr, int parent) {
    visitOrder[curr] = ++order;
    int ret = visitOrder[curr];

    for (int next : adj[curr]) {
        if (next == parent) continue;
        if (visitOrder[next]) {
            ret = min(ret, visitOrder[next]);
            continue;
        }
        int low = dfs(next, curr);
        if (low > visitOrder[curr]) {
            bridges.push_back(minmax(curr, next));
        }
        ret = min(ret, low);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int V, E;
    cin >> V >> E;
    for (int i = 0; i < E; ++i) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    for (int i = 1; i <= V; ++i) {
        if (!visitOrder[i]) {
            dfs(i, 0);
        }
    }
    sort(bridges.begin(), bridges.end());
    cout << bridges.size() << "\n";
    for (auto& bridge : bridges) {
        cout << bridge.first << " " << bridge.second << "\n";
    }
    return 0;
}
