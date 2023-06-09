#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, b;
    cin >> n >> m >> b;

    vector<vector<int>> field(n, vector<int>(m));
    int min_val = INT_MAX, max_val = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> field[i][j];
            min_val = min(min_val, field[i][j]);
            max_val = max(max_val, field[i][j]);
        }
    }

    pair<int, int> answer = {INT_MAX, 0};

    for(int height = min_val; height <= max_val; height++) {
        int time = 0, blocks = b;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(field[i][j] < height) {
                    time += height - field[i][j];
                    blocks -= height - field[i][j];
                } else if(field[i][j] > height) {
                    time += 2 * (field[i][j] - height);
                    blocks += field[i][j] - height;
                }
            }
        }

        if(blocks >= 0) {
            if(answer.first > time) {
                answer = {time, height};
            } else if(answer.first == time) {
                answer = max(answer, make_pair(time, height));
            }
        }
    }

    cout << answer.first << " " << answer.second << "\n";

    return 0;
}
