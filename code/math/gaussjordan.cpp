int gauss(vector<vector<double>> &a, vector<double> &ans) {
  int n = sz(a), m = sz(a[0]) - 1;
  vi where(m, -1);
  for(int col=0, row=0; col<m && row<n; ++col) {
    int sel = row;
    fore(i,row,n-1)
      if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if(abs(a[sel][col]) < eps) continue;

    fore(i,col,m) swap (a[sel][i], a[row][i]);
    where[col] = row;

    forn(i,n){
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j=col; j<=m; ++j) a[i][j] -= a[row][j] * c;
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  forn(i,m){
    if(where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
  }
  forn(i,n){
    double sum = 0;
    forn(j,m) sum += ans[j] * a[i][j];
    if(abs(sum - a[i][m]) > eps) return 0;
  }

  forn(i,m) if(where[i] == -1) return 1e9; /// infinitas soluciones
  return 1;
}
