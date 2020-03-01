class Solution {
public:
    
    int convert(char ch){
        if(ch>='a' && ch<='z'){
            return ch-'a';
        }else if(ch>='A' && ch<= 'Z'){
            return ch - 'A';
        }else if(ch>='0' && ch<='9'){
            return ch - '0' + 26;
        }else{
            return -1;
        }
    }
    
    
    bool isPalindrome(string s) {
        int n = s.size();
        if(n==0) return true;
        int l= 0, r = n-1;
        while(l<r){
            int n1 = convert(s[l]), n2 = convert(s[r]);
            if(n1==-1){
                ++l;
                continue;
            }   
            if(n2==-1){
                --r;
                continue;
            }
            if(n1==n2){
                ++l; --r;
                continue;
            }else{
                return false;
            }
        }
        return true;
    }
};
