#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> time(N + 1);
    vector<int> indegree(N + 1, 0);
    vector<int> result(N + 1, 0);
    vector<vector<int>> graph(N + 1);

    for(int i = 1; i <= N; i++) {
        cin >> time[i];
        while(true) {
            int x;
            cin >> x;
            if(x == -1) break;
            graph[x].push_back(i);
            indegree[i]++;
        }
    }

    queue<int> q;

    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) {
            q.push(i);
            result[i] = time[i];
        }
    }

    while(!q.empty()) {
        int current = q.front();
        q.pop();

        for(int i = 0; i < graph[current].size(); i++) {
            int next = graph[current][i];
            result[next] = max(result[next], result[current] + time[next]);
            if(--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    for(int i = 1; i <= N; i++)
        cout << result[i] << '\n';

    return 0;
}
