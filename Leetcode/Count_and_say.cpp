class Solution {
public:
    string convert(string s){
        int n = s.size();
        int sum = 1;
        string a="";
        for(int i = 1; i<n; ++i){
            if(s[i]==s[i-1]){
                sum++;
            }else{
                a+= to_string(sum) + s[i-1];
                sum = 1;
            }
        }
        a+= to_string(sum) + s[n-1];
        return a;
    }
    
    string countAndSay(int n) {
        string s ="1";
        n--;
        if(n==0) return s;
        while(n--){
            s = convert(s);
        }
        return s;
    }
};
