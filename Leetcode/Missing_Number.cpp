class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long sum = 1LL*n*(n+1)/2;
        for(int i=0; i<n; i++){
            sum-=nums[i];
        }
        return sum;
    }
};
