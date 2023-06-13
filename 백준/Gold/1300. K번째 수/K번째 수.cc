#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N,k;
    cin >> N >> k;

    long long left = 1, right = k;
    long long answer;

    while(left <= right) {
        long long mid = (left + right) / 2;
        long long count = 0;
        for(int i = 1; i <= N; i++) {
            count += min(mid / i, N);
        }

        if (count < k) {
            left = mid + 1;
        } else {
            answer = mid;
            right = mid - 1;
        }
    }

    cout << answer;
    return 0;
}