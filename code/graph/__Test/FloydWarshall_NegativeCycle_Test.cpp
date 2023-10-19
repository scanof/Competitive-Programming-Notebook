// https://open.kattis.com/problems/allpairspath
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define d(x) cout << #x << " : " << x << el;
#define el '\n'

using namespace std;

const int N = 151, Q = 1001, inf = 1e9;
int d[N][N];

void negative_floyd(int n){
  forn(k, n) 
    forn(u, n)
      forn(v, n) // IF: U -> K and K -> V (reachable)
        if(d[u][k] < inf && d[k][v] < inf)  
          d[u][v] = min(d[u][v], d[u][k] + d[k][v]);

  forn(u, n)
    forn(v, n)
      forn(k, n)  // IF: K is in negative cycle, (U -> K and K -> V)
        if(d[u][k] < inf && d[k][k] < 0 && d[k][v] < inf) 
          d[u][v] = -inf;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m, q; 
  while(cin >> n >> m >> q && (n+m+q)){
    forn(i, n) forn(j, n) d[i][j] = i == j ? 0 : inf;
    forn(i, m){
      int u, v, w; cin >>u >> v >> w;
      d[u][v] = min(d[u][v], w);
    }
    negative_floyd(n);
    
    forn(i, q){
      int u, v; cin >>u >> v;
      if(d[u][v] == inf) cout << "Impossible" << el;
      else if(d[u][v] == -inf) cout << "-Infinity" << el;
      else cout << d[u][v] << el;
    }
    cout << el;
  }
}