#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int n, m, k, q, d[111111], res[111111];
vector<vector<pair<int, int>>> adj;
set<int> st[111111];
int parent[111111];
pair<int, pair<int, int>> edges[211111];

int findParent(int x) {
    return (x == parent[x]) ? x : (parent[x] = findParent(parent[x]));
}

void merge(int x, int y) {
    x = findParent(x);
    y = findParent(y);
    parent[x] = y;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &q);
    adj.resize(n + 1);
    
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
        edges[i].second = {x, y};
    }
    
    memset(d, -1, sizeof(d));
    priority_queue<pair<int, int>> pq;
    
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        pq.push({0, x});
    }
    
    while (!pq.empty()) {
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
        
        if (d[here] != -1)
            continue;
        
        d[here] = cost;
        
        for (auto next : adj[here]) {
            if (d[next.first] == -1)
                pq.push({-next.second - cost, next.first});
        }
    }
    
    for (int i = 1; i <= q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        st[x].insert(i);
        st[y].insert(i);
    }
    
    for (int i = 0; i < m; i++)
        edges[i].first = -min(d[edges[i].second.first], d[edges[i].second.second]);
    
    sort(edges, edges + m);
    
    for (int i = 0; i < m; i++) {
        int lo = findParent(edges[i].second.first);
        int hi = findParent(edges[i].second.second);
        
        if (lo == hi)
            continue;
        
        if (st[lo].size() > st[hi].size())
            swap(lo, hi);
        
        for (auto next : st[lo]) {
            if (st[hi].count(next)) {
                res[next] = -edges[i].first;
                st[hi].erase(next);
            }
            else {
                st[hi].insert(next);
            }
        }
        
        merge(lo, hi);
    }
    
    for (int i = 1; i <= q; i++)
        printf("%d\n", res[i]);
    
    return 0;
}
