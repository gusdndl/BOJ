import java.lang.Math;

class Solution {
    public int solution(String dirs) {
        int answer = 0;
        boolean [][] visitVertical = new boolean [11][10];
        boolean [][] visitHorizontal = new boolean [10][11];
        
        int x = 5;
        int y = 5;
        
        for(int i=0;i<dirs.length();i++){
            char c = dirs.charAt(i);
            int X=x;
            int Y=y;
            
            boolean horizontal = false;
            boolean vertical = false;
            
            if(c=='U'){
                Y++;
                vertical = true;
            }else if(c=='D'){
                Y--;
                vertical = true;
            }else if(c=='L'){
                X--;
                horizontal = true;
            }else if(c=='R'){
                X++;
                horizontal = true;
            }
            
            if(X>=0&&X<11&&Y>=0&&Y<11){
                
                if(horizontal){
                    if(!visitHorizontal[Math.min(X,x)][Y]){
                        visitHorizontal[Math.min(X,x)][Y] = true;
                        answer++;
                    }
                    
                }else if(vertical){
                    if(!visitVertical[X][Math.min(Y,y)]){
                        visitVertical[X][Math.min(Y,y)] = true;
                        answer++;
                    }
                    
                }
                
                                
                x = X;
                y = Y;
            }
        }
        return answer;
    }
}