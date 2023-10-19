// https://open.kattis.com/problems/bigbrother
#include <bits/stdc++.h>

#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout<< #x<< " " << x<<el
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)

using namespace std;

typedef double ld;
const ld eps = 1e-7, inf = 1e12;
struct pt {  // for 3D add z coordinate
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator-(pt p){return pt(x - p.x, y - p.y);}
  pt operator*(ld t){return pt(x * t, y * t);}
  pt operator/(ld t){return pt(x / t, y / t);}
  ld operator%(pt p){return x * p.y - y * p.x;}
  ld operator*(pt p){return x * p.x + y * p.y;}
};

struct halfplane {
  pt p, v;  ld c, angle;
  halfplane(){}
  halfplane(pt p, pt q): p(p), v(q - p), c(v % p), angle(atan2(v.y, v.x)){}
  bool operator<(halfplane b)const{ return angle < b.angle; }
  bool operator/(halfplane l){ return abs(v % l.v) <= eps; } // 2D
  pt operator^(halfplane l){ return *this / l ? pt(inf, inf) : (l.v*c - v*l.c) / (v % l.v);}
  bool out(pt q){ return v % q < c; } // try < c-eps
};

vector<pt> intersect(vector<halfplane> b){
  vector<pt> bx = {{inf, inf}, {-inf, inf}, {-inf, -inf}, {inf, -inf}};
  forn(i, 4) b.pb(halfplane(bx[i], bx[(i+1) % 4]));
  sort(all(b));
  int n = sz(b), q = 1, h = 0;
  vector<halfplane> c(sz(b) + 10);
  forn(i, n){
    while(q < h && b[i].out(c[h] ^ c[h-1])) --h;
    while(q < h && b[i].out(c[q] ^ c[q+1])) ++q;
    c[++h] = b[i];
    if(q < h && abs(c[h].v % c[h-1].v) < eps){
      if(c[h].v * c[h-1].v <= 0) return {};
      h--;
      if(b[i].out(c[h].p)) c[h] = b[i];
    }
  }
  while(q < h-1 && c[q].out(c[h] ^ c[h-1])) --h;
  while(q < h-1 && c[h].out(c[q] ^ c[q+1])) ++q;
  if(h - q <= 1) return {};
  c[h+1] = c[q];
  vector<pt> s;
  fore(i, q, h) s.pb(c[i] ^ c[i+1]);
  return s;
}

ld area(vector<pt>& pol){
  if(sz(pol) <= 2) return 0;
  ld a = 0;
  forn(i, sz(pol)) a += pol[i] % pol[(i+1) % sz(pol)];
  return abs(a) / 2;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(8) << fixed; 
  int n; cin >> n;
  vector<pt> p(n);
  forn(i, n) cin >> p[i].x >> p[i].y;

  vector<halfplane> h(n);
  forn(i, n) h[i] = halfplane(p[(i+1) % n], p[i]);  // Input in CW order
  
  auto pol = intersect(h);
  cout << area(pol) << el;
}