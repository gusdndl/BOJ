#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T; // number of test cases
    cin >> T;

    while (T--) {
        int N, K; // number of vertices and edges
        cin >> N >> K;

        vector<int> time(N + 1, 0);
        vector<int> indegree(N + 1, 0);
        vector<int> result(N + 1, 0);
        vector<vector<int>> adj(N + 1);
        queue<int> q;

        for (int i = 1; i <= N; i++) {
            cin >> time[i];
        }

        for (int i = 0; i < K; i++) {
            int X, Y;
            cin >> X >> Y;
            adj[X].push_back(Y);
            indegree[Y]++;
        }

        for (int i = 1; i <= N; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                result[i] = time[i];
            }
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (int next : adj[curr]) {
                result[next] = max(result[next], result[curr] + time[next]);
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        int W;
        cin >> W;
        cout << result[W] << '\n';
    }
    return 0;
}
