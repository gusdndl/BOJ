#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
char maze[50][50];
bool visited[50][50][1<<6];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

struct State {
    int x, y, key, step;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    State start;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++) {
            cin >> maze[i][j];
            if(maze[i][j] == '0') {
                start = {i, j, 0, 0};
            }
        }
    memset(visited, false, sizeof(visited));
    
    queue<State> q;
    q.push(start);
    visited[start.x][start.y][start.key] = true;
    
    while(!q.empty()) {
        State cur = q.front();
        q.pop();
        
        if(maze[cur.x][cur.y] == '1') {
            cout << cur.step;
            return 0;
        }
        
        for(int i=0; i<4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int key = cur.key;
            
            if(nx<0 || ny<0 || nx>=N || ny>=M) continue;
            
            char next = maze[nx][ny];
            if(next == '#') continue;
            if(next >= 'a' && next <= 'f') key |= (1 << (next-'a'));
            if(next >= 'A' && next <= 'F') {
                if(!(key & (1 << (next-'A')))) continue;
            }
            if(visited[nx][ny][key]) continue;
            
            visited[nx][ny][key] = true;
            q.push({nx, ny, key, cur.step+1});
        }
    }
    
    cout << -1;
    return 0;
}
