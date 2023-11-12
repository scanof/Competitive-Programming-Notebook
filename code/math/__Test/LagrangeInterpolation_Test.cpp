// https://codeforces.com/gym/104505/problem/A
#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define fore(i,l,r) for(int i=l; i<=r; ++i)
#define fored(i,l,r) for(int i=r; i>=l; --i)
#define el '\n'
#define sz(v) int(v.size())

typedef long long ll;
const int mod = 1e9 + 7;
template <class T>
T bpow(T b, int e) {
  T a(1);
  do{
    if(e & 1) a *= b;
    b *= b;
  }while(e >>= 1);
  return a;
}
struct mint {
  int x;
  mint(): x(0){}
  mint(ll v) : x((v % mod + mod) % mod) {} // be careful of negative numbers!
  // Helpers to shorten code
  #define add(a, b) a + b >= mod ? a + b - mod : a + b
  #define sub(a, b) a < b ? a + mod - b : a - b
  #define yo *this
  #define cmint const mint&
  
  mint &operator += (cmint o) { return x = add(x, o.x), yo; }
  mint &operator -= (cmint o) { return x = sub(x, o.x), yo; }
  mint &operator *= (cmint o) { return x = ll(x) * o.x % mod, yo; }
  mint &operator /= (cmint o) { return yo *= bpow(o, mod-2); }

  mint operator + (cmint b) const { return mint(yo) += b; }
  mint operator - (cmint b) const { return mint(yo) -= b; }
  mint operator * (cmint b) const { return mint(yo) *= b; }
  mint operator / (cmint b) const { return mint(yo) /= b; }

  mint operator - () const { return mint() - mint(yo); }
  bool operator == (cmint b) const { return x == b.x; }
  bool operator != (cmint b) const { return x != b.x; }

  friend ostream& operator << (ostream &os, cmint p) { return os << p.x; }
  friend istream& operator >> (istream &is, mint &p) { return is >> p.x; }
};

const int N = 1e6;
mint f[N], fr[N];
void initC(){
  if(f[0] == 1) return; // Already precalculated
  f[0] = 1;
  for1(i, N-1) f[i] = f[i-1] * i;
  fr[N-1] = bpow(f[N-1], mod-2);
  fored(i, 1, N-1) fr[i-1] = fr[i] * i;
}
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

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mint n;  int k;
  cin >> n >> k;
  vector<mint> num(2*k + 10);
  auto den = num;
  for1(i, sz(num)-1) {
    num[i] = num[i-1] + bpow(mint(i), k) * bpow(n-i+1, k);
    den[i] = den[i-1] + bpow(n-i+1, k);
  }
  LagrangePol p_num(num), p_den(den);
  cout << p_num.eval(n) / p_den.eval(n) << el;
}