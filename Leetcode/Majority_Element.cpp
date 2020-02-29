class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> mapa;
        int maxi=0, maxelement =0;
        for(int i= 0; i<nums.size(); ++i){
            mapa[nums[i]]++;
            if(maxi < mapa[nums[i]]){
                maxi = mapa[nums[i]];
                maxelement = nums[i];
            }
        }
        return maxelement;
    }
};
