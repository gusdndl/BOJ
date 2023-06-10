#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N+1);
    vector<int> inDegree(N+1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        graph[A].push_back(B);
        inDegree[B]++;
    }

    for(int i = 1; i <= N; i++) {
        if(inDegree[i] == 0) {
            pq.push(i);
        }
    }

    while(!pq.empty()) {
        int problem = pq.top();
        pq.pop();
        cout << problem << ' ';

        for(auto next : graph[problem]) {
            inDegree[next]--;
            if(inDegree[next] == 0) {
                pq.push(next);
            }
        }
    }

    return 0;
}
