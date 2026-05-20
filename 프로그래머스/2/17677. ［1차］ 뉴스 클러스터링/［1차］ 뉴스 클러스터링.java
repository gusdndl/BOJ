import java.util.ArrayList;
import java.util.List;

class Solution {
    public int solution(String str1, String str2) {
        // 두 문자열을 소문자로 변환한 뒤, 2글자씩 끊어서 리스트에 저장
        List<String> list1 = stringSplit(str1);
        List<String> list2 = stringSplit(str2);

        // 두 리스트가 모두 비어있을 경우, 유사도를 65536으로 가정
        if (list1.isEmpty() && list2.isEmpty()) {
            return 65536;
        }

        List<String> union = new ArrayList<>();	// 합집합을 저장할 리스트
        List<String> inter = new ArrayList<>();	// 교집합을 저장할 리스트

        // 첫 번째 리스트를 순회하면서
        for (String s : list1) {
            // 두 번째 리스트에서 현재 문자열과 같은 것을 찾아 교집합에 추가
            if (list2.remove(s)) {
                inter.add(s);
            }

            // 합집합에 현재 문자열을 추가
            union.add(s);
        }

        // 교집합과 두 번째 리스트의 남은 원소를 합집합에 추가
        union.addAll(list2);

        // 자카드 유사도를 계산 (교집합 크기 / 합집합 크기)
        double jacquard = (double) inter.size() / (double) union.size();

        // 유사도에 65536 곱하고 소수점을 버린 값 반환
        return (int) (jacquard * 65536);
    }

    // 문자열을 2글자씩 끊어서 리스트에 저장하는 함수
    private List<String> stringSplit(String str) {
        List<String> list = new ArrayList<>();
        str = str.toLowerCase(); // 문자열을 소문자로 변환

        for (int i = 0; i < str.length() - 1; i++) {
            String s = str.substring(i, i + 2).replaceAll("[^a-z]", "");

            // 길이가 2보다 작으면 건너뛰고, 그렇지 않으면 리스트에 추가
            if (s.length() < 2) {
                continue;
            }

            list.add(s);
        }

        return list;
    }
}
