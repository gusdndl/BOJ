#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, W, dp[1010][1010], track[1010][1010];
pair<int, int> event[1010];

int dist(pair<int, int> a, pair<int, int> b) {
    return abs(b.first - a.first) + abs(b.second - a.second);
}

int solve(int a, int b) {
    if (a == W || b == W) return 0;

    int &ret = dp[a][b];
    if (ret != -1) return ret;

    int next = max(a, b) + 1;
    int car1 = solve(next, b) + dist(event[next], a ? event[a] : make_pair(1, 1));
    int car2 = solve(a, next) + dist(event[next], b ? event[b] : make_pair(N, N));

    return ret = min(car1, car2);
}

void trace(int a, int b) {
    if (a == W || b == W) return;

    int next = max(a, b) + 1;
    int car1 = solve(next, b) + dist(event[next], a ? event[a] : make_pair(1, 1));
    int car2 = solve(a, next) + dist(event[next], b ? event[b] : make_pair(N, N));

    if (car1 > car2) {
        cout << 2 << '\n';
        trace(a, next);
    }
    else {
        cout << 1 << '\n';
        trace(next, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> W;
    for (int i = 1; i <= W; i++)
        cin >> event[i].first >> event[i].second;

    memset(dp, -1, sizeof(dp));

    cout << solve(0, 0) << '\n';
    trace(0, 0);
    
    return 0;
}
