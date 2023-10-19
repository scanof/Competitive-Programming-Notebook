// https://codeforces.com/group/hzSLIARNBN/contest/467095/problem/H
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) v.size()
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << ": " << x <<  el;

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

const int len = 1e7, neutro = 1e9;
struct node{ int mn, l, r; };
struct stree{
  vi rts{0};  vector<node> t;
  int n, idx{0}, l, r, pos, val;
  inline int oper(int a, int b){ return a < b ? a : b; }
  stree(const vi &a): n(sz(a)), t(len){ build(0, n-1, a); }
  int build(int tl, int tr, const vi &a){
    int v = idx++;
    if(tl == tr){ t[v].mn = a[tl]; return v; }
    int tm = (tl + tr) >> 1;
    t[v].l = build(tl, tm, a),  t[v].r = build(tm + 1, tr, a);
    t[v].mn = oper(t[t[v].l].mn, t[t[v].r].mn);
    return v;
  }
  int que(int v, int tl, int tr){
    if(tl > r || tr < l) return neutro;
    if(l <= tl && tr <= r) return t[v].mn;
    int tm = (tl + tr) >> 1;
    return oper(que(t[v].l, tl, tm), que(t[v].r, tm + 1, tr));
  }
  int upd(int prv, int tl, int tr){
    int v = idx++;
    t[v] = t[prv];
    if(tl == tr){  t[v].mn = val;  return v; }
    int tm = (tl + tr) >> 1;
    if(pos <= tm) t[v].l = upd(t[v].l, tl, tm);
    else t[v].r = upd(t[v].r, tm + 1, tr);
    t[v].mn = oper(t[t[v].l].mn, t[t[v].r].mn);
    return v;
  }
  int query(int v, int cl, int cr){ l = cl, r = cr;  return que(v, 0, n-1); }
  void upd(int i, int x){ pos = i, val = x, rts.pb(upd(rts.back(), 0, n-1)); }
};

const int N = 3e5 + 20;
vi g[N], deeps[N];
int in[N], out[N], timer;
int dep[N], rt_dep[N];

void pre(int u, int p, int dd){
  in[u] = timer++;
  dep[u] = dd;
  deeps[dd].pb(u);
  for(int v : g[u]){
    if(v == p) continue;
    pre(v, u, dd + 1);
  }
  out[u] = timer - 1;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, r;
  cin >> n >> r;
  --r;
  vi val(n);
  forn(i,n) cin >> val[i];
  
  forn(i, n-1){
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].pb(v);
    g[v].pb(u);
  }
  pre(r, r, 0);

  stree st(vi(n, neutro));
  forn(i, N){
    for(int u : deeps[i]){
      st.upd(in[u], val[u]);
    }  
    rt_dep[i] = st.rts.back();
  }
  int m;
  cin >> m;

  int lst = 0;
  forn(i,m){
    int p, q;
    cin >> p >> q;
    int x, k;
    x = (p + lst)%n;
    k = (q + lst)%n;
    int dd = dep[x] + k;
    lst = st.query(rt_dep[dd], in[x], out[x]);
    cout << lst << el;
  } 
}