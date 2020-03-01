class Solution {
public:
    bool isValid(string s) {
        stack<char> pila;
        for(int i= 0; i< s.size(); ++i){
            if(s[i]=='(' ||s[i]=='[' ||s[i]=='{') pila.push(s[i]);
            else{
                if(s[i]==')')
                    if(pila.empty() || pila.top()!='(') return false;
                if(s[i]=='}')
                    if(pila.empty() || pila.top()!='{') return false;
                if(s[i]==']')
                    if(pila.empty() || pila.top()!='[') return false;
                pila.pop();
            }
        }
        return pila.empty();
    }
};
