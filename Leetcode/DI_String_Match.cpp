class Solution {
public:
    vector<int> diStringMatch(string S) {
        int l=0, r=S.size();
        vector<int> nums;
        nums.reserve(S.size());
        for(int i=0; i<S.size(); ++i){
            if(S[i]=='I'){
                nums.push_back(l++);
            }else{
                nums.push_back(r--);
            }
        }
        nums.push_back(r);
        return nums;
    }
};
