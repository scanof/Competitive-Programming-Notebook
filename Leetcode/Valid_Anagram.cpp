#define forn(i,n) for(int i=0; i< (int)n; ++i)
class Solution {
public:
    bool isAnagram(string s, string t) {
        int let1[26],let2[26];
        memset(let1,0,sizeof let1);
        memset(let2,0,sizeof let2);
        int n1= s.size(), n2= t.size();
        if(n1!=n2) return false;
        forn(i,n1){
            char ch = s[i];
            ++let1[ch-'a'];
            ch= t[i];
            ++let2[ch-'a'];
        }
        forn(i,26){
            if(let1[i]!=let2[i]) return false;
        }
        return true;
    }
};
