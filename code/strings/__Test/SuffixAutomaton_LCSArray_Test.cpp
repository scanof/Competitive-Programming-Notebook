// https://codeforces.com/gym/103388/problem/B
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'
#define pb push_back
#define sz(v) int(v.size())

using namespace std;

typedef vector<int> vi;

struct node {
  int len, link;
  map<char, int> to;
  bool terminal;
};

const int N = 4e5+1; // el doble del MAXN
node st[N];
int sz, last;
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[sz = last = 0].link = -1;
    for(char c: s) extend(c);
  }
  void extend(char c) {
    int v = ++sz, p = last;
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p != -1) {
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else {
        int w = ++sz;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        while (p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    last = v;
  }
  vi lcs(string &T){
    int v = 0, l = 0;
    vi ans(sz(T));
    forn(i, sz(T)){
      while(v && !st[v].to.count(T[i])) v = st[v].link, l = st[v].len;
      if(st[v].to.count(T[i])) v = st[v].to[T[i]], ++l;
      ans[i] = l; // LCS(S, T) ending at position i
    }
    return ans;
  }
};

struct stree{
  int n, neutro = 0;  vi t, lazy;
  stree(int n): n(n), t(n<<2), lazy(n<<2){}
  inline int op(int a, int b){ return max(a, b); }
  void push(int v) {
    t[v*2] += lazy[v];  lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];  lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
  }
  void upd(int v, int tl, int tr, int l, int r, int val) {
    if(tl>r || tr<l) return;
    if(l <= tl && tr <= r){ t[v] += val; lazy[v] += val; return; }
    push(v);
    int tm = (tl + tr)/ 2;
    upd(v*2, tl, tm, l, r, val);
    upd(v*2+1, tm+1, tr, l, r, val);
    t[v] = op(t[v*2], t[v*2+1]);
  }
  int query(int v, int tl, int tr, int l, int r) {
    if(tl>r || tr<l) return neutro;
    if(l <= tl && tr <= r) return t[v];
    push(v);
    int tm = (tl + tr)/ 2;
    return op(query(v*2, tl, tm, l, r), query(v*2+1, tm+1, tr, l, r));
  }
  void upd(int l, int r, int val){ upd(1,0,n-1,l, r,val); }
  int query(int l, int r){ return query(1,0,n-1,l,r); }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m;  cin >> n >> m;
  string s; cin >> s;
  s += s;
  string t = "";
  forn(i, m){
    string p; cin >> p;
    if(i) t.pb('#');
    for(char c: p) t.pb(c);
  }

  suf_aut sa(t);
  vi a = sa.lcs(s);
  stree st(sz(a));
  int ans = n;
  forn(i, sz(a)){
    if(i >= n) st.upd(0, i-n, -1);
    if(a[i]){
      int l = i - a[i] + 1;
      int cur = st.query(l, l);
      if(a[i] > cur) st.upd(l, l, a[i] - cur);
    }
    if(i >= n) ans = min(ans, st.query(0, sz(a)-1));
  }
  cout << ans << el;
}