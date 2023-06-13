#include <iostream>
#include <queue>
using namespace std;
 
struct Point {
    int x, y, h;
    bool operator < (const Point &p) const {
        return h > p.h;
    }
};
 
int n, m, ans, dh[] = { -1, 0, 1, 0 }, dw[] = { 0, 1, 0, -1 };
char arr[51][51];
bool visit[51][51];
priority_queue<Point> pq;
 
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            arr[i][j] -= '0';
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                pq.push({ i, j, arr[i][j] });
            else
                arr[i][j] = -arr[i][j];
        }
 
    while (!pq.empty()) {
        Point cur = pq.top(); pq.pop();
        if (visit[cur.x][cur.y]) continue;
        visit[cur.x][cur.y] = true;
        for (int i = 0; i < 4; i++) {
            int nh = cur.x + dh[i], nw = cur.y + dw[i];
            if (nh < 0 || nw < 0 || nh >= n || nw >= m || visit[nh][nw]) continue;
            if (arr[nh][nw] < 0 && -arr[nh][nw] <= cur.h) {
                pq.push({ nh, nw, cur.h });
                ans += cur.h + arr[nh][nw];
                arr[nh][nw] = cur.h;
            }
            else if(arr[nh][nw] < 0)
                pq.push({ nh, nw, -arr[nh][nw] });
            else
                pq.push({ nh, nw, arr[nh][nw] });
        }
    }
 
    cout << ans;
 
    return 0;
}
