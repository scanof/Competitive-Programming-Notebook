// https://matcomgrader.com/problem/9598/colors-ii/
#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ld;
typedef vector<int> vi;
const ld pi = acos(-1), eps = 0;
const int inf = 1e9, mod = 998244353;

struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
  pt operator-(pt p){ return pt(x-p.x, y-p.y); }
  pt operator*(ld t){ return pt(x*t, y*t); }
  ld operator*(pt p){ return x*p.x + y*p.y; }
  ld operator%(pt p){ return x*p.y - y*p.x; }
  bool operator<(pt p){ return x == p.x ? y < p.y : x < p.x; }
  ld norm2(){ return *this * *this; }
  ld side(pt p, pt q){return (q - p) % (*this - p);}
};

vector<pt> chull(vector<pt>& p){ 
  if(sz(p) < 3) return p;
  vector<pt> r;
  sort(all(p));  // first x, then y
  forn(i,sz(p)){ // lower huld
    while(sz(r) > 1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  int k = sz(r);
  fored(i, 0, sz(p)-1){ // upper huld
    while(sz(r) > k+1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  return r;
}

ld rot_cal(vector<pt>& a, vector<pt>& b){
  pair<ld, int> start = {-1, -1};
  if(sz(a) == 1) swap(a, b);

  forn(i, sz(a)) start = max(start, {(b[0] - a[i]).norm2(), i});
  if(sz(b) == 1) return start.fi;

  ld r = 0;
  for(int i = 0, j = start.se; i < sz(b); ++i){
    for(;; j = (j+1) % sz(a)){
      r = max(r, (b[i] - a[j]).norm2());
      if((b[(i+1) % sz(b)] - b[i]) % (a[(j+1) % sz(a)] - a[j]) <= eps) break;
    }
  }
  return r;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  int n; cin >> n;
  vector<pt> p(n);
  vi col(n);
  forn(i, n) cin >> p[i].x >> p[i].y >> col[i];

  ld ans = 0;
  vector<pt> a, b;
  int m = log2(n) + 2;
  forn(j, m){
    a.clear();  b.clear();
    forn(i, n){
      if(col[i] & (1 << j)) a.pb(p[i]);
      else b.pb(p[i]);
    }
    if(sz(a) == 0 || sz(b) == 0) continue;
    auto ca = chull(a), cb = chull(b);
    ans = max(ans, rot_cal(ca, cb));
  }
  cout << ans << el;
}