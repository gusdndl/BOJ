#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll MOD = 1e9 + 7;
const int MAXN = 1e5;
const int INF = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define SZ(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define COMPRESS(v) sort(ALL(v)); v.erase(unique(ALL(v)), v.end())
#define RESET(X) memset(X, 0, sizeof(X))
#define PB push_back
#define FI first
#define SE second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpii vector<pair<int, int>>
#define vpll vector<pair<ll,ll>>
#define endl "\n"
#define LOG 18

ld a, b, c;

ld f(ld s, ld t) {
    ld at = pow(a, t);
    ld bt = pow(b, t);
    ld as = pow(a, s);
    ld bs = pow(b, s);
    return at * bt * (bs - as) / (bs * bt - as * at);
}

ld val(ld s, ld t) {
    ld fval = f(s, t);
    return t * fval - s * c * (1 - fval);
}

void solve() {
    ld x, p;
    cin >> x >> p;
    p = p / 100;

    a = (1 + sqrt(1 - 4 * p * (1 - p))) / (2 * (1 - p));
    b = (1 - sqrt(1 - 4 * p * (1 - p))) / (2 * (1 - p));
    c = 1 - x / 100;

    ld maxv = 0;
    int maxt = 1;
    int maxs = 1;

    for (int i = 1; i <= 2498; i += 10) {
        for (int j = 1; j <= 20528; j += 10) {
            ld temp = val(j, i);
            if (temp >= maxv) {
                maxv = temp;
                maxt = i;
                maxs = j;
            }
        }
    }

    for (int i = max(1, maxt - 10); i <= maxt + 10; i++) {
        for (int j = max(1, maxs - 10); j <= maxs + 10; j++) {
            maxv = max(maxv, val(j, i));
        }
    }

    cout << fixed << setprecision(7) << maxv << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    t = 1;
    while (t--) {
        solve();
    }
}
