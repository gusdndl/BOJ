import java.util.*;

class Solution {
    static HashMap<String, Integer> map = new HashMap<>();

    public int solution(String[][] clothes) {
        int answer = 1;

        for(int i = 0; i < clothes.length; i++) {
            map.put(clothes[i][1], map.getOrDefault(clothes[i][1], 0) + 1);
        }

        for(String str : map.keySet()) {
            answer *= (map.get(str) + 1);
        }
        answer -= 1;
        return answer;
    }
}