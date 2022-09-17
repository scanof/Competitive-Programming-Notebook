// Complexity: V + E
// Given an undirected graph
int n, timer, tin[nax], low[nax];
vi g[nax]; // adjacency list of graph

void dfs(int u, int p) {
  tin[u] = low[u] = ++timer;
  int children=0;
  for (int v : g[u]) {
    if (v == p) continue;
    if (tin[v]) low[u] = min(low[u], tin[v]);
    else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > tin[u]) // BRIDGE
        IS_BRIDGE(u, v);

      if (low[v] >= tin[u] && p!=-1) // POINT
        IS_CUTPOINT(u);
      ++children;
    }
  }
  if(p == -1 && children > 1) // POINT
    IS_CUTPOINT(u);
}

void find_articulations() {
  timer = 0;
  forn(i,n) if(!tin[i]) dfs(i,-1);
}
