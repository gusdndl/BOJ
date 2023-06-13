#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int cost[16][16];
int dp[1 << 16][16][10];

int solve(int visit, int cur, int price) {
    if (dp[visit][cur][price] != -1) return dp[visit][cur][price];
    dp[visit][cur][price] = 1;
    for (int i = 0; i < n; i++) {
        if ((visit & (1 << i)) == 0 && cost[cur][i] >= price) {
            dp[visit][cur][price] = max(dp[visit][cur][price], solve(visit | (1 << i), i, cost[cur][i]) + 1);
        }
    }
    return dp[visit][cur][price];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            cost[i][j] = c - '0';
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(1, 0, 0);
    return 0;
}
