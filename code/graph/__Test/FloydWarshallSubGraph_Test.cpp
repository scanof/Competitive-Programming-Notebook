// https://codeforces.com/contest/295/problem/B
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'
#define d(x) cout << #x << " : " << x << el;


using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int N = 501;
const ll inf = 1e18;

int g[N][N];
ll dist[N][N];

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n; cin >> n;

  forn(i, n) forn(j, n) cin >> g[i][j];
  forn(i, n) forn(j, n) dist[i][j] = inf;

  vi ord(n);
  forn(i, n) {
    cin >> ord[n-1-i];
    --ord[n-i-1];
  }

  vector<ll> res(n);
  forn(i, n){
    int cur = ord[i];
    dist[cur][cur] = 0;

    forn(j, i){
      int u = ord[j];
      forn(k, i){
        int v = ord[k];
        dist[u][cur] = min(dist[u][cur], dist[u][v] + g[v][cur]);
        dist[cur][u] = min(dist[cur][u], g[cur][v] + dist[v][u]);
      }
    }

    forn(j, i){
      int u = ord[j];
      forn(k, i){
        int v = ord[k];
        dist[u][v] = min(dist[u][v], dist[u][cur] + dist[cur][v]);
      }
    }
    
    ll ans = 0;
    forn(u, n) forn(v, n) if(dist[u][v] < inf) ans += dist[u][v];
    res[n-1-i] = ans;
  }
  for(ll x: res) cout << x << " ";
  cout << el;
}