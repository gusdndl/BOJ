import java.util.Stack;

class Solution {
    public boolean solution(String s) {
        // 여는 괄호를 저장할 스택 초기화
        Stack<Character> stack = new Stack<>();

        // 문자열의 각 문자를 순회
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // 여는 괄호를 만나면 스택에 추가
            if (c == '(') {
                stack.push(c);
            }
            // 닫는 괄호를 만나면 스택에서 여는 괄호를 제거
            else if (c == ')') {
                // 스택이 비어 있으면 짝이 맞지 않음
                if (stack.isEmpty()) {
                    return false;
                }
                stack.pop(); // 가장 최근의 여는 괄호 제거
            }
        }

        // 모든 괄호의 짝이 맞는지 확인
        return stack.isEmpty();
    }
}