// Complejidad aprox O(1)
struct dsu{
  vi p, r; int num_sets;
  void init(int n){
    p.assign(n, 0), r.assign(n, 1), num_sets = n;
    iota(all(p), 0);
  }
  int find_set(int i){
    return (p[i] == i ? i : p[i] = find_set(p[i]));
  }
  bool is_same_set(int i, int j){
    return find_set(i) == find_set(j);
  }
  void union_set(int i, int j){
    int x = find_set(i), y = find_set(j);
    if(x == y) return;
    if(r[x] > r[y]) swap(x, y);
    p[x] = y;
    r[y] += r[x], r[x] = 0;
    --num_sets;
  }
};
