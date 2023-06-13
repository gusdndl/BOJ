#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

ll eulerPhi(ll n) {
    ll result = n;
    for(ll i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    cout << eulerPhi(n) << '\n';

    return 0;
}
