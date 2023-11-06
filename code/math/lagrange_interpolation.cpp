#include "mint.cpp"
const int N = 1e6;
mint f[N], fr[N];
void initC(){
  if(f[0] == 1) return; // Already precalculated
  f[0] = 1;
  for1(i, N-1) f[i] = f[i-1] * i;
  fr[N-1] = bpow(f[N-1], mod-2);
  fored(i, 1, N-1) fr[i-1] = fr[i] * i;
}
// mint C(int n, int k) { return k<0 || k>n ? 0 : f[n] * fr[k] * fr[n-k]; }
struct LagrangePol {
  int n;
  vector<mint> y, den, l, r;
  LagrangePol(vector<mint> f): n(sz(f)), y(f), den(n), l(n), r(n){// f[i] := f(i) 
    // Calcula interpol. pol P in O(n) := deg(P) = sz(v)-1 
    initC();
    forn(i, n) {
      den[i] = fr[n-1-i] * fr[i];
      if((n-1-i) & 1) den[i] = -den[i];
    }
  }
  mint eval(mint x){ // Evaluate LagrangePoly P(x) in O(n)
    l[0] = r[n-1] = 1;
    for1(i, n-1) l[i] = l[i-1] * (x - i + 1);
    fored(i, 0, n-2) r[i] = r[i+1] * (x - i - 1);
    mint ans = 0;
    forn(i, n) ans += l[i] * r[i] * y[i] * den[i];
    return ans;
  }
};