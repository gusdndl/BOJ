#include <string>
#include <vector>
#include <cstdint>

using namespace std;

struct ImplicitTreap {
    struct Node {
        long long val;
        long long sum;
        int sz;
        int l;
        int r;
        uint32_t pri;
    };

    vector<Node> tree;
    int root = 0;
    uint32_t seed = 2463534242u;

    ImplicitTreap() {
        tree.push_back({0, 0, 0, 0, 0, 0});
    }

    uint32_t rnd() {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        return seed;
    }

    int size(int x) const {
        return x ? tree[x].sz : 0;
    }

    long long sum(int x) const {
        return x ? tree[x].sum : 0;
    }

    int newNode(long long v) {
        tree.push_back({v, v, 1, 0, 0, rnd()});
        return (int)tree.size() - 1;
    }

    void pull(int x) {
        if (!x) return;
        tree[x].sz = size(tree[x].l) + size(tree[x].r) + 1;
        tree[x].sum = sum(tree[x].l) + sum(tree[x].r) + tree[x].val;
    }

    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;

        if (tree[a].pri > tree[b].pri) {
            tree[a].r = merge(tree[a].r, b);
            pull(a);
            return a;
        } else {
            tree[b].l = merge(a, tree[b].l);
            pull(b);
            return b;
        }
    }

    void split(int x, int k, int &a, int &b) {
        if (!x) {
            a = b = 0;
            return;
        }

        if (size(tree[x].l) >= k) {
            split(tree[x].l, k, a, tree[x].l);
            b = x;
            pull(b);
        } else {
            split(tree[x].r, k - size(tree[x].l) - 1, tree[x].r, b);
            a = x;
            pull(a);
        }
    }

    void build(const vector<long long> &arr) {
        root = 0;
        for (long long v : arr) {
            root = merge(root, newNode(v));
        }
    }

    long long pointValue(int idx) const {
        int x = root;

        while (x) {
            int leftSize = size(tree[x].l);

            if (idx < leftSize) {
                x = tree[x].l;
            } else if (idx == leftSize) {
                return tree[x].val;
            } else {
                idx -= leftSize + 1;
                x = tree[x].r;
            }
        }

        return 0;
    }

    long long rangeSum(int l, int r) {
        int a, b, c;

        split(root, l, a, b);
        split(b, r - l + 1, b, c);

        long long ret = sum(b);

        root = merge(a, merge(b, c));
        return ret;
    }

    void eraseAndInsert(int l, int r, long long val) {
        int a, b, c, mid;

        split(root, r, a, b);
        split(b, 1, mid, c);

        root = merge(a, c);

        tree[mid].val = val;
        tree[mid].l = 0;
        tree[mid].r = 0;
        pull(mid);

        split(root, l, a, b);
        root = merge(merge(a, mid), b);
    }
};

vector<long long> solution(vector<int> values, vector<vector<int>> edges, vector<vector<int>> queries) {
    vector<long long> answer;

    int n = (int)values.size();
    if (n == 0) return answer;

    vector<vector<int>> graph(n + 1);

    for (const auto &e : edges) {
        int a = e[0];
        int b = e[1];

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    vector<int> st;
    st.push_back(1);

    while (!st.empty()) {
        int node = st.back();
        st.pop_back();

        order.push_back(node);

        for (int next : graph[node]) {
            if (next == parent[node]) continue;

            parent[next] = node;
            depth[next] = depth[node] + 1;
            st.push_back(next);
        }
    }

    vector<int> subtreeSize(n + 1, 1);
    vector<int> heavy(n + 1, 0);

    for (int i = n - 1; i >= 0; --i) {
        int node = order[i];
        subtreeSize[node] = 1;

        int bestSize = 0;

        for (int next : graph[node]) {
            if (parent[next] != node) continue;

            subtreeSize[node] += subtreeSize[next];

            if (subtreeSize[next] > bestSize) {
                bestSize = subtreeSize[next];
                heavy[node] = next;
            }
        }
    }

    vector<int> head(n + 1, 0);
    vector<int> pos(n + 1, 0);

    int cur = 0;

    vector<int> nodeStack;
    vector<int> headStack;

    nodeStack.push_back(1);
    headStack.push_back(1);

    while (!nodeStack.empty()) {
        int node = nodeStack.back();
        int chainHead = headStack.back();

        nodeStack.pop_back();
        headStack.pop_back();

        while (node != 0) {
            head[node] = chainHead;
            pos[node] = cur++;

            for (int next : graph[node]) {
                if (parent[next] == node && next != heavy[node]) {
                    nodeStack.push_back(next);
                    headStack.push_back(next);
                }
            }

            node = heavy[node];
        }
    }

    vector<long long> base(n);

    for (int node = 1; node <= n; ++node) {
        base[pos[node]] = values[node - 1];
    }

    ImplicitTreap treap;
    treap.build(base);

    for (const auto &query : queries) {
        int node = query[0];
        int q = query[1];

        if (q == -1) {
            int l = pos[node];
            int r = pos[node] + subtreeSize[node] - 1;

            answer.push_back(treap.rangeSum(l, r));
        } else {
            int curNode = node;

            while (head[curNode] != 1) {
                int chainHead = head[curNode];
                int chainParent = parent[chainHead];

                long long insertValue = treap.pointValue(pos[chainParent]);

                treap.eraseAndInsert(pos[chainHead], pos[curNode], insertValue);

                curNode = chainParent;
            }

            treap.eraseAndInsert(pos[1], pos[curNode], q);
        }
    }

    return answer;
}