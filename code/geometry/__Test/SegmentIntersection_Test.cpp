// https://codeforces.com/problemset/problem/793/C
#include <bits/stdc++.h>

#define el '\n'
#define d(x) cout << #x << ": " << x << el;
#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define sz(v) int(v.size())
#define pb push_back

using namespace std;

typedef double ld;
const int N = 1e5+10, mod = 1e9+7;
struct pt{
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}
  
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
	pt operator-(pt p){ return pt(x-p.x, y-p.y); }
	pt operator*(ld t){ return pt(x*t, y*t); }
	pt operator/(ld t){ return pt(x/t, y/t); }
	ld operator*(pt p){ return x*p.x + y*p.y; }
	ld operator%(pt p){ return x*p.y - y*p.x; }

  ld side(pt p, pt q){ return (q - p) % (*this - p);}
  bool in_disk(pt p, pt q){ return (p - *this) * (q - *this) <= 0; }
  bool on_segment(pt p, pt q){ return side(p, q) == 0 && in_disk(p, q); }
};

void segment_intersection(pt a, pt b, pt c, pt d, vector<pt>& out){ // AB y CD
  ld sa = a.side(c, d), sb = b.side(c, d);
  ld sc = c.side(a, b), sd = d.side(a, b);
  if(sa*sb < 0 && sc*sd < 0) out.pb((a*sb - b*sa) / (sb-sa)); // proper cut
  for(pt p : {c, d}) if(p.on_segment(a, b)) out.pb(p);
  for(pt p : {a, b}) if(p.on_segment(c, d)) out.pb(p);
}

pt pts[N], v[N];
void fin(){ cout << -1 << el; exit(0); }

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << setprecision(12) << fixed;
  
  int n; ld x1, x2, y1, y2;
  cin >> n >> x1 >> y1 >> x2 >> y2;
  vector<pt> es{ {x1, y1}, {x1, y2}, {x2, y2}, {x2, y1} };
  
  forn(i, n){
    int xx, yy; cin >> xx >> yy;
    pts[i] = pt(xx, yy);
    cin >> xx >> yy;
    v[i] = pt(xx, yy);
  }

  ld l = 0, r = 1e12;
  forn(i, n){
    set<ld> tim;
    if(x1 < pts[i].x && pts[i].x < x2 && y1 < pts[i].y && pts[i].y < y2){
      tim.insert(0);
      if(v[i].x == 0 && v[i].y == 0) tim.insert(r);
    }
    if((pts[i].x == x1 || pts[i].x == x2) && v[i].x == 0) fin();
    if((pts[i].y == y1 || pts[i].y == y2) && v[i].y == 0) fin();

    if(abs(v[i].x) > 0 || abs(v[i].y) > 0){
      pt a = pts[i], b = pts[i] + (v[i] * 1e7);
      forn(j, 4){
        vector<pt> out;
        segment_intersection(a, b, es[j], es[(j+1)%4], out);
        for(auto& o: out){
          if(v[i].x != 0) tim.insert(abs(a.x - o.x) / abs(v[i].x));
          else tim.insert(abs(a.y - o.y) / abs(v[i].y));
        }
      }
    }
    assert(sz(tim) <= 2);
    if(!sz(tim)) fin();
    l = max(l, *tim.begin()), r = min(r, *tim.rbegin());
  }
  if(l >= r) cout << -1 << el;
  else cout << l << el;
} 