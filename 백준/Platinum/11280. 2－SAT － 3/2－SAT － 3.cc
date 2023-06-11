#include <bits/stdc++.h>
using namespace std;

vector<int> adj[20002];
stack<int> stk;
int id[20002], finished[20002];
int SCCId[20002];
vector<vector<int>> SCC;
int N, M, vertexNum, SCCNum;

inline int NOT(int x) { return x^1; }
inline int TRUE(int x) { return 2*x; }
inline int FALSE(int x) { return 2*x+1; }

int dfs(int x) {
    id[x] = ++vertexNum;
    stk.push(x);

    int ret = id[x];
    for(int nx : adj[x]) {
        if(id[nx] == 0) ret = min(ret, dfs(nx));
        else if(!finished[nx]) ret = min(ret, id[nx]);
    }

    if(ret == id[x]) {
        vector<int> currSCC;
        while(1) {
            int t = stk.top(); stk.pop();
            currSCC.push_back(t);
            finished[t] = true;
            SCCId[t] = SCCNum;
            if(t == x) break;
        }
        SCCNum++;
        SCC.push_back(currSCC);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        u = (u < 0) ? FALSE(-u) : TRUE(u);
        v = (v < 0) ? FALSE(-v) : TRUE(v);
        adj[NOT(u)].push_back(v);
        adj[NOT(v)].push_back(u);
    }

    for(int i=2; i<=2*N+1; ++i)
        if(id[i] == 0) dfs(i);

    for(int i=1; i<=N; ++i) {
        if(SCCId[TRUE(i)] == SCCId[FALSE(i)]) {
            cout << 0;
            return 0;
        }
    }

    cout << 1;
    return 0;
}
