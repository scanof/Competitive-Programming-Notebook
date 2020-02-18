class Solution {
public:
    int climbStairs(int n) {
        int dp[n+1];
        memset(dp, 0,sizeof dp);
        dp[0]=1;
        for(int i= 1; i<=n; ++i ){
            if(i-2>=0) dp[i]+= dp[i-1]+ dp[i-2] ;
            else if(i-1>=0) dp[i]+= dp[i-1];
            cout<< dp[i]<<" ";
        }
        return dp[n];
    }     
};
