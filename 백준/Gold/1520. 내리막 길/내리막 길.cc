#include <iostream>
#include <vector>
using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int m, n;
vector<vector<int>> map;
vector<vector<int>> dp;

int dfs(int y, int x) {
    if(y == m - 1 && x == n - 1) return 1;
    if(dp[y][x] != -1) return dp[y][x];

    dp[y][x] = 0;
    for(int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if(ny >= 0 && ny < m && nx >= 0 && nx < n && map[y][x] > map[ny][nx]) {
            dp[y][x] += dfs(ny, nx);
        }
    }

    return dp[y][x];
}

int main() {
    cin >> m >> n;
    map = vector<vector<int>>(m, vector<int>(n));
    dp = vector<vector<int>>(m, vector<int>(n, -1));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }

    cout << dfs(0, 0);
    return 0;
}
