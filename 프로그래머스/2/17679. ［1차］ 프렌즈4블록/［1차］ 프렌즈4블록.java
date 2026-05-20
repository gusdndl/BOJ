import java.util.*;

class Solution {
    private static char[][] Board;
    private static boolean[][] EraseMap; // 선택되어 지워져야할 블록 체크
    private static int M, N;
    private static int Cnt = 0;
    public int solution(int m, int n, String[] board) {
        M = m;
        N = n;
        Board = new char[M][N];
        
        // Board 채우기
        for(int i = 0; i < M; i++) {
            char[] row = board[i].toCharArray();
            for (int j = 0; j < N; j++) {
                Board[i][j] = row[j];
            }
        }
        
        // 2x2 안찾아질때까지 반복
        
        
        while(true) {
            EraseMap = new boolean[M][N];
            boolean found = false; 
            for (int i = 0; i < M-1; i++) {
                for (int j = 0; j < N-1; j++) {
                    if(isSameTwoTwo(i, j)) { // 2x2 발견
                        deleteTwoTwo(i, j);
                        found = true;
                    }
                }
            }
            if(found == false) // 2x2발견 못하면 종료
                break;
            else { // 2x2 발견 다 하면 이제 ' ' 로 표시된 부분 위에서 아래로 빈칸 다 매꿔주기
                fillBlanks();
                found = false; // 내린 다음 또 발견을 위해 false으로 초기화
            }
        }
        
        // System.out.println(Arrays.deepToString(Board));
        return Cnt;
    }
    
    private static boolean isSameTwoTwo(int r, int c) {
        char leftTop = Board[r][c];
        if (leftTop == ' ')
            return false;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (!isInside(r, c) || Board[r + i][c + j] != leftTop) {
                    return false;
                }
            }
        }
        return true;
    }
    
    private static void deleteTwoTwo(int r, int c) { // Erase 맵에 지워야할 블록 체크
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if(EraseMap[r + i][c + j] == false) {
                    EraseMap[r + i][c + j] = true;
                    Cnt++;
                }
            }
        }
    }
    
    private static void fillBlanks() {
        // 먼저 EraseMap 참고해서 빈칸으로 다 바꿔주기
        // System.out.println("before");
        // printBoard(Board);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if(EraseMap[i][j] == true) {
                    Board[i][j] = ' ';
                    EraseMap[i][j] = false;
                }
            }
        }
        // System.out.println("middle");
        // printBoard(Board);
        // 왼쪽 열부터 오른쪽으로 훑기
        for (int c = 0; c < N; c++) {
            // 아래 행부터 위로 훑기 (빈칸 찾기)
            int lowestBlankRow = -1; // 빈칸중 맨 아래
            for (int r = M - 1; r >= 0; r--) {
                if (lowestBlankRow == -1 && Board[r][c] == ' ') { // 제일 아래 빈칸 찾았으면
                    lowestBlankRow = r;
                } else if (lowestBlankRow != -1 && Board[r][c] != ' ') { // 아래 빈칸이 있는데 채워져있는 블록을 찾음
                    char block = Board[r][c];
                    Board[lowestBlankRow][c] = block; // 아래의 빈칸 위에서 내려서 채우기
                    Board[r][c] = ' '; // 아래로 내렸으니 빈칸으로 만들기
                    r = lowestBlankRow;
                    lowestBlankRow = -1; // 다시 탐색을 위해 초기화
                }
            }
        }
        
        // System.out.println("after");
        // printBoard(Board);
    }
    
    private static boolean isInside(int r, int c) {
        return (0 <= r && r < M && 0 <= c && c < N);
    }
    
    private static void printBoard(char[][] board) {
        for(char[] row : board) {
            System.out.println(Arrays.toString(row));
        }
    }
}