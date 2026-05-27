import java.util.Arrays;

class Solution {
    public int solution(int n, int k) {
        // 숫자 n을 k진법으로 표현한 문자열
        String kNumber = Integer.toString(n, k);
        // 문자열을 0을 기준으로 분리하여 배열에 저장
        String[] arr = kNumber.split("0");
        // 소수의 개수를 저장하는 변수
        int answer = 0;

        // 분리된 문자열 배열을 순회
        for (String s : arr) {
            if (s.equals("")) { // 빈 문자열 무시
                continue;
            }

            // 문자열을 long 타입 숫자로 변환합니다.
            long num = Long.parseLong(s);

            // 변환된 숫자가 소수인지 확인
            if (isPrime(num)) {
                answer++; // 소수인 경우 answer 증가
            }
        }

        return answer;
    }
    
    // 소수인지 여부를 판단하는 메서드
    private static boolean isPrime(long num) {
    	// 1보다 작거나 같은 경우 false
        if (num <= 1) {
            return false;
        }
        
        // i를 2부터 num의 제곱근 까지 반복
        for (int i = 2; i <= (int) Math.sqrt(num); i++) {
            // num % i가 0이면 소수가 아니므로 false 반환
            if (num % i == 0) {
                return false;
            }
        }
        
        return true;
    }
}
