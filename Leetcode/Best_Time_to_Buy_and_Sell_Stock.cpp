class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n= prices.size();
        if(n<=1) return 0;
        int dp[2][n];
        memset(dp, 0, sizeof dp);
        dp[0][0]= prices[0];
        for(int i=1; i<n; ++i){
            dp[0][i]= dp[0][i-1];
            dp[1][i]= dp[1][i-1];
            if(prices[i]< dp[0][i]){
                dp[0][i]= prices[i];
                dp[1][i]= 0;
            }else{
                dp[1][i]= max(prices[i], dp[1][i]);
            }
            
        }
        int best= 0;
        for(int i= 0; i<n; ++i){
            best= max(best, dp[1][i]-dp[0][i]);
            cout<< dp[0][i]<< " "<<dp[1][i]<<endl;
        }
        return best;
    
    }
};
