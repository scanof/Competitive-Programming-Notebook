const int eps = 0, mod = 1e9+7;

int gauss(vector<vi> &a, vi &ans) {
  int n = sz(a), m = sz(a[0]) - 1;
  vi where(m, -1);
  for(int col=0, row=0; col<m && row<n; ++col) {
    int sel = row;
    fore(i,row,n-1)
      if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if(abs(a[sel][col]) <= eps) continue;

    fore(i,col,m) swap (a[sel][i], a[row][i]);
    where[col] = row;

    forn(i,n){
      if (i != row) {
        int c = 1LL*a[i][col] * inv(a[row][col])%mod;
        for (int j=col; j<=m; ++j) a[i][j] = (mod + a[i][j] - (1LL*a[row][j] * c)%mod)%mod;
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  forn(i,m){
    if(where[i] != -1) ans[i] = 1LL*a[where[i]][m] * inv(a[where[i]][i])%mod;
  }
  forn(i,n){
    ll sum = 0;
    forn(j,m) sum = (sum + 1LL*ans[j] * a[i][j])%mod;
    if(abs(sum - a[i][m]) > eps) return 0;
  }

  forn(i,m) if(where[i] == -1) return 1e9; /// infinitas soluciones
  return 1;
}
