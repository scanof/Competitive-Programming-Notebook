class Solution {
public:
    unsigned long long combinationSum4(vector<int>& nums, int target) {
        unsigned long long dp[target+1];
        memset(dp, 0, sizeof dp);
        dp[0]=1;
        for(int i= 1; i<=target; ++i){
            for(int j : nums){
                if(i-j < 0) continue;
                dp[i]+= dp[i-j];
            }
        }
        return dp[target];
    }
};
