class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0) return "";
        string s="";
        int j= 0;
        while(true){
            char ch;
            if(strs[0].size()>j){
                ch = strs[0][j];
            }else return s;
            
            for(int i = 0; i< strs.size(); ++i){
                if(strs[i].size()> j && strs[i][j]==ch){
                    
                }else return s;
            }
            s+= ch; 
            ++j;
        }
    }
};
