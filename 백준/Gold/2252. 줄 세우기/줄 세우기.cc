#include<bits/stdc++.h>
using namespace std;

int N, M; // N - number of students, M - number of comparisons
vector<int> graph[32001]; // adjacency list to represent the graph
int inDegree[32001]; // array to store in-degrees of all nodes
queue<int> q; // queue for topological sort

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        inDegree[b]++;
    }

    // Enqueue all nodes with in-degree of 0
    for(int i = 1; i <= N; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Topological Sort
    while(!q.empty()) {
        int curr = q.front();
        q.pop();

        cout << curr << ' ';

        for(int i = 0; i < graph[curr].size(); i++) {
            int next = graph[curr][i];
            inDegree[next]--;

            if(inDegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return 0;
}
