#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> segtree;
vector<int> nums;

void build(int node, int start, int end) {
    if (start == end) {
        // Leaf node
        segtree[node] = (nums[start] > 0) ? 1 : ((nums[start] < 0) ? -1 : 0);
        return;
    }

    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    segtree[node] = segtree[2 * node] * segtree[2 * node + 1];
}

int query(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        // Completely outside the range
        return 1;
    }

    if (left <= start && right >= end) {
        // Completely inside the range
        return segtree[node];
    }

    int mid = (start + end) / 2;
    int leftProduct = query(2 * node, start, mid, left, right);
    int rightProduct = query(2 * node + 1, mid + 1, end, left, right);

    return leftProduct * rightProduct;
}

void update(int node, int start, int end, int idx, int value) {
    if (start == end) {
        // Leaf node
        segtree[node] = (value > 0) ? 1 : ((value < 0) ? -1 : 0);
        return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid) {
        // Update left subtree
        update(2 * node, start, mid, idx, value);
    } else {
        // Update right subtree
        update(2 * node + 1, mid + 1, end, idx, value);
    }

    segtree[node] = segtree[2 * node] * segtree[2 * node + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    while (cin >> n >> k) {
        nums.resize(n);
        segtree.resize(4 * n);

        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }

        build(1, 0, n - 1);

        char queryType;
        int left, right;
        for (int i = 0; i < k; i++) {
            cin >> queryType >> left >> right;

            if (queryType == 'C') {
                update(1, 0, n - 1, left - 1, right);
            } else if (queryType == 'P') {
                int product = query(1, 0, n - 1, left - 1, right - 1);
                if (product > 0) {
                    cout << "+";
                } else if (product < 0) {
                    cout << "-";
                } else {
                    cout << "0";
                }
            }
        }

        cout << "\n";
    }

    return 0;
}
