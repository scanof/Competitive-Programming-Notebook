#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int abc[200];
        forn(i,200){
            abc[i]=-1;
        }
        int n= s.size();
        if(n==0){
            return 0;
        }
        int nums[n];
        int ult= -1;
        nums[0]=1;
        int maxi=1;
        abc[s[0]-' ']=0;
        for1(i,n-1){
            char ch = s[i];
            if(abc[ch-' ']==-1){
                nums[i] = nums[i-1]+1;
            }else if(ult<abc[ch-' ']){
                nums[i]= i-abc[ch-' '] ;
                ult=abc[ch-' '];
            }else{
                nums[i] = nums[i-1]+1;
            }
            abc[ch-' ']=i;
            maxi=max(maxi,nums[i]);
        }
        return maxi;
    }
};
