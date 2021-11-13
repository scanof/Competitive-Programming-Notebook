//K  has to satisfy K> log nax + 1
ll st[nax][K], a[nax], sum = 0;
void init(int N){
  forn(i,N) st[i][0] = a[i];
  for1(j,K-1)
    forn(i,N-(1 << j)+1)
      st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j - 1];
}
void get(int l, int r){
  for (int j = K-1; j >= 0; j--) {
    if ((1 << j) <= r - l + 1) {
      sum += st[l][j];
      l += 1 << j;
    }
  }
}
