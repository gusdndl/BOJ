function solution(n) {
  const dp = [1, 1, 3, 10];
  const memo = [
    [2, 6, 12, 32], // 2 4 2 2 4 2 2 4 2 2 4  0
    [2, 4, 16, 36], // 2 2 4 2 2 4 2  1
    [4, 6, 12, 52], // 4 2 2 4 2 2 4  2
  ];

  for (let i = 4; i <= n; i++) {
    const now = (i - 1) % 3;
    const t1 = (now + 1) % 3;
    const t2 = (now + 2) % 3;

    dp[i] = (dp[i - 1] + dp[i - 2] * 2 + dp[i - 3] * 5 + memo[now][i - 4]) % 1000000007;

    memo[now][i] = (memo[now][i - 1] + dp[i] * 4) % 1000000007;
    memo[t1][i] = (memo[t1][i - 1] + dp[i] * 2) % 1000000007;
    memo[t2][i] = (memo[t2][i - 1] + dp[i] * 2) % 1000000007;
  }

  return dp[n] % 1000000007;
}