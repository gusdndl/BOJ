def solution(n):
    dp = [0, 1, 2]
    for i in range(n - len(dp) + 1):
        dp.append((dp[-1] + dp[-2]) % 1000000007)
    return dp[n]