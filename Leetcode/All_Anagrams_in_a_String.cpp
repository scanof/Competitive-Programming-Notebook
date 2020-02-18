#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define pb push_back

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int let1[26], let2[26];
        memset(let1, 0, sizeof let1);
        memset(let2, 0, sizeof let2);
        vector<int> a;
        int S = s.size(), P= p.size();
        a.reserve(S);
        if(P>S) return a;
        bool iguales = true;
        forn(i,P){
            char ch= s[i];
            ++let1[ch-'a'];
            ch = p[i];
            ++let2[ch-'a'];
        }        
        forn(i,26){
            if(let1[i]!=let2[i]){
                iguales = false;
                break;
            }
        }
        if(iguales) a.pb(0);
        fore(i,P,S-1){
            char ch = s[i];
            ++let1[ch-'a'];
            ch= s[i-P];
            --let1[ch-'a'];
            iguales= true;
            forn(j,26){
                if(let1[j]!=let2[j]){
                    iguales = false;
                    break;
                }
            }
            if(iguales) a.pb(i-P+1);
        }
        return a;
    }
};
