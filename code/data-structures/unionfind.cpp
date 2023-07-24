// Complejidad aprox O(1)
struct dsu{
  vi p, r; int comp;
  dsu(int n):comp(n), p(n), r(n, 1){ iota(all(p), 0);}
  int find_set(int i){return (p[i] == i ? i : p[i] = find_set(p[i]));}
  bool is_same_set(int i, int j){ return find_set(i) == find_set(j);}
  void union_set(int i, int j){
    if((x = find_set(x)) == (y = find_set(y))) return;
    if(r[x] > r[y]) swap(x, y);
    r[y] += r[x], r[x] = 0;
    p[x] = y;  --comp;
  }
};
