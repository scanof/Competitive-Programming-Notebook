#include <bits/stdc++.h>

#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout<< #x<< " " << x<<el
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)

using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct stree{
  int n, neutro = 0;   vii t;  vi lazy;
  stree(vi &a, string& s): n(sz(a)), t(n << 2), lazy(n << 2){ build(1, 0, n-1, a, s);}
  inline ii oper(ii a, ii b){ return {a.fi ^ b.fi, a.se ^ b.se}; }
  void build(int v, int tl, int tr, vi &a, string& s){
    if(tl == tr){
      if(s[tl] == '0') t[v].fi = a[tl];
      else t[v].se = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    build(v*2, tl, tm, a, s);
    build(v*2+1, tm+1, tr, a, s);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  void push(int v) {
    if(lazy[v] & 1){
      swap(t[2*v].fi, t[2*v].se); swap(t[2*v+1].fi, t[2*v+1].se);
      lazy[v*2] += lazy[v];   lazy[v*2+1] += lazy[v];
      lazy[v] = 0;
    }
  }
  void upd(int v, int tl, int tr, int l, int r) {
    if(tl > r || tr < l) return;
    if(l <= tl && tr <= r){
      swap(t[v].fi, t[v].se);
      lazy[v] += 1;   return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    upd(v*2, tl, tm, l, r);
    upd(v*2+1, tm+1, tr, l, r);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  ii query(int v, int tl, int tr, int l, int r) {
    if(tl > r || tr < l) return {neutro, neutro};
    if (l <= tl && tr <= r) return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return oper(query(v*2, tl, tm, l, r), query(v*2+1, tm+1, tr, l, r));
  }
  void upd(int l, int r){ upd(1, 0, n-1, l, r); }
  ii query(){ return query(1, 0, n-1, 0, n-1); }
};


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    vi a(n); forn(i, n) cin >> a[i];
    string s; cin >> s;

    stree st(a, s);

    int q; cin >> q;
    forn(i, q){
      int ty; cin >> ty;
      if(ty == 1){
        int l, r; cin >> l >> r;
        st.upd(--l, --r);
      } else{
        int g; cin >> g;
        if(g == 0) cout << st.query().fi << " ";
        else cout << st.query().se << " ";
      }
    }
    cout << el;
  }
}
