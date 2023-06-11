#include <bits/stdc++.h>
using namespace std;
#define MAX 100001

int parent[MAX], diff[MAX];

int find(int x) {
    if (x == parent[x]) return x;
    int prev = find(parent[x]);
    diff[x] += diff[parent[x]];
    return parent[x] = prev;
}

void merge(int x, int y, int z) {
    int X = find(x);
    int Y = find(y);
    if (X == Y) return;
    parent[Y] = X;
    diff[Y] = diff[x] - diff[y] + z;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (true) {
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) break;

        for (int i = 1; i <= n; ++i) {
            parent[i] = i; diff[i] = 0;
        }

        while (m--) {
            char cmd; cin >> cmd;
            if (cmd == '!') {
                int x, y, z; cin >> x >> y >> z;
                merge(x, y, z);
            }
            else {
                int x, y; cin >> x >> y;
                if (find(x) == find(y)) cout << diff[y] - diff[x] << '\n';
                else cout << "UNKNOWN" << '\n';
            }
        }
    }
    return 0;
}
