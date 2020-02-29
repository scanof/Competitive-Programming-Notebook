class Solution {
public:
    int convert(char c){
        if(c=='I') return 1;
        if(c=='V') return 5;
        if(c=='X') return 10;
        if(c=='L') return 50;
        if(c=='C') return 100;
        if(c=='D') return 500;
        if(c=='M') return 1000;
        return 0;
    }
    
    int romanToInt(string s) {
        int ans=0;
        for(int i=0; i<s.size()-1; ++i){
            if(convert(s[i])<convert(s[i+1]))  ans-=convert(s[i]);
            else ans+=convert(s[i]);
        }
        ans += convert(s[s.size()-1]);
        return ans;
    }
};
