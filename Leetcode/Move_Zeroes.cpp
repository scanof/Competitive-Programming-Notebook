class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);
        int pt=0;
        for(int i=0; i<nums.size(); ++i){
            if(nums[i]!=0){
                ans[pt]=nums[i];
                pt++;  
            } 
        }
        nums=ans;
    }
};
