#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Node {
    Node() {}
    Node(ll min_val, ll max_val, ll sum_val) : min_val(min_val), max_val(max_val), sum_val(sum_val) {}
    ll min_val, max_val, sum_val;
} tree[1 << 18];

ll tmp1[1 << 18], tmp2[1 << 18];

Node merge(Node a, Node b) {
    return {min(a.min_val, b.min_val), max(a.max_val, b.max_val), a.sum_val + b.sum_val};
}

void push(int node, int start, int end) {
    if (tmp2[node] <= -INF) {
        tree[node].max_val += tmp1[node];
        tree[node].min_val += tmp1[node];
        tree[node].sum_val += (end - start + 1) * tmp1[node];
        if (start != end) {
            tmp1[node * 2] += tmp1[node];
            tmp1[node * 2 + 1] += tmp1[node];
        }
    } else {
        tree[node].max_val = tree[node].min_val = tmp1[node] + tmp2[node];
        tree[node].sum_val = (end - start + 1) * (tmp1[node] + tmp2[node]);
        if (start != end) {
            tmp1[node * 2] = tmp1[node];
            tmp1[node * 2 + 1] = tmp1[node];
            tmp2[node * 2] = tmp2[node];
            tmp2[node * 2 + 1] = tmp2[node];
        }
    }
    tmp1[node] = 0, tmp2[node] = -INF;
}

void add(int node, int start, int end, int left, int right, ll value) {
    push(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tmp1[node] = value;
        push(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    add(node * 2, start, mid, left, right, value);
    add(node * 2 + 1, mid + 1, end, left, right, value);
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

void divide(int node, int start, int end, int left, int right, ll divisor) {
    push(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        if (floor((double)tree[node].min_val / divisor) == floor((double)tree[node].max_val / divisor)) {
            tmp2[node] = floor((double)tree[node].min_val / divisor);
            push(node, start, end);
            return;
        }
        if (tree[node].min_val + 1 == tree[node].max_val) {
            tmp1[node] = floor((double)tree[node].min_val / divisor) - tree[node].min_val;
            push(node, start, end);
            return;
        }
    }
    int mid = (start + end) / 2;
    divide(node * 2, start, mid, left, right, divisor);
    divide(node * 2 + 1, mid + 1, end, left, right, divisor);
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

Node query(int node, int start, int end, int left, int right) {
    push(node, start, end);
    if (right < start || end < left) return {INF, -INF, 0};
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return merge(query(node * 2, start, mid, left, right), query(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < (1 << 18); i++) tmp2[i] = -INF;
    int numElements, numQueries;
    cin >> numElements >> numQueries;
    for (int i = 0; i < numElements; i++) {
        int value;
        cin >> value;
        add(1, 0, numElements - 1, i, i, value);
    }
    while (numQueries--) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            ll left, right, value;
            cin >> left >> right >> value;
            add(1, 0, numElements - 1, left, right, value);
        } else if (operation == 2) {
            ll left, right, divisor;
            cin >> left >> right >> divisor;
            divide(1, 0, numElements - 1, left, right, divisor);
        } else {
            int left, right;
            cin >> left >> right;
            Node result = query(1, 0, numElements - 1, left, right);
            if (operation == 3)
                cout << result.min_val << "\n";
            else
                cout << result.sum_val << "\n";
        }
    }
    return 0;
}
