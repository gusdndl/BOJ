#include <bits/stdc++.h>
using namespace std;

int main() {
    long long T;
    int n, m;
    cin >> T;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    cin >> m;
    vector<int> B(m);
    for (int i = 0; i < m; i++)
        cin >> B[i];

    vector<long long> sumA, sumB;
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += A[j];
            sumA.push_back(sum);
        }
    }
    for (int i = 0; i < m; i++) {
        long long sum = 0;
        for (int j = i; j < m; j++) {
            sum += B[j];
            sumB.push_back(sum);
        }
    }

    sort(sumA.begin(), sumA.end());
    sort(sumB.begin(), sumB.end());

    long long ans = 0;
    for (int i = 0; i < sumA.size(); i++) {
        auto lo = lower_bound(sumB.begin(), sumB.end(), T - sumA[i]);
        auto hi = upper_bound(sumB.begin(), sumB.end(), T - sumA[i]);
        ans += hi - lo;
    }

    cout << ans << '\n';
    
    return 0;
}
