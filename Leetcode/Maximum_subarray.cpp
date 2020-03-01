class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n= nums.size();
        long long sum= 0;
        long long best = nums[0];
        for(int i= 0; i<nums.size(); ++i){
            if(sum+nums[i]<0){
                sum = 0;
            }else{
                sum+= nums[i];
                best = max(best, sum);
            }    
            best = max(best, (long long)nums[i]);
        }
        return best;
    }
};
