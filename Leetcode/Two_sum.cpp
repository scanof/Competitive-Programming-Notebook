#define pb push_back
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)

typedef pair<int,int> ii;
class Solution {
public:
    
    vector<int> twoSum(vector<int>& nums, int target) {
        ii arr[nums.size()];
        forn(i,nums.size()){
            arr[i]= ii(nums[i],i);
        }
        sort(arr,arr+nums.size());
        int l=0, r=nums.size()-1;
        while(l!=r){
            if(arr[l].fi+arr[r].fi==target){
                vector<int> a;
                a.pb(arr[l].se);
                a.pb(arr[r].se);
                return a;
            }else if(arr[l].fi+arr[r].fi>target) {
                --r;
            }else{
                ++l;
            }
        }
        vector<int> a;
        return a;
    }
};
