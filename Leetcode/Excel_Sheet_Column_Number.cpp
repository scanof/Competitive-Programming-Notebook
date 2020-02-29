class Solution {
public:
    int titleToNumber(string s) {
        int num=0;
        int temp;
        for(int i=0; i<s.size(); i++){
            temp = s[i]-'A'+1;
            num+= temp*pow(26,(s.size()-i-1));
        }
        return num;
    }
};
