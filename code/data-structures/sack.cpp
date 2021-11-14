// Time Complexity O(N*log(N))
int timer;
int cnt[nax], big[nax], fr[nax], to[nax], who[nax];
vector<int> g[nax];
int pre(int u, int p){
  int sz = 1, tmp;
  who[timer] = u;
  fr[u] = timer++;
  ii best = {-1, -1};
  for(int v: g[u]){
    if(v==p) continue;
    tmp = pre(v,u);
    sz+=tmp;
    best = max(best, {tmp, v});
  }
  big[u] = best.se;
  to[u] = timer-1;
  return sz;
}
void add(int u, int x) { /// x == 1 add, x == -1 delete
  cnt[u] += x;
}
void dfs(int u, int p, bool keep = true){
  for(int v: g[u])
    if(v!=p && v!=big[u])
      dfs(v,u, 0);
  if(big[u]!=-1) dfs(big[u], u);
  /// add all small
  for(int v: g[u])
    if(v!=p && v!=big[u])
      for(int i = fr[v]; i<= to[v]; ++i)
        add(who[i],1);
  add(u,1);
  /// Answer queries
  if(!keep)
    for(int i = fr[u]; i<= to[u]; ++i)
      add(who[i],-1);
}
void solve(int root){
  timer = 0;
  pre(root, root);
  dfs(root, root);
}
