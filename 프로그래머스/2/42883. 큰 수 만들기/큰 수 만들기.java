class Solution {
    public String solution(String number, int k) {
        StringBuilder answer = new StringBuilder();
        char[] numArray = number.toCharArray();
        int lenAnswer = number.length() - k; // 결과
        int startIndex = 0;
 
        // 문자열의 길이가 lenAnswer이 될 때 까지 while
        while (startIndex < number.length() && answer.length() != lenAnswer){
            int endNum = k + answer.length() ; // 최댓값 찾는 숫자 갯수
            int maxNum = 0; // 현재 최댓값
            // startIndex부터 endNum 자릿수 사이의 숫자들로 돌려서 최댓값 찾기
            for (int i = startIndex; i <= endNum; i++){
                // charAt : 리스트에서 해당 인덱스의 요소, charAt(i) - 0 : 뽑은 요소 정수로 변환하기
                // i번째 숫자와 max를 비교해서 가장 큰 걸 max에 넣기
                if (maxNum < number.charAt(i) - '0') { 
                    maxNum = number.charAt(i) - '0';
                    // 가장 큰 값 찾았으면 그 수 뒤에거부터 다시 돌기
                    startIndex = i + 1;
                }
            }
            answer.append(Integer.toString(maxNum));
        }
        return answer.toString();
    }
}