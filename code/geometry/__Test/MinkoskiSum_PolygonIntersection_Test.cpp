// https://codeforces.com/gym/101889/attachments (A)
#include <bits/stdc++.h>

#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout<< #x<< " " << x<<el
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

const ld pi = acos(-1), eps = 1e-7;
const int inf = 1e9, mod = 1e9+7, N = 14;

struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator+(pt p){return pt(x + p.x, y + p.y);}
  pt operator-(pt p){return pt(x - p.x, y - p.y);}
  ld operator%(pt p){return x * p.y - y * p.x;}
  ld side(pt p, pt q){return (q - p) % (*this - p);}
};

struct mink_sum{
  vector<pt> p, q, pol;
  mink_sum(){}
  mink_sum(vector<pt>& p1, vector<pt>& p2, bool inter = 1): p(p1), q(p2){
    if(inter) for(auto& [x, y] : q) x = -x, y = -y;
    pol.reserve(sz(p) + sz(q));
    reorder(p),  reorder(q);
    forn(i, 2) p.pb(p[i]), q.pb(q[i]);
	  int i = 0, j = 0;
    while(i+2 < sz(p) || j+2 < sz(q)){
      pol.pb(p[i] + q[j]);
      auto cro = (p[i+1] - p[i]) % (q[j+1] - q[j]);
      i += cro >= -eps;
      j += cro <= eps;
    }
  }
  void reorder(vector<pt> &p){
    if(p[2].side(p[0], p[1]) < 0) reverse(all(p));
    int pos = 0;
    forn(i, sz(p)) if(ii{p[i].y, p[i].x} < ii{p[pos].y, p[pos].x}) pos = i;
    rotate(p.begin(), p.begin() + pos, p.end());
  }
  bool has(pt p){
    int cnt = 0;
    forn(i, sz(pol)) cnt += p.side(pol[i], pol[(i+1) % sz(pol)]) >= 0;
    return cnt == sz(pol);
  }
  bool intersect(pt shift = pt(0, 0)){ return has(shift); }
};  // Do polygons p1 and p2+shift intersect?

ld dist[N][N];
int L[N], R[N];
vector<pt> pts[N];

ld calc(int i, int j){
  if(i == j) return 0;
  auto mink = mink_sum(pts[i], pts[j]);
  ld l = 0, r = 2e8 + 10;
  while(l + eps < r){
    ld m = (l + r) / 2;
    if(mink.intersect(pt(m, 0))) l = m; 
    else r = m;
  }
  return r;
}

ld dp[1 << N][N];
int all_mask, n;

ld go(int mask, int cur){
  if(mask == all_mask) return R[cur];
  ld &r = dp[mask][cur];
  if(r > -0.5) return r;
  r = 1e12;
  forn(i, n){
    if(mask & (1 << i)) continue;
    r = min(r, dist[cur][i] + go(mask | (1 << i), i));
  }
  return r;
} 

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(3) << fixed; 
  cin >> n;
  all_mask = (1 << n) - 1; 

  forn(i, n){
    int k; cin >> k;
    pts[i].resize(k);
    forn(j, k){
      int x, y; cin >> x >> y;
      pts[i][j] = pt(x, y);
      L[i] = max(L[i], -x);
      R[i] = max(R[i], x);
    }
  }

  forn(i, n) forn(j, n) dist[i][j] = calc(i, j);
  
  ld ans = 1e12;
  memset(dp, -1, sizeof dp);
  forn(i, n) ans = min(ans, L[i] + go(1 << i, i));
  cout << ans << el;
}