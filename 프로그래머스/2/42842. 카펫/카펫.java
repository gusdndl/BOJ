class Solution {
    public int[] solution(int brown, int yellow) {
        int[] answer = new int[2]; // 결과를 저장할 배열 선언
        int sum = brown + yellow; // 격자의 총 개수

        // 노란색 격자의 개수가 1 이상, 행은 3부터 시작하는 범위에서 반복
        for (int i = 3; i < sum / 2; i++) {
            int row = i;
            int col = sum / row;
            
            // (행-2) * (열-2) 가 노란색 격자의 개수와 일치하는 경우
            if ((row - 2) * (col - 2) == yellow) {
                answer[0] = col;
                answer[1] = row;
                break;
            } 
        }
    
        return answer;
    }
}
