import java.util.*;
class Solution {
    public int solution(int cacheSize, String[] cities) {
        int answer = 0;
        Queue <String> cache = new LinkedList<>();
        for(String s : cities) {
            s = s.toLowerCase();
            if(cache.contains(s)) {
                answer++;
                cache.remove(s);
                cache.offer(s);
            }
            else {
                answer += 5;
                if(cache.size() == cacheSize)
                    cache.poll();
                if(cache.size() < cacheSize)
                    cache.offer(s);
            }
        }
        return answer;
    }
}
