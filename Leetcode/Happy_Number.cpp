class Solution {
public:
    int work = -1;
    unordered_set<long long> mapa;
    string square(string a) {
        long long ans = 0;
        for(char c: a) {
            ans += (c-'0')*(c-'0');
        }
        if(ans == 1) work =1;
        if(mapa.count(ans)){
            work = 0;
        }else{
            mapa.insert(ans);
        }
        return to_string(ans);
    }
    bool isHappy(int n) {
        string s = to_string(n);
        while(work==-1){
            s= square(s);
        }
        return work;
    }
};
