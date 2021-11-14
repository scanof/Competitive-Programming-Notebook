#define neutro 0
struct node{
  int sum, l, r;
};
struct stree{
  vector<int> rts;
  vector<node> t;
  int n, idx;
  inline int oper(int a, int b){ return a+b; }
  int build(int tl, int tr, vector<int> &a){
    int v = idx++;
    if(tl==tr){
      t[v].sum = a[tl]; return v;
    }
    int tm = (tl+tr)/2;
    t[v].l = build(tl, tm, a);
    t[v].r = build(tm+1, tr, a);
    t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
    return v;
  }
  stree(vector<int> &a){
    n = sz(a);
    t.resize(# define nax);
    idx = 0;
    rts.pb(0);
    build(0, n-1, a);
  }
  int query(int v, int tl, int tr, int l, int r){
    if(tl>r || tr<l) return neutro;
    if(l<=tl && tr<= r){
      return t[v].sum;
    }
    int tm = (tl+tr)/2;
    return oper(query(t[v].l, tl, tm, l, r), query(t[v].r, tm+1, tr, l, r));
  }
  int upd(int prev, int tl, int tr, int pos, int val){
    int v = idx++; t[v] = t[prev];
    if(tl==tr){
      t[v].sum = val; return v;
    }
    int tm = (tl+tr)/2;
    if(pos<=tm) t[v].l = upd(t[v].l, tl, tm, pos, val);
    else t[v].r = upd(t[v].r, tm+1, tr, pos, val);

    t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
    return v;
  }
  int query(int v, int l, int r){
    return query(v, 0, n-1, l, r);
  }

  void upd(int pos, int val){
    int id = upd(rts.back(), 0, n-1, pos, val);
    rts.pb(id);
  }
};
