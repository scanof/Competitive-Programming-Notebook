// https://codeforces.com/contest/1860/problem/C
#include <bits/stdc++.h>

#define sz(v) ((int)v.size())
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)

using namespace std;

typedef vector<int> vi;

const int N = 3e5;  // limit for array size
int t[2 * N];
struct stree{ 
  int n, neutro = 1e9;
  stree(int n): n(n){ forn(i, 2*n) t[i] = neutro; }
  stree(vi a): n(sz(a)){ build(a); }
  inline int op(int a, int b){ return min(a, b); }
  void build(vi& a) { 
    forn(i, n) t[n + i] = a[i];
    fored(i, 1, n-1) t[i] = op(t[i<<1], t[i<<1|1]);
  }
  int query(int l, int r) {  // [l, r]
    int vl = neutro, vr = neutro;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if(l&1) vl = op(vl, t[l++]);
      if(r&1) vr = op(t[--r], vr);
    }
    return op(vl, vr);
  }
  void upd(int p, int val) {  // set val at position p (0 - idx)
    for (t[p += n] = val; p > 1; p >>= 1) t[p>>1] = op(t[p], t[p^1]);
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  
  int tt; cin >> tt;
  while(tt--){
    int n; cin >> n;
    vi p(n); forn(i, n) cin >> p[i];

    stree st(vi(n+1, 1));
    vi mins(n);
    forn(i, n) mins[i] = min((i ? mins[i-1] : int(1e9)), p[i]);

    int ans = 0;
    forn(i, n){
      if(p[i] == mins[i]) ++ans;
      else{
        int mn = st.query(1, p[i]-1);
        if(mn == 1) st.upd(p[i], 0); 
        else ++ans;
      }
    }
    cout << n - ans << endl;
  }
}