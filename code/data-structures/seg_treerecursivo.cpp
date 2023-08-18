struct stree{
  int n, neutro = 1e9;  vi t;
  stree(int n): n(n), t(n<<2){}
  stree(vi a): n(sz(a)), t(n<<2){ build(1, 0, n-1, a); }
  inline int oper(int a, int b){ return min(a, b); }
  void build(int v, int tl, int tr, vi& a){// solo para el 2. constructor
    if(tl == tr){ t[v]= a[tl];  return; }
    int tm = (tr+tl)/ 2;
    build(v*2, tl, tm, a);
    build(v*2+1, tm+1, tr, a);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  int query(int v, int tl, int tr, int l, int r){
    if(tl > r || tr < l) return neutro;  // estoy fuera
    if(l <= tl && tr <= r) return t[v];
    int tm = (tl+tr)/2;
    return oper(query(v*2, tl, tm, l, r), query(v*2+1, tm+1, tr, l, r));
  }
  void upd(int v, int tl, int tr, int pos, int val){
    if(tl==tr){ t[v] = val;  return; }
    int tm = (tr+tl)/ 2;
    if(pos<= tm) upd(v*2, tl, tm, pos, val);
    else upd(v*2+1, tm+1, tr, pos, val);
    t[v] = oper(t[v*2], t[v*2+1]);
  }
  void upd(int pos, int val){ upd(1, 0, n-1, pos, val);}
  int query(int l, int r){ return query(1, 0, n-1, l, r);}
};