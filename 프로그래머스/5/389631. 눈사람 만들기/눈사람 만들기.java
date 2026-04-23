import java.util.*;

class Solution {
    
    int dx[] = {1,0,-1,0};
    int dy[] = {0,1,0,-1};
    
    public long solution(String[] grid) {
        
        int snowman[][] = new int[2][2]; // 눈덩이 시작 위치. snowball로 할껄.
        int n = grid.length;
        int m = grid[0].length();
        
        int snowmanIdx = 0;
        for(int i = 0; i < n; i++){ // 눈덩이 위치 찾기.
            for(int j = 0; j < m; j++){
                if(grid[i].charAt(j) == 'o'){
                    snowman[snowmanIdx][0] = j;
                    snowman[snowmanIdx][1] = i;
                    snowmanIdx++;
                }
            }
        }
        
        boolean been[][][] = new boolean[2][n][m];
        // 한쪽 눈공을 움직이지 않았을 때,
        long sharedBlocks = 0; // 공유블럭 :두 눈덩이 모두 접근할 수 있는 눈 블럭
        long aOnlyBlocks = 0; // A블럭 : 첫 번째 눈덩이만 접근할 수 있는 눈 블럭
        long bOnlyBlocks = 0; // B블럭 : 두 번째 눈덩이만 접근할 수 있는 눈 블럭
        
        int threeWays[][] = new int[2][3]; // 눈덩이로부터 가장 가까운 갈림길(삼거리) 위치 및 거리
        threeWays[0][2] = -1;
        threeWays[1][2] = -1;
        
        long snowballDistance = n * m + 1; //눈덩이 스타트 지점 간 거리
        boolean isCase2 = false;
        
        for(int s = 0; s < 2; s++){ // 각 눈덩이 스타트 지점부터 bfs. 
            Queue<int[]> queue = new LinkedList<>();
            queue.add(new int[]{snowman[s][0], snowman[s][1], 0});
            
            been[s][snowman[s][1]][snowman[s][0]] = true;
            
            while(!queue.isEmpty()){
                int p[] = queue.poll();
                int x = p[0]; // 현재 탐색 위치
                int y = p[1];
                int dis = p[2];
                
                int nx, ny; // 다음 탐색 위치
                int choices = 0; // 몇 개의 다른 칸과 이어져 있는지
                for(int i = 0; i < 4; i++){
                    nx = x + dx[i];
                    ny = y + dy[i];

                    if(nx < 0 || nx >= m || ny < 0 || ny >= n || grid[ny].charAt(nx) == '#'){
                        continue;
                    }

                    choices++;

                    if(been[s][ny][nx]){
                        continue;
                    }
                    
                    if(grid[ny].charAt(nx) == 'o'){
                        snowballDistance = Math.min(snowballDistance, dis + 1);
                        continue;
                    }
                    
                    been[s][ny][nx] = true;

                    queue.add(new int[]{nx, ny, dis+1});
                }

                if(choices >= 3){// 삼거리 이상, 즉 갈림길이면

                    if(s == 1 && been[0][y][x] && grid[y].charAt(x) == '.'){
                        isCase2 = true;
                    }

                    if(threeWays[s][2] == -1){
                        threeWays[s][0] = x;
                        threeWays[s][1] = y;
                        threeWays[s][2] = dis;    
                    }

                }
                
            }
            
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                
                if(grid[i].charAt(j) == 'o'){
                    continue;
                }
                else if(been[0][i][j] && been[1][i][j]){
                    sharedBlocks ++;
                }
                else if(been[0][i][j]){
                    aOnlyBlocks++;
                }
                else if(been[1][i][j]){
                    bOnlyBlocks++;
                }
            }
        }
        
        
        //외길일 경우(갈림길 없을 경우) - CASE 1.
        if(threeWays[0][2] == -1 && threeWays[1][2] == -1){

            return calculateAnswer(1, snowballDistance, sharedBlocks, Math.min(aOnlyBlocks, bOnlyBlocks),
                                  Math.max(aOnlyBlocks, bOnlyBlocks), 250001);
        }
        
        //눈덩이 사이에 갈림길이 하나 이상 있는 경우 - CASE 2, 
        // 또는 A블럭, B블럭 양쪽 모두에 갈림길이 있는 경우
        if((threeWays[0][2] != -1 && threeWays[1][2] != -1 ) || isCase2){
            return calculateAnswer(2, snowballDistance, sharedBlocks, aOnlyBlocks, bOnlyBlocks, 0);   
        }
        
      
        //눈덩이 사이는 외길이고, 다른 곳에 세갈림길이 있는 경우 - CASE 3.  
        
        if(threeWays[0][2] == -1){
            
            return calculateAnswer(3, snowballDistance, sharedBlocks, aOnlyBlocks, bOnlyBlocks
                                   , threeWays[1][2]);
        } else {
            
            return calculateAnswer(3, snowballDistance, sharedBlocks, bOnlyBlocks, aOnlyBlocks
                                   , threeWays[0][2]);
        } 
        
    }
    
    //케이스 1에선 고유영역이 더 큰 쪽이 B. 케이스 3에선 갈림길까지 거리가 더 가까운쪽이 B
    long calculateAnswer(int caseType, long snowballDistance, long sharedBlocks, long aOnlyBlocks,
                         long bOnlyBlocks, long disToThreeWay){
        long ret = 0;
        
        long sum = sharedBlocks + aOnlyBlocks + bOnlyBlocks;
       
        for(long i = snowballDistance-1; i <= sum; i++){
            
            if(caseType == 3 && i > sharedBlocks + aOnlyBlocks + disToThreeWay + 1){
                sharedBlocks ++;
            }
            
            if(caseType == 2){
                ret += i/2 + 1;
            } else{
                ret += Math.min(i/2 + 1, aOnlyBlocks + sharedBlocks + 1) ;
            }
            
            if(caseType == 1 && i > bOnlyBlocks + sharedBlocks){
                ret -= i - bOnlyBlocks - sharedBlocks;
            }
        }
        
        return ret;
    }
}