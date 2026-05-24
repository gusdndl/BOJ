import java.util.Arrays;

class Solution {
    public int solution(int[] people, int limit) {
        int twoSafe = 0; // 한 번에 2명씩 구출된 횟수
        Arrays.sort(people); // 사람들의 무게를 오름차순으로 정렬

        int left = 0; // 왼쪽 인덱스
        int right = people.length - 1; // 오른쪽 인덱스

        while (left < right) {
            // left와 right의 무게 합이 limit 이하인 경우
            if (people[left] + people[right] <= limit) {
                left++; // 왼쪽 인덱스 증가
                right--; // 오른쪽 인덱스 감소
                twoSafe++; // 2명이 한 번에 구출된 횟수 증가

            // 무게 합이 limit를 초과하는 경우
            } else {
                right--; // 오른쪽 인덱스만 감소
            }
        }

        // 모든 사람의 수 - 한 번에 구출된 횟수(구명보트의 수)
        return people.length - twoSafe;
    }
}