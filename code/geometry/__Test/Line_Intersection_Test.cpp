// https://codeforces.com/group/hzSLIARNBN/contest/465598/problem/C
#include <bits/stdc++.h>

#define forn(i,n) for(int i = 0; i < n; ++i)
#define fore(i,l,r) for(int i = l; i <= r; ++i)
#define el '\n'
#define sz(v) v.size()
#define all(v) v.begin(),v.end()
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;

const ll inf = 1e18;
const ld eps = 1e-7;

struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  bool operator<(pt p)const{ // for convex hull/set/map
		return x < p.x-eps || (abs(x-p.x) <=eps && y < p.y-eps);}
  pt operator-(pt p){return pt(x-p.x, y-p.y);}
  pt operator+(pt p){return pt(x+p.x, y+p.y);}
  pt operator*(ld t){return pt(x*t, y*t);}
  pt operator/(ld t){return pt(x/t, y/t);}
  
  ld operator*(pt p){return x*p.x + y*p.y;}
  ld operator%(pt p){return x*p.y - y*p.x;}
};

struct ln{
  pt v;  ld c;
  ln(){}
  ln(pt p, pt q): v(q-p), c(v%p){}
  bool operator<(ln l){ return v % l.v > 0; }
  bool operator/(ln l){ return v % l.v == 0; }
  pt operator^(ln l){ return (l.v*c - v*l.c) / (v % l.v); }
  bool has(pt r){return v%r == c;}
};

vector<string> names;
void fin(int idx){ cout << names[idx] << el; exit(0); }

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int r, x0, y0;  ll n;
  cin >> r >> n >> x0 >> y0;

  names.resize(r);
  vector<ln> st(r);
  forn(i, r){
    cin >> names[i];
    int x1, y1, x2, y2;   cin >> x1 >> y1 >> x2 >> y2;
    if(x1 > x2 || (x1 == x2 && y1 > y2)) swap(x1, x2), swap(y1, y2);
    st[i] = ln(pt(x1, y1), pt(x2, y2));
  }

  vector<pair<pt, int>> pts[r];
  forn(i, r){
    fore(j, i+1, r-1){
      if(st[i] / st[j]) continue;
      pt inter = st[i] ^ st[j];
      pts[i].pb({inter, j});
      pts[j].pb({inter, i});
    }
  }
  forn(i, r) sort(all(pts[i]));

  pt cur = pt(x0, y0);
  int idx = -1;
  forn(i, r) if(st[i].has(cur)) assert(idx == -1), idx = i;
  assert(idx != -1);
  
  map<pt, int> times;
  int pos = 1, ct = 0, ni;
  while(n--){
    auto it = lower_bound(all(pts[idx]), pair<pt, int>(cur, 0));
    if(pos) {
      if(ct) ++it;
      if(it == pts[idx].end()) fin(idx);
    }else {
      if(it == pts[idx].begin()) fin(idx);
      --it;
    }
    tie(cur, ni) = *it;

    if(times.count(cur)) n %= ct - times[cur];
    times[cur] = ct++;

    if(st[idx] < st[ni]) pos = 1 - pos;
    idx = ni;
  }
  fin(idx);
}