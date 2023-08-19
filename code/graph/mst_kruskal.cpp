struct edge{
  int u, v, w;
  edge(int u, int v, int w): u(u), v(v), w(w){}
  bool operator < (const edge &o) const{ return w < o.w;}
};
vector<edge> g;
void kruskal(int n){
  sort(all(g));  dsu uf(n); // union-find
  for(auto& [u, v, w]: g) 
    if(!uf.is_same_set(u, v)) uf.union_set(u, v);
}