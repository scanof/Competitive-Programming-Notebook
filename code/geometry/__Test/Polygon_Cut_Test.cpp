// http://codeforces.com/problemset/problem/280/A
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define forn(i,n) for(int i=0; i<n; ++i)
#define sz(v) int(v.size())

typedef double ld;
typedef long long ll;
const double DINF = 1e20, eps = 1e-7, pi = acos(-1);

struct pt{
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}
	pt(ld ang): x(cos(ang)), y(sin(ang)){}  // Polar unit point: ang(randians)
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
	pt operator-(pt p){ return pt(x-p.x, y-p.y); }
	ld operator*(pt p){ return x*p.x + y*p.y; }
	ld operator%(pt p){ return x*p.y - y*p.x; }
  pt rot(pt p){ return pt(*this % p,*this * p); }// use ccw90(1,0), cw90(-1,0)
	pt rot(ld ang){ return rot(pt(sin(ang), cos(ang))); } // CCW, ang (radians)
};

struct line{
  pt v;  ld c;
  line(){}
  line(pt p, pt q): v(q - p), c(v % p){}
  bool operator/(line l){ return v % l.v == 0; } 
  pt operator^(line l){ return (l.v*c - v*l.c) / (v % l.v); }
  ld side(pt p){ return v % p - c; }
};

inline int sgn(ld x){ return x <- eps ? -1 : x > eps; }
struct poly {
	int n; vector<pt> p;
	poly(){}
	poly(vector<pt>& p):p(p), n(sz(p)){}
	ld area(){
		ld r = 0;
		forn(i, n) r += p[i] % p[(i+1)%n];
		return abs(r) / 2; // negative if CW, positive if CCW
	}
	poly cut(line l){   // cut CONVEX polygon by line l
		vector<pt> q;  // returns part at left of l.pq
		forn(i, n) {
			int d0 = sgn(l.side(p[i])), d1 = sgn(l.side(p[(i+1) % n]));
			if(d0 >= 0) q.pb(p[i]);
			line m(p[i], p[(i+1) % n]);
			if(d0*d1 < 0 && !(l / m)) q.pb(l ^ m);
		}
		return poly(q);
	}
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);  cout.tie(0);
  cout << setprecision(8) << fixed;
	ld w, h, a; cin >> w >> h >> a;
	a *= pi/180;
	vector<pt> q, p{
    {w/2, h/2}, {-w/2, h/2}, {-w/2, -h/2}, {w/2,-h/2}
  };
	forn(i, 4) q.pb(p[i].rot(a));
	poly pol(p);
	forn(i, 4) pol = pol.cut(line(q[i], q[(i+1)%4]));
	cout << pol.area() << endl;
}