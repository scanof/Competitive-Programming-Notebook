class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int l = 1, r= 1;
        int n = nums.size();
        if(n==0) return 0;
        int len = 1;
        while(r<n){
            if(nums[r]==nums[r-1] || nums[r]==nums[l-1]){
                while(r<n && (nums[r]==nums[r-1] || nums[r]==nums[l-1]) ){
                    r++;
                }
                if(r>=n)  break;
            }
            swap(nums[r],nums[l]);
            ++len;
            ++r;
            ++l;
        }
        return len;
    }
};
