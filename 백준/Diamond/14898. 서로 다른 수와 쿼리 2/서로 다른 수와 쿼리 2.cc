#include<bits/stdc++.h>
using namespace std;
typedef int Integer;
#define ADD_ELEMENT push_back
#define FIRST_ELEMENT first 
#define SECOND_ELEMENT second
 
struct Node {
    Integer left, right, value;
};
 
vector<Node> tree;
void makeNode() {
    tree.ADD_ELEMENT({-1, -1, 0});
}
 
 
void init(Integer start, Integer end, Integer node) {
    if (start == end) return;
    makeNode();
    tree[node].left = tree.size() - 1;
 
    makeNode();
 
    tree[node].right = tree.size() - 1;
 
    init(start, (start + end) / 2, tree[node].left);
    init((start + end) / 2 + 1, end, tree[node].right);
}
 
void update(Integer index, Integer value, Integer start, Integer end, Integer node1, Integer node2) {
    if (index < start || index > end) {
        tree[node2].left = tree[node1].left;
        tree[node2].right = tree[node1].right;
        tree[node2].value = tree[node1].value;
        return;
    }
 
    tree[node2].value = tree[node1].value + value;
    if (start == end) return;
 
    if (index <= (start + end) / 2) {
        tree[node2].right = tree[node1].right;
        makeNode();
        tree[node2].left = tree.size() - 1;
 
        update(index, value, start, (start + end) / 2, tree[node1].left, tree[node2].left);
    }
    else {
        tree[node2].left = tree[node1].left;
        makeNode();
        tree[node2].right = tree.size() - 1;
 
        update(index, value, (start + end) / 2 + 1, end, tree[node1].right, tree[node2].right);
    }
}
 
Integer solve(Integer left, Integer right, Integer start, Integer end, Integer node) {
    if (end < left || right < start) return 0;
    if (left <= start && end <= right) return tree[node].value;
    return solve(left, right, start, (start + end) / 2, tree[node].left) +
           solve(left, right, (start + end) / 2 + 1, end, tree[node].right);
}
 
Integer arr[1010101];
vector<Integer> v[1000101];
vector<Integer> uniqueNums;
 
int main() {
    Integer i, j, k, l, m, n;      
    scanf("%d", &n);
    tree.reserve(12500000);
    for (i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        uniqueNums.ADD_ELEMENT(arr[i]);
    }
    sort(uniqueNums.begin(), uniqueNums.end());
    uniqueNums.erase(unique(uniqueNums.begin(), uniqueNums.end()), uniqueNums.end());
 
    for (i = 1; i <= n; i++)
        arr[i] = lower_bound(uniqueNums.begin(), uniqueNums.end(), arr[i]) - uniqueNums.begin();
    for (i = 0; i <= n; i++)
        v[i].ADD_ELEMENT(0);
 
    for (i = 1; i <= n; i++)
        v[arr[i]].ADD_ELEMENT(i);
 
    for (i = 0; i <= n; i++)
        for (j = 1; j < v[i].size(); j++)
            arr[v[i][j]] = v[i][j - 1];
 
    Integer count = 0;
 
    for (i = 0; i <= 2 * n; i++)
        makeNode();
    init(1, n, 0);
 
    for (i = 1; i <= n; i++) {
        if (arr[i]) {
            count++;
            update(arr[i], -1, 1, n, count - 1, count);
        }
        count++;
        update(i, 1, 1, n, count - 1, count);
        v[i][0] = count;
    }
    Integer q;
    Integer last = 0;
    scanf("%d", &q);
    solve(1, 1, 1, n, 2);
   
    while (q--) {
        Integer a, b;
        scanf("%d %d", &a, &b);
        last = solve(a + last, b, 1, n, v[b][0]);
        printf("%d\n", last);
    }   
}