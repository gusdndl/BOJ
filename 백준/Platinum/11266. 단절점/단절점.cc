#include<bits/stdc++.h>
using namespace std;

const int MAX = 10001;
int V, E, order[MAX], orderCnt, ans;
vector<int> adj[MAX];
bool isCut[MAX];

int dfs(int cur, bool isRoot, int parent) {
    order[cur] = ++orderCnt;
    int ret = order[cur];

    int childCnt = 0;
    for (int next : adj[cur]) {
        if (next == parent) continue;
        if (order[next]) {
            ret = min(ret, order[next]);
            continue;
        }
        int prev = dfs(next, false, cur);
        if (!isRoot && prev >= order[cur]) isCut[cur] = true;
        ret = min(ret, prev);
        childCnt++;
    }
    if (isRoot && childCnt >= 2) isCut[cur] = true;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    for (int i = 1; i <= V; i++) {
        if (order[i]) continue;
        dfs(i, true, 0);
    }
    for (int i = 1; i <= V; i++) ans += isCut[i];
    cout << ans << "\n";
    for (int i = 1; i <= V; i++) {
        if (isCut[i]) cout << i << " ";
    }
    return 0;
}
