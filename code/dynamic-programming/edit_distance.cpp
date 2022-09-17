// O(m*n) donde cada uno es el tamano de cada string
int editDist(string &s1, string &s2){
  int m = sz(s1), n = sz(s2);
  int dp[m+1][n+1];
  forn(i,m+1)
    forn(j,n+1){
      if (i==0) dp[i][j] = j;
      else if (j==0) dp[i][j] = i;
      else if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
      else dp[i][j] = 1 + min({dp[i][j-1],  // Insert
                              dp[i-1][j],  // Remove
                              dp[i-1][j-1]}); // Replace
    }
  return dp[m][n];
}