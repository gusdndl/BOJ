def solution(n):
    a, b = 0, 1          # F(0) = a, F(1) = b
    for i in range(n):
        a, b = b, a + b  # F(n) = F(n-1) + F(n-2)
    return a % 1234567   # 1234567로 나눈 나머지 반환