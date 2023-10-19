const int N = 1e5 + 10, K = 20;  //K  has to satisfy K> log nax + 1
ll st[N][K];
struct RMQ{
  ll neutro = inf;
  inline ll oper(ll a, ll b){ return a < b ? a : b; }
  RMQ(vi& a){
    forn(i, sz(a)) st[i][0] = a[i];
    for1(j, K-1)
      forn(i, sz(a) - (1 << j) + 1)
        st[i][j] = oper(st[i][j-1], st[i + (1 << (j-1))][j-1]);
  }
  ll query(int l, int r){
    if(l > r) return neutro;
    int j = 31 - __builtin_clz(r-l+1);
    return oper(st[l][j], st[r - (1 << j) + 1][j]);
  }
};