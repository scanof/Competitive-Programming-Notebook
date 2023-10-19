// https://codeforces.com/contest/1860/problem/C
#include <bits/stdc++.h>

#define sz(v) ((int)v.size())
#define forn(i,n) for(int i=0; i< (int)n; ++i)

using namespace std;

typedef vector<int> vi;
struct stree{
  int neutro = 1e9, n, l, r, pos, val;  vi t;
  stree(int n): n(n), t(n << 2){}
  stree(const vi& a): n(sz(a)), t(n<<2){ build(1, 0, n-1, a); }
  inline int oper(int a, int b){ return a < b ? a : b; }
  void build(int v, int tl, int tr, const vi& a){// solo para el 2. constructor
    if(tl == tr){ t[v] = a[tl];  return; }
    int tm = (tl + tr) >> 1;
    build(v << 1, tl, tm, a), build((v << 1) | 1, tm+1, tr, a);
    t[v] = oper(t[v << 1], t[(v << 1) | 1]);
  }
  int query(int v, int tl, int tr){
    if(tl > r || tr < l) return neutro;  // estoy fuera
    if(l <= tl && tr <= r) return t[v];
    int tm = (tl + tr) >> 1;
    return oper(query(v << 1, tl, tm), query((v << 1) | 1, tm+1, tr));
  }
  void upd(int v, int tl, int tr){
    if(tl == tr){ t[v] = val;  return; }
    int tm = (tl + tr) >> 1;
    if(pos <= tm) upd(v << 1, tl, tm);
    else upd((v << 1) | 1, tm+1, tr);
    t[v] = oper(t[v << 1], t[(v << 1) | 1]);
  }
  void upd(int idx, int num){ pos = idx, val = num, upd(1, 0, n-1);}
  int query(int ql, int qr){ l = ql, r = qr;  return query(1, 0, n-1);}
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