// Complejidad O( E* log V)
struct edge{
  int u, v, w;
  edge(int u, int v, int w):u(u),v(v),w(w){}
  bool operator < (const edge &o) const{
    return w < o.w;//if want max, change this
  }
};
vector<edge> g, st;
dsu uf; // union-find
int kruskal(int n){
  uf.init(n);
  sort(all(g));
  int total = 0, u, v, w;
  for(int i = 0; i < sz(g) && uf.numSets!=1; ++i){
    u = g[i].u;
    v = g[i].v;
    w = g[i].w;
    if(!uf.isSameSet(u,v)){
      total+= w;
      uf.unionSet(u,v);
      st.pb(g[i]);
    }
  }
  return total;
}
