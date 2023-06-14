#include <bits/stdc++.h>
using namespace std;

using cdbl = complex<long double>;

const long double PI = acos(-1.0L);

inline unsigned bitreverse(const unsigned n, const unsigned k) {
    unsigned r, i;
    for (r = 0, i = 0; i < k; ++i)
        r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}

void fft(vector<cdbl>& a, bool is_reverse = false) {
    const unsigned n = a.size(), k = __builtin_ctz(n);
    unsigned s, i, j;
    for (i = 0; i < n; i++) {
        j = bitreverse(i, k);
        if (i < j)
            swap(a[i], a[j]);
    }
    for (s = 2; s <= n; s *= 2) {
        vector<cdbl> w(s / 2);
        for (i = 0; i < s / 2; i++) {
            long double t = 2 * PI * i / s * (is_reverse ? -1 : 1);
            w[i] = cdbl(cos(t), sin(t));
        }
        for (i = 0; i < n; i += s) {
            for (j = 0; j < s / 2; j++) {
                cdbl tmp = a[i + j + s / 2] * w[j];
                a[i + j + s / 2] = a[i + j] - tmp;
                a[i + j] += tmp;
            }
        }
    }
    if (is_reverse)
        for (i = 0; i < n; i++)
            a[i] /= n;
}

void convolution(vector<cdbl>& a, vector<cdbl>& b) {
    const unsigned n = a.size();
    fft(a);
    fft(b);
    for (unsigned i = 0; i < n; i++)
        a[i] *= b[i];
    fft(a, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unsigned n, m;
    cin >> n >> m;
    n++;
    m++;

    unsigned np = 1;
    for (; np < 2 * max(n, m) - 1; np *= 2);

    vector<cdbl> a(np, 0), b(np, 0);
    for (unsigned i = 0; i < n; i++)
        cin >> a[i];
    for (unsigned i = 0; i < m; i++)
        cin >> b[i];

    convolution(a, b);

    unsigned long long res = 0;
    for (unsigned i = 0; i < n + m - 1; i++)
        res ^= static_cast<unsigned long long>(a[i].real() + (a[i].real() > 0 ? 0.5L : -0.5L));

    cout << res;

    return 0;
}
