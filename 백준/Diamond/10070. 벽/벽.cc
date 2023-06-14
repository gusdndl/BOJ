#include<cstdio>
#include<algorithm>

using namespace std;

const int MAXIMUM = 2e6, INFINITY = 1e5;
int num, iterations;

struct SegmentTree {
    int lower, upper;
    SegmentTree operator+(SegmentTree input) {
        return{ min(max(lower,input.lower),input.upper), min(max(upper,input.lower),input.upper) };
    }
} tree[MAXIMUM * 4];

void updateTree(int index, int left, int right, int gl, int gr, SegmentTree x) {
    if (right < gl || gr < left) return;
    if (left != right) {
        tree[index * 2 + 1] = tree[index * 2 + 1] + tree[index];
        tree[index * 2 + 2] = tree[index * 2 + 2] + tree[index];
        tree[index] = { 0, INFINITY };
    }
    if (gl <= left && right <= gr) tree[index] = tree[index] + x;
    else {
        updateTree(index * 2 + 1, left, (left + right) / 2, gl, gr, x);
        updateTree(index * 2 + 2, (left + right) / 2 + 1, right, gl, gr, x);
    }
}

SegmentTree queryTree(int index, int left, int right, int g) {
    if (right < g || g < left) return{ 0, INFINITY };
    if (left == right) return tree[index];
    return queryTree(index * 2 + 1, left, (left + right) / 2, g) + queryTree(index * 2 + 2, (left + right) / 2 + 1, right, g) + tree[index];
}

int main() {
    for (scanf("%d%d", &num, &iterations); iterations--;) {
        int operation, left, right, height;
        scanf("%d%d%d%d", &operation, &left, &right, &height);
        if (operation == 1) updateTree(0, 0, num - 1, left, right, { height, INFINITY });
        else updateTree(0, 0, num - 1, left, right, { 0, height });
    }
    for (int i = 0; i < num; i++) printf("%d\n", queryTree(0, 0, num - 1, i).upper);
    return 0;
}
