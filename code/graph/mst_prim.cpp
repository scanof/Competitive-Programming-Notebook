//Complexity O(E * log V)
vector<ii> g[nax];
bool seen[nax];
priority_queue<ii> pq;
void process(int u) {
  seen[u] = true;
  for (ii v: g[u])
    if (!seen[v.fi])
      pq.push(ii(-v.se, v.fi));
}
int prim(int n){
  process(0);
  int total = 0, u, w;
  while (sz(pq)){
    ii e = pq.top(); pq.pop();
    tie(w,u) = e; w*=-1;
    if (!seen[u])
      total += w, process(u);
  }
  return total;
}

