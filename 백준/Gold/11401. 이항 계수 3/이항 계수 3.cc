#include <iostream>

#define MAX 4000000
#define MOD 1000000007

using namespace std;

typedef long long ll;

ll fact[MAX+1];
ll inv[MAX+1];

ll power(ll x, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2) {
            res *= x;
            res %= MOD;
        }
        x *= x;
        x %= MOD;
        y /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fact[0] = 1;
    fact[1] = 1;
    inv[0] = 1;
    inv[1] = 1;
    for (int i = 2; i <= MAX; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
        inv[i] = power(fact[i], MOD-2);
    }

    int n, k;
    cin >> n >> k;
    ll ans = (fact[n] * inv[k]) % MOD;
    ans = (ans * inv[n-k]) % MOD;
    cout << ans << '\n';

    return 0;
}
