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