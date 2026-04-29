#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <map>
#include <set>
using namespace std;
struct Node{
    int n;
    long long cost;
    bool operator<(Node o) const{
        return cost > o.cost;
    }
};
int N, M;
vector<Node> graph[50001];
vector<int> path[50001];
long long answer1[50001];
long long answer2[50001];
long long minCost;
unordered_map<int, int> roadNum[50001];
int result[200001];
unordered_set<int> pathCnt[50001];
int visited[50001];
void dijkstra1()
{
    for(int i = 1; i <= N; ++i)
    {
        answer1[i] = 999999987654321;
    }
    priority_queue<Node> pq;
    pq.push({1, 0});
    answer1[1] = 0;
    while(!pq.empty())
    {
        Node now = pq.top();
        pq.pop();
        if(answer1[now.n] < now.cost) continue;
        for(int i = 0; i < graph[now.n].size(); ++i)
        {
            Node nxt = graph[now.n][i];
            long long nextCost = nxt.cost + answer1[now.n];
            if(nextCost > answer1[nxt.n]) continue;
            else if(nextCost == answer1[nxt.n]){
                path[nxt.n].push_back(now.n);
            }
            else{
                path[nxt.n].clear();
                path[nxt.n].push_back(now.n);
                pq.push({nxt.n, nextCost});
                answer1[nxt.n] = nextCost;
            }
        }
    }
    minCost = answer1[N];
}
void dijkstra2()
{
    for(int i = 1; i <= N; ++i)
    {
        answer2[i] = 999999987654321;
    }
    priority_queue<Node> pq;
    pq.push({N, 0});
    answer2[N] = 0;
    while(!pq.empty())
    {
        Node now = pq.top();
        pq.pop();
        if(answer2[now.n] < now.cost) continue;
        for(int i = 0; i < graph[now.n].size(); ++i)
        {
            Node nxt = graph[now.n][i];
            long long nextCost = nxt.cost + answer2[now.n];
            if(nextCost >= answer2[nxt.n]) continue;
            answer2[nxt.n] = nextCost;
            pq.push({nxt.n, nextCost});
        }
    }
}
void printSummary()
{
    cout << minCost << "\n";
    for(int i = N; i != 1; i = path[i][0])
    {
        for(int j : path[i])
        {
            cout << j << " ";
        }
        cout << "\n";
    }
}
vector<int> solution(int n, vector<vector<int>> roads) {
    N = n;
    M = roads.size();
    for(int i = 1; i <= M; ++i)
    {
        int a = roads[i - 1][0];
        int b = roads[i - 1][1];
        long long l = roads[i - 1][2];
        long long t = roads[i - 1][3];
        graph[a].push_back({b, l + t});
        graph[b].push_back({a, l + t});
        roadNum[a][b] = i;
        roadNum[b][a] = i;
    }
    dijkstra1();
    dijkstra2();
    //printSummary();
    
    for(int i = 1; i <= M; ++i)
    {
        int a = roads[i - 1][0];
        int b = roads[i - 1][1];
        long long l = roads[i - 1][2];
        long long t = roads[i - 1][3];
        if(t == 0) continue;
        if((answer1[a] + answer2[b] + l < minCost) || (answer1[b] + answer2[a] + l < minCost)){
            result[roadNum[a][b]] = 1;
        }
    }
    
    int prev = N;
    queue<int> q;
    q.push(N);
    visited[N] = 1;
    while(!q.empty())
    {
        int qSize = q.size();
        for(int i = 0; i < qSize; ++i)
        {
            int now = q.front();
            q.pop();
            for(int k = 0; k < path[now].size(); ++k)
            {
                int nxt = path[now][k];
                if(path[now].size() == 1 && qSize == 1)
                    pathCnt[nxt].insert(now);
                if(visited[nxt]) continue;
                visited[nxt] = 1;
                q.push(nxt);
            }
        }
    }
    
    for(int i = 1; i <= N; ++i) {
        for(auto j : pathCnt[i]){
            result[roadNum[i][j]] = 1;
        }
    }
    vector<int> answer;
    for(int i = 1; i <= M; ++i) 
    {
        if(result[i]) answer.push_back(i);
    }
    if(answer.size() == 0) answer.push_back(-1);
    return answer;
}