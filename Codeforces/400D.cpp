// http://codeforces.com/contest/400/problem/D
#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define for1(i, n) for (int i = 1; i <= (int)n; ++i)
#define fore(i, l, r) for (int i = (int)l; i <= (int)r; ++i)
#define ford(i, n) for (int i = (int)(n)-1; i >= 0; --i)
#define fored(i, l, r) for (int i = (int)r; i >= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout << #x << " " << x << el
#define ri(n) scanf("%d", &n)
#define vec vector

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<char, int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;


const int MAXN = 1e5 + 200;

struct dsu { // 0-indexed
  vi p, r;
  int numSets;
  void init(int n) {
    p.assign(n, 0);
    r.assign(n, 1);
    numSets = n;
    forn(i, n) p[i] = i;
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    int x = findSet(i), y = findSet(j);
    if (x != y) {
      if (r[x] > r[y]) {
        p[y] = x;
        r[x] += r[y];
        r[y] = 0;
      } else {
        p[x] = y;
        r[y] += r[x];
        r[x] = 0;
      }
      numSets--;
    }
  }
};

const int INF = 1e9;
vector<ii> g[MAXN]; // g[u] = (v = nodo, w = peso)

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  int acum(0), dist[k], tipos[n];
  forn(i, k) {
    cin >> dist[i];
    forn(j, dist[i]) tipos[acum++] = i;
  }
  vec<tiii> edges;
  forn(i, m) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.pb(tiii(w, u - 1, v - 1));
  }
  sort(edges.begin(), edges.end());
  dsu uf;
  uf.init(n);
    int d[k][k];
    forn(i,k){
        forn(j,k){
            d[i][j]= INF;
        }
    }
  forn(i, m) {
    int w = get<0>(edges[i]);
    if (w == 0) {
      uf.unionSet(get<1>(edges[i]), get<2>(edges[i]));
    } else if (!uf.isSameSet(get<1>(edges[i]), get<2>(edges[i]))) {
      int u = uf.findSet(get<1>(edges[i]));
      int v = uf.findSet(get<2>(edges[i]));
      g[u].pb(ii(v, w));
      g[v].pb(ii(u, w));
    }
  }


  acum = 0;
  bool works = true;
  forn(i, k) {
    int parent = uf.findSet(acum);
    forn(j, dist[i]) {
      if (parent != uf.findSet(acum++)) {
        works = false;
        break;
      }
    }
    if (!works)
      break;
  }
  if (!works) {
    cout<<"No\n";
    return 0;
  }
  cout<< "Yes\n";

  // Complejidad nˆ3
  // Hay que saber inicializar el array d.

  // Los nodos estan numerados de 0 a n-1
    forn(i, m) {
        tiii a = edges[i];
        int w = get<0>(a);
        if (w == 0) {
            int u=tipos[get<1>(a)], v= tipos[get<2>(a)] ;
            d[u][v]= d[v][u]= 0;
        }else break;
    }
    forn(i,k){
        d[i][i]= 0;
    }
  forn(i,n)
    for(ii j: g[i]){
      int u=tipos[i], v= tipos[j.fi];
      d[u][v] = min(d[u][v],j.se);
      d[v][u] = min(d[u][v],j.se);
    }

  for(int l = 0; l < k; ++l)
    for (int i = 0; i < k; ++i)
      for (int j = 0; j < k; ++j)
        d[i][j] = min(d[i][j], d[i][l] + d[l][j]);

  forn(i, k) {
    forn(j, k) cout << (d[i][j]==INF ? -1 : d[i][j]) << " ";
    cout << el;
  }
}
