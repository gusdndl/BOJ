#include<bits/stdc++.h>
using namespace std;
#define MAX 1000000
typedef long long ll;

vector<ll> tree;

void update(int node, int start, int end, int index, ll diff) {
    if (index < start || index > end)
        return;
    tree[node] += diff;
    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, index, diff);
        update(node * 2 + 1, mid + 1, end, index, diff);
    }
}

int query(int node, int start, int end, int k) {
    if (start == end)
        return start;
    int mid = (start + end) / 2;
    if (k <= tree[node * 2])
        return query(node * 2, start, mid, k);
    else
        return query(node * 2 + 1, mid + 1, end, k - tree[node * 2]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    tree.resize(4 * (MAX + 1), 0);
    
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            int b;
            cin >> b;
            int flavor = query(1, 1, MAX, b);
            cout << flavor << '\n';
            update(1, 1, MAX, flavor, -1);
        }
        else if (a == 2) {
            int b, c;
            cin >> b >> c;
            update(1, 1, MAX, b, c);
        }
    }
    
    return 0;
}
