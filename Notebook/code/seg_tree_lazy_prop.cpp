#define neutro -1e9
struct stree{
  int n;   vector<int> t, lazy;
  stree(int m){
    n = m;    t.resize(n<<2);
    lazy.resize(n<<2);
  }
  stree(vector<int> &a){
    n = sz(a); t.resize(n<<2);   lazy.resize(n<<2);
    build(1,0, n-1, a);
  }
  inline int oper(int a, int b){ return max(a,b); }
  void build(int v, int tl, int tr, vector<int> &a){
    if(tl==tr){
      t[v]= a[tl]; return ;
    }
    int tm = tl + (tr-tl)/ 2;
    build(v*2, tl, tm, a);
    build(v*2+1, tm+1, tr, a);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  void push(int v) {
    t[v*2] += lazy[v]; lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v]; lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
  }
  void upd(int v, int tl, int tr, int l, int r, int val) {
    if(tl>r || tr<l) return ;
    if (l <= tl && tr <= r) {
      t[v] += val;
      lazy[v] += val; return ;
    }
    push(v);
    int tm = tl + (tr-tl)/ 2;
    upd(v*2, tl, tm, l, r, val);
    upd(v*2+1, tm+1, tr, l, r, val);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  int query(int v, int tl, int tr, int l, int r) {
    if(tl>r || tr<l) return neutro;
    if (l <= tl && tr <= r) return t[v];
    push(v);
    int tm = tl + (tr-tl)/ 2;
    return oper(query(v*2, tl, tm, l, r),
               query(v*2+1, tm+1, tr, l, r));
  }
  void upd(int l, int r, int val){ upd(1,0,n-1,l, r,val); }
  int query(int l, int r){ return query(1,0,n-1,l,r); }
};
