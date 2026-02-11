#include "../../template.h"

// https://cses.fi/problemset/task/1197/
const int N = 2501;
const ll inf = 1e18;

vector<ii> g[N];
ll dist[N];
int pa[N];

void bellman_ford(int s, int n){
  forn(i, n) dist[i] = (i == s ? 0 : inf);
  forn(_, n-1){
    forn(u, n){
      if(dist[u] == inf) continue; // Unreachable
      for(auto& [v, w] : g[u])
        if(dist[u] + w < dist[v])
          dist[v] = dist[u] + w, pa[v] = u;
    }
  }
  int start = -1;
  forn(u, n){
    if(dist[u] == inf) continue;  // Unreachable
    for(auto& [v, w] : g[u])
      if(dist[u] + w < dist[v]) start = v;
  }
  
  if(start == -1) cout << "NO" << el;
  else{  // Si se necesita reconstruir
    cout << "YES" << el;
    forn(_, n) start = pa[start];
    vi cycle{ start }; 
    int v = start;  
    while(pa[v] != start) v = pa[v], cycle.pb(v);
    cycle.pb(start); // solo si se necesita que vuelva al start
    reverse(all(cycle));
    for(int u: cycle) cout << u << " ";
    cout << el;
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m; cin >>n >> m;
  forn(i, m){
    int u, v, w; cin >> u >> v >> w;
    g[u].pb({v, w});
  }
  for1(i, n) g[0].pb({i, 0});
  bellman_ford(0, n+1);
}