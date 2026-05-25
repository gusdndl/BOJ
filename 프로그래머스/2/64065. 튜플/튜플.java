import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

class Solution {
    public List<Integer> solution(String s) {
        // 문자열에서 존재하는 "},{"를 "-"로 치환
        s = s.substring(2, s.length()- 2).replace("},{", "-");
        // "-"를 기준으로 배열로 분리
        String[] sArr = s.split("-");

        // 배열을 길이를 기준으로 정렬
        Arrays.sort(sArr, Comparator.comparingInt(String::length));

        List<Integer> list = new ArrayList<>();

        // 각 집합을 순회하며 정수로 변환하여 리스트에 추가
        for (String el : sArr) {
            String[] check = el.split(",");

            for (int i = 0; i < check.length; i++) {
                int num = Integer.parseInt(check[i]);

                // 중복된 값이 없을 때만 리스트에 추가
                if (!list.contains(num)) {
                    list.add(num);
                }
            }
        }

        return list;
    }
}
