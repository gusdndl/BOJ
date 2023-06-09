#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> dp(n, 0);
    vector<int> idx(n, 0);
    vector<pair<int, int>> trace;
    for (int i = 0; i < n; i++) cin >> arr[i];

    int length = 1;
    trace.push_back({1, arr[0]});
    dp[0] = arr[0];

    for (int i = 1; i < n; i++) {
        if (dp[length - 1] < arr[i]) {
            dp[length++] = arr[i];
            trace.push_back({length, arr[i]});
        } else {
            int pos = lower_bound(dp.begin(), dp.begin() + length, arr[i]) - dp.begin();
            dp[pos] = arr[i];
            trace.push_back({pos + 1, arr[i]});
        }
    }

    cout << length << '\n';

    vector<int> ans;
    int len = length;
    for (int i = n - 1; i >= 0; i--) {
        if (trace[i].first == len) {
            ans.push_back(trace[i].second);
            len--;
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << x << " ";
    
    return 0;
}
