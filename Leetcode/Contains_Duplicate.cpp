class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mapa;
        for(int i= 0; i< nums.size(); ++i){
            mapa[nums[i]]++;
            if(mapa[nums[i]]>1) return true;
        }
        return false;
    }
};
