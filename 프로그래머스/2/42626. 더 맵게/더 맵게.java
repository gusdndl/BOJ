import java.util.PriorityQueue;

class Solution {
    public int solution(int[] scoville, int K) {
        // 결과를 담을 answer
        int answer = 0;
        // 우선순위 큐 선언
        PriorityQueue<Integer> queue = new PriorityQueue<>();
        
        // scoville 배열 queue에 담기
        for (int i = 0; i < scoville.length; i++) {
            queue.add(scoville[i]);
        }
        
        // 가장 먼저 나올 스코빌 지수가 K 보다 작으면 반복
        while (queue.peek() < K) {
            // queue의 사이즈가 1이면 K를 넘을 방법이 없음
            if (queue.size() == 1) return -1;
            
            // 음식 섞기
            queue.add(queue.poll() + (queue.poll() * 2));
            answer++;
        }
        
        return answer;
    }
}
