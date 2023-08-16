struct dsu{
  vi p, r; int comp;
  dsu(int n): p(n), r(n, 1), comp(n){iota(all(p), 0);}
  int find_set(int i){return p[i] == i ? i : p[i] = find_set(p[i]);}
  bool is_same_set(int i, int j){return find_set(i) == find_set(j);}
  void union_set(int i, int j){
    if((i = find_set(i)) == (j = find_set(j))) return;
    if(r[i] > r[j]) swap(i, j);
    r[j] += r[i];  r[i] = 0;
    p[i] = j;  --comp;
  }
};