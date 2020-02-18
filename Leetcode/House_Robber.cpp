class Solution {
public:
    int rob(vector<int>& nums) {
        int n= nums.size();
        if(n==0) return 0;
        int dp[2][n];
        memset(dp, 0,sizeof dp);
        dp[0][0]= nums[0];
        for(int i=1; i<n; ++i){
            dp[0][i]= nums[i] + dp[1][i-1];
            dp[1][i]= max(dp[0][i-1],dp[1][i-1]);
        }
        return max(dp[0][n-1],dp[1][n-1]);
    }
};
