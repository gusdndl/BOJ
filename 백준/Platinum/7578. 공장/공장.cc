#include<bits/stdc++.h>
using namespace std;

#define MAX 1000001

int n, a[MAX], b[MAX], c[MAX];
long long tree[MAX];

long long sum(int i) {
    long long ans = 0;
    while(i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}

void update(int i, int diff) {
    while(i <= n) {
        tree[i] += diff;
        i += (i & -i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        c[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        b[i] = c[b[i]];
    }
    long long ans = 0;
    for(int i = n; i >= 1; i--) {
        ans += sum(b[i]-1);
        update(b[i], 1);
    }
    cout << ans;

    return 0;
}
