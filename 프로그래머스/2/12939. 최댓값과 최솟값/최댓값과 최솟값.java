class Solution {
    public String solution(String s) {
        // 주어진 문자열을 공백을 기준으로 나눠서 문자열 배열로 저장
        String[] sArr = s.split(" ");

        // 최대값과 최소값을 첫 번째 문자열로 초기화
        int max = Integer.parseInt(sArr[0]);
        int min = Integer.parseInt(sArr[0]);

        // 문자열 배열을 순회하며 최대값과 최소값을 계산
        for (String str : sArr) {
            int temp = Integer.parseInt(str);

            // 현재 숫자가 최소값보다 작으면 최소값을 업데이트
            if (min > temp) {
                min = temp;
            }

            // 현재 숫자가 최대값보다 크면 최대값을 업데이트
            if (max < temp) {
                max = temp;
            }
        }

        return min + " " + max;
    }
}
