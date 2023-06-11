#include <bits/stdc++.h>
#define MAX 4000000
#define MOD 1000000007
using namespace std;
using ll = long long;

ll fact[MAX + 1], invFact[MAX + 1];

ll power(ll x, ll y) {
    ll ret = 1;
    while (y > 0) {
        if (y % 2) ret = ret * x % MOD;
        y /= 2;
        x = x * x % MOD;
    }
    return ret;
}

void precalc() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = power(fact[i], MOD - 2);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precalc();

    int m;
    cin >> m;
    while (m--) {
        int n, k;
        cin >> n >> k;
        cout << fact[n] * invFact[k] % MOD * invFact[n - k] % MOD << '\n';
    }
    
    return 0;
}
