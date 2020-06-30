class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        string ans = "";
        if(numRows==1) return s;
        for(int i = 1; i<= numRows; ++i){
            int j = (numRows-1)*2 - 2*(i-1);
            int k = 2*(i-1);
            int idx = 0 + i - 1; 
            int prev = 0 + i - 1; 
            if(idx<n){
                ans.push_back(s[idx]);
            }
            while(idx < n ){
                idx += j;
                if(idx!= prev && idx<n){
                    ans.push_back(s[idx]);    
                }
                prev = idx;
                idx += k;
                    
                if(idx!=prev && idx<n){
                    ans.push_back(s[idx]);
                }
                prev = idx;
            }
        }
        return ans;
    }
};
