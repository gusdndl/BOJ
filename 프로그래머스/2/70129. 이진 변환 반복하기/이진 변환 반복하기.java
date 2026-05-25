class Solution {
    public int[] solution(String s) {
        int[] answer = {0, 0};			//정답 배열 선언
        
        while (!s.equals("1")) {				
            int before = s.length();	//0을 제거하기 전 길이
            s = s.replaceAll("0", "");	//0 제거
            int after = s.length();		//0을 제거한 후 길이
       
            answer[1] += before - after;		//제거한 0의 개수 저장
    
            s = Integer.toBinaryString(after);	//2진 변환
            
            answer[0]++;	//2진 변환한 횟수 증가
        }
        
        return answer;
    }
}