class Solution {
public:
    int n, m;
    string p, s;
    vector<vector<int>> dp;
    
    int go(int i, int j){
      if(i==n){
        if(j>=m){
          return 1;
        }
        if(j+1<m && p[j+1]=='*'){
          return go(i,j+2);
        }
        return 0;
      }
      if(j>=m){
        return 0;
      }
      int &r = dp[i][j];
      if(r!=-1) return r;
      r = 0;

      if(j+1<m && p[j+1]=='*'){
        r |= go(i,j+2);
        if(p[j]==s[i] || p[j]=='.'){
          r|= go(i+1, j);
          return r;
        }
      }
      if(s[i]==p[j] || p[j]=='.'){
        r|= go(i+1, j+1);
      }
      return r;
    }
    
    bool isMatch(string s1, string p1) {
        s = s1, p = p1;
        n = s.size();
        m = p.size();
        dp = vector<vector<int>>(n, vector<int>(m,-1));
        return go(0,0);
    }
};
