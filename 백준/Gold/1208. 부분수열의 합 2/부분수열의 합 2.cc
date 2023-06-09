#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr, v1, v2;
int N, S;

void dfs(int start, int end, int sum, vector<int>& v) {
    if (start > end) {
        v.push_back(sum);
        return;
    }
    dfs(start + 1, end, sum, v);
    dfs(start + 1, end, sum + arr[start], v);
}

int main() {
    cin >> N >> S;
    arr.resize(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    dfs(0, N / 2 - 1, 0, v1);
    dfs(N / 2, N - 1, 0, v2);
    sort(v2.begin(), v2.end());

    long long ans = 0;
    for (int i = 0; i < v1.size(); i++) {
        int target = S - v1[i];
        ans += upper_bound(v2.begin(), v2.end(), target) - lower_bound(v2.begin(), v2.end(), target);
    }

    if (S == 0) ans--; 
    cout << ans << '\n';

    return 0;
}
