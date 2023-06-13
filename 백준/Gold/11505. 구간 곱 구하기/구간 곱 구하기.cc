#include <iostream>
#include <vector>
#include <cmath>
#define MOD 1000000007LL

using namespace std;

typedef long long ll;

vector<ll> arr, tree;

ll init(int start, int end, int node) {
    if(start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = (init(start, mid, node * 2) * init(mid + 1, end, node * 2 + 1)) % MOD;
}

ll update(int start, int end, int node, int index, ll value) {
    if(index < start || index > end) return tree[node];
    if(start == end) return tree[node] = value;
    int mid = (start + end) / 2;
    return tree[node] = (update(start, mid, node * 2, index, value) * update(mid + 1, end, node * 2 + 1, index, value)) % MOD;
}

ll query(int start, int end, int node, int left, int right) {
    if(right < start || left > end) return 1;
    if(left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return (query(start, mid, node * 2, left, right) * query(mid + 1, end, node * 2 + 1, left, right)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    arr.resize(n);
    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));
    tree.resize(tree_size);

    for(int i = 0; i < n; i++) cin >> arr[i];

    init(0, n - 1, 1);

    for(int i = 0; i < m + k; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1) {
            update(0, n - 1, 1, b - 1, c);
            arr[b - 1] = c;
        } else if(a == 2) {
            cout << query(0, n - 1, 1, b - 1, c - 1) << "\n";
        }
    }

    return 0;
}
