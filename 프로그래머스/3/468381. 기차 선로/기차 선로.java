import java.io.*;
import java.util.*;

class Solution {
    final int[] dy = new int[]{0,0,1,-1};// 동 서 남 북
    final int[] dx = new int[]{1,-1,0,0};
    
    final int RIGHT = 0, LEFT = 1, DOWN = 2, UP = 3;
    final int EMPTY = 0, BLOCKED = -1;
    
    final int[][] PLACEABLE_RAILS = {
        {1, 3, 4, 7},  // RIGHT
        {1, 3, 5, 6},  // LEFT
        {2, 3, 4, 5},  // DOWN
        {2, 3, 6, 7},  // UP
    };
    
    int answer = 0,n,m;
    int[][] map, visited;
    
    public int solution(int[][] grid) {
        init(grid);
        
        backtracking(0,1,RIGHT);
        
        return answer;
    }
    
    private void backtracking(int y, int x, int direction){
        if(isOutOfRange(y,x) || isBlocked(y,x)) return;
        
        if(isGoal(y,x)){
            if(isVisitedAllRail() && isValidDirection(y,x,direction)){
                answer++;
            }
            return;
        }
        
        visited[y][x]++;
        
        if(isEmpty(y,x)){
            for(int rail : PLACEABLE_RAILS[direction]){
                map[y][x] = rail;
                int[] next = getNextPosition(y,x,direction);
                backtracking(next[0], next[1], next[2]);
            }
            map[y][x] = EMPTY;
        }else{     
            if(isValidDirection(y, x, direction)){
                int[] next = getNextPosition(y,x,direction);
                backtracking(next[0], next[1], next[2]);
            }     
        }
        
        visited[y][x]--;
    }
    
    // 레일 모양과 올바른 이동방향인지 체크
    private boolean isValidDirection(int y, int x, int direction){
        int currentRail = map[y][x];
        
        switch(currentRail){
            case 1:
                return direction == RIGHT || direction == LEFT;
            case 2:
                return direction == UP || direction == DOWN;
            case 3:
                return true;
            case 4:
                return direction == RIGHT || direction == DOWN;
            case 5:
                return direction == LEFT || direction == DOWN;
            case 6:
                return direction == LEFT || direction == UP;
            case 7:
                return direction == RIGHT || direction == UP;
            default:
                System.out.println("예외 케이스 발생");
                return false;
        }
    }
    
    private int[] getNextPosition(int y,int x,int direction){
        int[] next = new int[3];
        
        int currentRail = map[y][x];
        
        switch(currentRail){
            case 1,2,3:
                break;
            case 4:
                direction = direction == DOWN ? LEFT : UP;
                break;
            case 5:
                direction = direction == DOWN ? RIGHT : UP;
                break;
            case 6:
                direction = direction == UP ? RIGHT : DOWN;
                break;
            case 7:
                direction = direction == UP ? LEFT : DOWN;
                break;
        }
        
        next[0] = y + dy[direction];
        next[1] = x + dx[direction];
        next[2] = direction;
        
        return next;
    }
    
    private boolean isVisitedAllRail(){
        for(int y=0; y<n; y++){
            for(int x=0; x<m; x++){
                if(map[y][x] == 3 && visited[y][x] != 2){
                    return false;
                }
                
                if(map[y][x] >= 1 && map[y][x] <= 7 && visited[y][x] < 1){
                    return false;
                }
            }
        }
        
        return true;
    }
    
    private boolean isGoal(int y, int x){
        return y == n-1 && x == m-1;
    }
    
    private boolean isBlocked(int y, int x){
        return map[y][x] == -1;
    }
    
    private boolean isEmpty(int y ,int x){
        return map[y][x] == 0;
    }
    
    private boolean isOutOfRange(int y, int x){
        return y<0 || x<0 || y>=n || x>=m;
    }
    
    private void init(int[][] grid){
        n = grid.length;
        m = grid[0].length;
        
        map = grid;
        visited = new int[n][m];
        visited[0][0] = 1;
        visited[n-1][m-1] = 1;
    }
}