#include<bits/stdc++.h>
using namespace std;

const int MAX = 16;
const int INF = 987654321;
int N;
int W[MAX][MAX];
int cache[MAX][1 << MAX];

int TSP(int current, int visited) {
    if(visited == (1<<N) - 1) {
        if(W[current][0] != 0) return W[current][0];
        return INF;
    }

    int &ret = cache[current][visited];
    if(ret != -1) return ret;

    ret = INF;
    for(int next = 0; next < N; ++next) {
        if(visited & (1<<next) || W[current][next] == 0) continue;
        ret = min(ret, TSP(next, visited | (1<<next)) + W[current][next]);
    }

    return ret;
}

int main() {
    cin >> N;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            cin >> W[i][j];

    memset(cache, -1, sizeof(cache));
    cout << TSP(0, 1) << '\n';
    
    return 0;
}
