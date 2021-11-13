vector<int> g[nax];
int len[nax], dep[nax], in[nax], out[nax], head[nax], par[nax], idx;
void dfs_sz( int u, int d ) {
  dep[u] = d;
  int &sz = len[u]; sz = 1;
  for( auto &v : g[u] ) {
    if( v == par[u] ) continue;
    par[v] = u; dfs_sz(v, d+1);
    sz += len[v];
    if(len[ g[u][0] ] < len[v]) swap(g[u][0], v);
  }
  return ;
}
void dfs_hld( int u) {
  in[u] = idx++;
  arr[in[u]] = val[u]; /// to initialize the segment tree
  for( auto& v : g[u] ) {
    if( v == par[u] ) continue;
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  out[u] = idx-1;
}
void upd_hld( int u, int val ) {
  upd_DS(in[u], val);
}
int query_hld( int u, int v ) {
  int val = neutro;
  while( head[u] != head[v] ) {
    if( dep[ head[u] ] < dep[ head[v] ] ) swap(u, v);
    val = val + query_DS(in[ head[u] ], in[u]);
    u = par[ head[u] ];
  }
  if( dep[u] > dep[v] ) swap(u, v);
  val = val+query_DS(in[u], in[v]);
  return val;
/// when updates are on edges use: (line 36)
///   if (dep[u] == dep[v]) return val;
///   val = val+query_DS(in[u] + 1, in[v]);
}
void build(int root) {
  idx = 0; /// DS index [0, n)
  par[root] = head[root] = root;
  dfs_sz(root, 0);
  dfs_hld(root);
  /// initialize DS
}
