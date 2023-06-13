#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N, Q;
vector<ll> seg;

ll update(int idx, ll val, int node, int x, int y) {
    if (idx < x || y < idx) return seg[node];
    if (x == y) return seg[node] += val;
    int mid = (x + y) >> 1;
    return seg[node] = update(idx, val, node * 2, x, mid) + update(idx, val, node * 2 + 1, mid + 1, y);
}

ll query(int lo, int hi, int node, int x, int y) {
    if (y < lo || hi < x) return 0;
    if (lo <= x && y <= hi) return seg[node];
    int mid = (x + y) >> 1;
    return query(lo, hi, node * 2, x, mid) + query(lo, hi, node * 2 + 1, mid + 1, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> Q;
    seg.resize(4 * N);
    
    while (Q--) {
        int a, b, c; cin >> a >> b >> c;
        if (a == 1) {
            update(b, c, 1, 1, N);
        } else if (a == 2) {
            cout << query(b, c, 1, 1, N) << "\n";
        }
    }

    return 0;
}
