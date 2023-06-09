#include<bits/stdc++.h>
using namespace std;
#define mod 1000000000

int dp[101][10][1 << 10]; // dp[length][last number][used numbers]
int N;

int solve(int length, int last, int used) {
    if(length == N) {
        if(used == (1<<10) - 1) return 1;
        else return 0;
    }

    if(dp[length][last][used] != -1) return dp[length][last][used];

    dp[length][last][used] = 0;

    if(last != 0) dp[length][last][used] += solve(length + 1, last - 1, used | (1 << (last - 1)));
    if(last != 9) dp[length][last][used] += solve(length + 1, last + 1, used | (1 << (last + 1)));

    dp[length][last][used] %= mod;

    return dp[length][last][used];
}

int main() {
    cin >> N;

    memset(dp, -1, sizeof(dp));
    int res = 0;

    for(int i = 1; i <= 9; i++) {
        res += solve(1, i, 1 << i);
        res %= mod;
    }

    cout << res;
    return 0;
}
