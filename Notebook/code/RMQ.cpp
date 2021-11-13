//K  has to satisfy K> log nax + 1
int st[nax][K], a[nax];
int logp[nax];
void init(int N){
//  logp[1] = 0;
//  for (int i = 2; i < nax; i++) logp[i] = logp[i/2] + 1;

  forn(i,N) st[i][0] = a[i];
  for1(j,K-1)
    forn(i,N-(1 << j)+1)
      st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

int get(int l, int r){ //assuming L<=R
  if(l>r) return inf;
//  int j = logp[r - l + 1];
  int j = 31 - __builtin_clz(r-l+1);
  return min(st[l][j], st[r - (1 << j) + 1][j]);
}
