const int N = 1e5 + 10;
int t[N << 2], lazy[N << 2];
struct stree{
  int n, l, r, val, neutro = 0;
  stree(int n): n(n){ forn(i, n << 2) t[i] = lazy[i] = 0; }
  stree(vector<int> &a){ n = sz(a); forn(i, n << 2) t[i] = lazy[i] = 0;
    build(1, 0, n-1, a);
  }
  inline int oper(int a, int b){ return a > b ? a : b; }
  inline void push(int v){
    if(lazy[v]){
      t[v << 1] += lazy[v];  lazy[v << 1] += lazy[v];
      t[(v << 1) | 1] += lazy[v];  lazy[(v << 1) | 1] += lazy[v];
      lazy[v] = 0;
    }
  }
  void build(int v, int tl, int tr, vi& a){
    if(tl == tr){
      t[v] = a[tl]; return;
    }
    int tm = (tl + tr) >> 1;
    build(v << 1, tl, tm, a), build((v << 1) | 1, tm+1, tr, a);
    t[v] = oper(t[v << 1], t[(v << 1) | 1]);
  }
  void upd(int v, int tl, int tr){
    if(tl > r || tr < l) return;
    if(l <= tl && tr <= r){
      t[v] += val;  lazy[v] += val;
      return ;
    }
    push(v);  int tm = (tl + tr) >> 1;
    upd(v << 1, tl, tm);  upd((v << 1) | 1, tm+1, tr);
    t[v] = oper(t[v << 1], t[(v << 1) | 1]);
  }
  int query(int v, int tl, int tr){
    if(tl > r || tr < l) return neutro;
    if(l <= tl && tr <= r) return t[v];
    push(v);  int tm = (tl + tr) >> 1;
    return oper(query(v << 1, tl, tm), query((v << 1) | 1, tm + 1, tr));
  }
  void update(int ql, int qr, int qval){  
    l = ql, r = qr, val = qval, upd(1, 0, n-1); }
  int query(int ql, int qr){ l = ql, r = qr;  return query(1, 0, n-1); }
};
