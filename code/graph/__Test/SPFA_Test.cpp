// https://cses.fi/problemset/task/1197/
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define d(x) cout << #x << " : " << x << el;
#define all(v) v.begin(),v.end()
#define el '\n'
#define sz(v) int(v.size())
#define pb push_back


using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef long long ll;

const int N = 2501;
const ll inf = 1e18;

vector<ii> g[N];
ll dist[N];
int pa[N], cnt[N];
bool in_q[N];
void spfa(int s, int n){
  forn(i, n) dist[i] = (i == s ? 0 : inf);
  queue<int> q({s});  in_q[s] = 1;
  int start = -1;
  while(sz(q) && start == -1) {
    int u = q.front();  q.pop();
    in_q[u] = false;
    for(auto& [v, w] : g[u]){
      if(dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pa[v] = u;
        if(!in_q[v]) {
          q.push(v);
          in_q[v] = 1;
          ++cnt[v];
          if(cnt[v] > n){ start = v;  break; }
        }
      }
    }
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
  spfa(0, n+1);
}