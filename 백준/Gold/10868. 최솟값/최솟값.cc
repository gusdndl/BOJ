#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1e9;

vector<int> segtree;
vector<int> nums;

void build(int node, int start, int end) {
    if (start == end) {
        // Leaf node
        segtree[node] = nums[start];
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    segtree[node] = min(segtree[2 * node], segtree[2 * node + 1]);
}

int query(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        // Completely outside the range
        return INF;
    }

    if (left <= start && right >= end) {
        // Completely inside the range
        return segtree[node];
    }

    int mid = (start + end) / 2;
    int leftMin = query(2 * node, start, mid, left, right);
    int rightMin = query(2 * node + 1, mid + 1, end, left, right);

    return min(leftMin, rightMin);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    nums.resize(n);
    segtree.resize(4 * n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int left, right;
        cin >> left >> right;

        int minVal = query(1, 0, n - 1, left - 1, right - 1);
        cout << minVal << "\n";
    }

    return 0;
}
