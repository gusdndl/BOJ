class Solution {
    public String solution(int n, int t, int m, int p) {
        /*
        n : n진법
        t : 미리 구해야할 숫자의 개수
        m : 게임에 참가하는 인원
        p : 튜브의 순서
        */
        StringBuilder nums = new StringBuilder();
        StringBuilder answer = new StringBuilder();

        // 0부터 t * m까지 모든 숫자를 n진법으로 변환 후 nums 문자열에 추가
        for (int i = 0; nums.length() < t * m; i++) {
            nums.append(Integer.toString(i, n).toUpperCase());
        }

        // 튜브의 순서 p에 맞는 숫자를 선택하여 answer 문자열에 추가
        for (int i = p - 1; answer.length() < t; i += m) {
            answer.append(nums.charAt(i));
        }

        return answer.toString();
    }
}
