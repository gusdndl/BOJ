import java.util.*;

class Solution {
    
    class Triangle {
        
        public int x;
        public int y;
        public int state; // 0 : |\ |/, 1 : \| /|
        
        public Triangle(int x, int y, int state) {
            this.x = x;
            this.y = y;
            this.state = state;
        }
        
    }
    
    private int N, M;
    private int[][][] group;
    private int[] dx = {-1,1,0,0};
    private int[] dy = {0,0,-1,1};
    private int[][] dir = {{1,2},{0,2},{0,3},{1,3}}; // 현재 삼각형이 |\ |/ \| /| 일때 이동 가능 방향
    private int[][] updownState = {{1,0},{0,1},{0,1},{1,0}}; // 현재 삼각형이 |\ |/ \| /| 일때 위 또는 아래 삼각형의 state
    
    public int solution(int[][] grid) {
        init(grid);
        
        int answer = 0;
        int groupNum = 1;
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                for (int k=0; k<2; k++) {
                    if (group[i][j][k] == 0) {
                        answer = Math.max(answer, bfs(i, j, k, groupNum, grid));
                        groupNum++;
                    }
                }
            }
        }
        
        return answer;
    }
    
    public void init(int[][] grid) {
        N = grid.length;
        M = grid[0].length;
        group = new int[N][M][2];
    }
    
    public int bfs(int x, int y, int state, int groupNum, int[][] grid) {
        Queue<Triangle> q = new LinkedList<>();
        q.offer(new Triangle(x, y, state));
        group[x][y][state] = groupNum;
        
        int size = 0;
        while (!q.isEmpty()) {
            Triangle cur = q.peek();
            q.poll();
            size++;
            
            int shape; // 현재 삼각형 모양 0 : |\, 1 : |/, 2 : \|, 3 : /|
            if (grid[cur.x][cur.y] == -1) shape = cur.state == 0 ? 0 : 2;  
            else shape = cur.state == 0 ? 1 : 3;  
            
            for (int i=0; i<2; i++) {
                int nd = dir[shape][i]; // 다음 방향
                int nx = cur.x + dx[nd];
                int ny = cur.y + dy[nd];

                if (!isValid(nx, ny)) continue; // 격자 밖일 경우
                if (group[nx][ny][0] == groupNum || group[nx][ny][1] == groupNum) continue; // 이미 방문한 경우
                
                int nState; // 다음 삼각형의 state
                // 위아래일 경우에는 grid[nx][ny]에 따라 state 결정
                if (nd == 0 || nd == 1) nState = updownState[shape][grid[nx][ny] == -1 ? 0 : 1]; 
                else nState = nd == 2 ? 1 : 0; // 왼쪽일 경우 1, 오른쪽일 경우 0

                group[nx][ny][nState] = groupNum; // 현재 그룹에 포함시키기
                q.offer(new Triangle(nx, ny, nState));
            }
        }
        
        return size;
    }
    
    // 좌표가 격자 내부인지 판별하는 메소드
    public boolean isValid(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < M;
    }
    
}