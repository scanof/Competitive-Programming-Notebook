#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)

class Solution {
public:
    
    bool checkInclusion(string s1, string s2) {
        int let1[26], let2[26];
        memset(let1, 0, sizeof let1);
        memset(let2, 0, sizeof let2);
        int n1= s1.size(), n2= s2.size();
        if(n1>n2){
            return false;
        }
        forn(i,n1){
            char ch= s1[i];
            ++let1[ch-'a'];
            ch = s2[i];
            ++let2[ch-'a'];
        }   
        bool iguales= true;
        forn(i,26){
            if(let1[i]!=let2[i]){
                iguales = false;
                break;
            }
        }
        if(iguales) return true;
        fore(i,n1,n2-1){
            char ch= s2[i];
            ++let2[ch-'a'];
            ch = s2[i-n1];
            --let2[ch-'a'];
            iguales= true;
            forn(i,26){
                if(let1[i]!=let2[i]){
                    iguales = false;
                    break;
                }
            }
            if(iguales) return true;
        }
        return false;
    }
};
