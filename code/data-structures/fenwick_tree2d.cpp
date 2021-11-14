struct fwtree{ /// 1-indexed
  vector<vector<ll>> bit;
  int n, m;
  fwtree(){}
  fwtree(int n, int m):n(n),m(m){
    bit = vector<vector<ll>>(n+1, vector<ll>(m+1,0));
  }
  ll sum(int x, int y) {
    ll v = 0;
    for (int i = x; i > 0; i -= i&(-i) )
      for (int j = y; j > 0; j -= j&(-j) )
        v += bit[i][j];
    return v;
  }

  void add(int x, int y, ll dt) {
    for (int i = x; i <= n; i += i&(-i) )
      for (int j = y; j <= m; j += j&(-j) )
        bit[i][j] += dt;
  }
};