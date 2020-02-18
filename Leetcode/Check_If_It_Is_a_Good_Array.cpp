#define forn(i,n) for(int i=0; i< (int)n; ++i)
class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int n= nums.size();
        if(nums.size()==1 && nums[0]==1){
            return true;
        }
        if(n==0 || n==1) return false;
        int number=nums[0];
        forn(i,n){
            number=__gcd(number,nums[i]);
            if(number==1) return true;
        }
        return false;
    }
};
