class Solution {
    public int solution(int n, int[] tops) {
        int k = 2 * n + 1;
        int MOD = 10007;
        int[] dp = new int[k + 1];
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= k; i++){
            //산모양인 경우
            if(i % 2 == 0 && tops[(i - 1) / 2] == 1){
                dp[i] = ((dp[i - 1] * 2) + dp[i - 2]) % MOD;
            }
            else {
                dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
            }
        }
        return dp[k];
    }
}