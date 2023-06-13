#include <iostream>
#include <vector>

using namespace std;

vector<long long> arr;
vector<long long> tree;

long long init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
    }
}

long long sum(int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return sum(node * 2, start, mid, left, right) + sum(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int index, long long diff) {
    if (index < start || index > end) {
        return;
    }
    tree[node] += diff;
    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, index, diff);
        update(node * 2 + 1, mid + 1, end, index, diff);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    arr.resize(n + 1);
    tree.resize(4 * (n + 1));
    
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    init(1, 1, n);
    
    for (int i = 0; i < q; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        
        if (x > y) {
            swap(x, y);
        }
        
        cout << sum(1, 1, n, x, y) << '\n';
        
        long long diff = b - arr[a];
        arr[a] = b;
        update(1, 1, n, a, diff);
    }
    
    return 0;
}
