// https://open.kattis.com/problems/joiningflows
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
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

const int inf = 1e9, mod = 1e9+7, N = 1e6 + 10;
int t[10], a[10], b[10];

struct pt {  // for 3D add z coordinate
  ll x,y;
  pt(ll x, ll y):x(x),y(y){}
  pt(){}
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
  pt operator-(pt p){return pt(x-p.x,y-p.y);}
  pt operator*(ll t){return pt(x*t,y*t);}
  pt operator/(ll t){return pt(x/t,y/t);}
  ll operator*(pt p){return x*p.x+y*p.y;}
  ll operator%(pt p){return x*p.y-y*p.x;}

  bool operator<(pt p)const{ return x == p.x ? y < p.y : x < p.x;}
    
  ll side(pt p, pt q){ return (q - p) % (*this - p);}
  bool left(pt p, pt q){ return side(p, q) > 0; }
  bool in_disk(pt p, pt q){ return (p - *this) * (q - *this) <= 0; }
  bool on_seg(pt p, pt q){ return side(p, q) == 0 && in_disk(p, q); }
};
// CCW order, excludes collinear points
// Change .side(r[sz(r)-2], p[i]) > 0 to include collinear
vector<pt> chull(vector<pt>& p){ 
  if(sz(p) < 3) return p;
  vector<pt> r;
  sort(all(p));
  forn(i,sz(p)){ // lower hull
    while(sz(r) > 1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  int k = sz(r);
  fored(i, 0, sz(p)-1){ // upper hull
    while(sz(r) > k+1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  return r;
}

struct poly{
  int n, nor = -1;  vector<pt> p;
  poly(){}
  poly(vector<pt>& p):p(p), n(sz(p)){}

  void remove_col(){ // helper de has_log 
    vector<pt> s;
    forn(i, n) if(!p[i].on_seg(p[(i-1+n) % n], p[(i+1) % n])) s.pb(p[i]);
    p.swap(s);  n = sz(p);
  }
  void normalize(){  // helper de has_log 
    remove_col();
    if(p[2].left(p[0], p[1])) reverse(all(p));
    int pi = min_element(all(p)) - p.begin();
    vector<pt> s(n);
    forn(i, n) s[i] = p[(pi+i) % n];
    p.swap(s);  n = sz(p);
  }
  bool has_log(pt q){ /// O(log(n)) only CONVEX.
    if(nor == -1) nor = 1, normalize();
    if(q.left(p[0], p[1]) || q.left(p[n-1], p[0])) return false;
    int l = 1, r = n-1;    // returns true if point on boundary
    while(l+1 < r){          // (change sign of EPS in left
      int m = (l+r) / 2;       //  to return false in such case)
      if(!q.left(p[0], p[m])) l = m;
      else r = m;
    }
    return !q.left(p[l], p[l+1]);
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(10) << fixed; 
  int k;  cin >> k;
  forn(i, k) cin >> t[i] >> a[i] >>b[i];

  vector<pt> pol;
  forn(mask, 1<<k){
    ll xx=0, yy=0;
    forn(i, k){
      if(mask & (1<<i)){
        xx += a[i];
        yy += ll(a[i]) * t[i];
      } else{
        xx += b[i];
        yy += ll(b[i]) * t[i];
      }
    }
    pol.pb(pt(xx, yy));
  }
  
  pol = chull(pol);
  poly pp = poly(pol);
  pp.normalize();

  int q; cin >> q;
  forn(i, q){
    ll tt, xx; cin >> tt >> xx;
    if(k == 1){
      if(tt == t[0] && a[0] <= xx && xx <= b[0]) 
        cout << "yes" << el;
      else cout << "no" << el;
    } else{
      ll x1 = xx, t1 = tt * x1;
      if(pp.has_log(pt(x1, t1))) cout << "yes" << el;
      else cout << "no" << el;
    }
  }
}