import java.util.*;

class Solution {
    
    // 순서롤 무조건 (하,좌,우,상) 해야함
    int[] dx = {1,0,0,-1};
    int[] dy = {0,-1,1,0};
    // 각 인덱스에 맞는 문자 매핑
    String[] dir = {"d","l","r","u"};
    
    // 도착지 전역변수화
    int endX;
    int endY;
    
    // 맵의 크기
    int n,m;
    
    // 3차원으로 방문 배열을 만들어줘야함
    boolean[][][] visited = new boolean[51][51][2501];
    
    // 정답이 구해졌으면 더이상 DFS를 못하도록 하기 위한 플래그
    boolean finish = false;
    
    // 일단 숫자로 받은 다음 문자로 전환할 것임
    List<Integer> result;
    
    public String solution(int n, int m, int x, int y, int r, int c, int k) {
        
        String answer = "";
        this.n = n;
        this.m = m;
        endX = r;
        endY = c;
        dfs(x,y,k,new ArrayList<>());
        StringBuilder sb = new StringBuilder();
        if(result == null) answer = "impossible";
        else {
            for(int i : result){
                sb.append(dir[i]);
            }
            answer = sb.toString();
        }
        return answer;
    }
    
    void dfs(int x, int y, int k, List<Integer> cnt){
        if(finish) return; // 정답이 구해졌으면 더이상 안함
        // k = 0 일때 해당 자리가 도착 지점이면 성공한 것
        if(k <= 0){
            if(x == endX && y == endY) {
                result = cnt;
                finish = true;
            }
            return;
        }
       
       // 인덱스를 0 ~ 3으로 호출함으로써 우선순위대로 호출
       for(int i = 0; i < 4; i++){
           int nx = x + dx[i];
           int ny = y + dy[i];
           // k-1은 이동 이후의 남은 횟수를 뜻함
           if(nx > n || ny > m || nx < 1 || ny < 1 || visited[nx][ny][k-1]) continue;
           // 방문 체크
           visited[nx][ny][k-1] = true;
           List<Integer> list = new ArrayList<Integer>(cnt);
           list.add(i);
           dfs(nx,ny,k-1,list);
           if(finish) return;
       }
    }
}