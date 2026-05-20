import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
    public List<Integer> solution(String msg) {
        List<Integer> answer = new ArrayList<>();
        Map<String, Integer> map = new HashMap<>();

        // 사전에 등록할 인덱스 초기화
        int idx = init(map);

        for (int i = 0; i < msg.length(); i++) {
            String word = "";

            // 사전에 등록된 가장 긴 문자열 찾기
            while (i < msg.length() && map.containsKey(word + msg.charAt(i))) {
                word += msg.charAt(i);
                i++;
            }

            // 찾은 문자열의 인덱스 answer 리스트에 추가
            answer.add(map.get(word));

            // 남은 문자가 있는 경우
            if (i < msg.length()) {
                // 다음 문자를 더한 후 사전에 등록 하기
                map.put(word + msg.charAt(i), idx);
                idx++; // 인덱스 증가
                i--; // 증가된 i 감소 시킨 후 반복문 진행
            }
        }

        return answer;
    }

    private int init(Map<String, Integer> map) {
        int idx = 1;

        for (char ch = 'A'; ch <= 'Z'; ch++) {
            map.put(String.valueOf(ch), idx++);
        }

        return idx;
    }
}
