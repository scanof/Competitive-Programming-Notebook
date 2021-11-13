const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];
inline int op(int a, int b){ return a+b; }
void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = op(t[i<<1], t[i<<1|1]);
}
void upd(int p, int val) {  // set value at position p
  for (t[p += n] = val; p > 1; p >>= 1) t[p>>1] = op(t[p], t[p^1]);
}
int query(int l, int r) {  // sum on interval [l, r)
  int v = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) v = op(v,t[l++]);
    if (r&1) v = op(v,t[--r]);
  }
  return v;
}
int main() {
  cin>> n;
  forn(i,n) cin >> t[n + i];
  build();
  return 0;
}