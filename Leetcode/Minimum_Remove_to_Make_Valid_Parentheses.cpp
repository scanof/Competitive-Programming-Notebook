#define forn(i,n) for(int i=0; i< (int)n; ++i)
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n= s.size();
        char nuevo[100005], t[100005];
        int y=0;
        int par= 0;
        stack<int> pila;
        forn(i,n){
            if(s[i]=='('){
                nuevo[y]=s[i];
                ++par;
                pila.push(y++);
            }else if(s[i]==')'){
                if(par>0){
                    nuevo[y++]=s[i];
                    pila.pop();
                    --par;
                }
            }else{
                nuevo[y++]=s[i];
            }
        }
        unordered_map<int,int> m;
        while(!pila.empty()){
            ++m[pila.top()];
            pila.pop();
        }
        int j=0;
        forn(i,y){
            if(m[i]>0){

            }else{
                t[j++]= nuevo[i];
            }
        }
        t[j]=0;
        string de = t;
        return de;
        
    }
};
