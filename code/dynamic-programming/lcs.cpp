const int nax = 1005;
int dp[nax][nax];
int lcs(const string &s, const string &t){
  int n = sz(s), m = sz(t);
  forn(j,m+1) dp[0][j] = 0;
  forn(i,n+1) dp[i][0] = 0;
  for1(i,n){
    for1(j,m){
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      if (s[i-1] == t[j-1]){
        dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
      }
    }
  }
  return dp[n][m];
}

