class Solution {
public:
    const int INF = 1e9;
    int coinChange(vector<int>& coins, int amount) {
        int dp[amount+1];
        dp[0]=0;
        for(int i=1; i<=amount; ++i){
            dp[i]=INF;
            for(int coin: coins){
                if(i-coin<0) continue;
                dp[i]= min(dp[i], 1+ dp[i-coin]);
            }
        }
        return (dp[amount]==INF ? -1 : dp[amount]);
    }
};
