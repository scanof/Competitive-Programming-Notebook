vi g[nax], gr[nax], ts;
int scc[nax];
bool seen[nax];
void dfs1(int u){
  seen[u] = true;
  for (int v: g[u])
    if (!seen[v])
      dfs1(v);
  ts.pb(u);
}
void dfs(int u, int comp){
  scc[u] = comp;
  for (int v : gr[u])
    if (scc[v] == -1)
      dfs(v, comp);
}
// Retorna la cantidad de componentes
int find_scc(int n){
  //TENER CREADO EL GRAFO REVERSADO gr
  forn(i,n) if(!seen[i]) dfs1(i);
  reverse(all(ts));
  int comp = 0;
  for(int u: ts)
    if (scc[u] == -1) dfs(u, comp++);
  return comp;
}
