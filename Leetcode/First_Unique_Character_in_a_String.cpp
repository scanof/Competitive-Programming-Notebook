class Solution {
public:
    int firstUniqChar(string s) {
        if(s.size()==0) return -1;
        int let[26];
        int ind[26];
        for(int i=0; i<26; i++){
            let[i]=0;
        }
        for(int i=0; i<s.size(); i++){
            if(let[s[i]-'a']==0) {
                ind[s[i]-'a']=i;
            }
            let[s[i]-'a']++;
        }
        int ans=INT_MAX;
        for(int i=0; i<26; ++i){
            if(let[i]==1)ans = min(ans, ind[i]);
        }
        if(ans==INT_MAX) return -1;
        return ans;
    }
};
