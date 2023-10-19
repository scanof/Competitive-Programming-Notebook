// https://szkopul.edu.pl/problemset/problem/p73RF9garyZ3keuGDIdyomLv/site/?key=statement
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
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ll;
typedef double ld;

const ld inf = 1e18, pi = acos(-1), eps = 1e-8;

struct pt {  // for 3D add z coordinate
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}     
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
	pt operator-(pt p){ return pt(x-p.x, y-p.y); }
	pt operator*(ld t){ return pt(x*t, y*t); }
	pt operator/(ld t){ return pt(x/t, y/t); }
	ld operator*(pt p){ return x*p.x + y*p.y; }
	ld operator%(pt p){ return x*p.y - y*p.x; }

  ld norm2(){ return *this**this; }
	ld norm(){ return sqrt(norm2()); }
	ld min_angle(pt p){ return acos(*this*p / (norm()*p.norm())); }
	pt rot(pt p){ return pt(*this % p,*this * p); }// pt ccw90(1,0), cw90(-1,0)
  int cuad(){
    if(x > 0 && y >= 0) return 0;
    if(x <= 0 && y > 0) return 1;
    if(x < 0 && y <= 0) return 2;
    if(x >= 0 && y < 0) return 3;
    return -1; // x == 0 && y == 0
  }
};
bool cmp(pt p1, pt p2){ // Around Origin(0, 0):  -->  sort(all(pts), cmp); 
  int c1 = p1.cuad(), c2 = p2.cuad();
  return c1 == c2 ? p1.y*p2.x < p1.x*p2.y : c1 < c2; 
} 

const pt ccw90(1,0), cw90(-1,0);
struct circle {
	pt o;  ld r;
  circle(){}
	circle(pt o, ld r): o(o), r(r){}
	inline bool in(circle c){ return (o - c.o).norm() + r <= c.r + eps; }// non strict
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		ld d = (o - c.o).norm();
		if(d > r + c.r + eps || d + min(r, c.r) + eps < max(r, c.r)) return s;
		ld x = (d*d - c.r*c.r + r*r) / (2*d), y = sqrt(r*r - x*x);
		pt v = (c.o - o) / d;
		s.pb(o + v*x - v.rot(ccw90)*y);
		if(y > eps) s.pb(o + v*x + v.rot(ccw90)*y);
		return s;
	}
};

vector<ld> intercircles(vector<circle> c){
	vector<ld> r(sz(c) + 1); // r[k]: area covered by at least k circles
	forn(i, sz(c)){           // O(n^2 log n) (high constant)
		int k = 1;  pt O = c[i].o;
		vector<pair<pt, int>> p = {
			{c[i].o + pt(1,0) * c[i].r, 0},
			{c[i].o - pt(1,0) * c[i].r, 0}};
		forn(j, sz(c)) if(j != i){
			bool b0 = c[i].in(c[j]), b1 = c[j].in(c[i]);
			if(b0 && (!b1 || i < j)) ++k;
			else if(!b0 && !b1){
				auto v = c[i] ^ c[j];
				if(sz(v) == 2){
					p.pb({v[0], 1});  p.pb({v[1], -1});
					if(cmp(v[1] - O, v[0] - O)) ++k;
				}
			}
		}
		sort(all(p), [&](auto& a, auto& b){ return cmp(a.fi - O, b.fi - O); });
		forn(j, sz(p)){
			pt p0 = p[j ? j-1 : sz(p)-1].fi, p1 = p[j].fi;
			ld a = (p0 - c[i].o).min_angle(p1 - c[i].o);
			r[k] += (p0.x - p1.x)*(p0.y + p1.y)/2 + c[i].r*c[i].r*(a - sin(a))/2;
			k += p[j].se;
		}
	}
	return r;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout<< setprecision(20)<< fixed;
  int n, k;  ld r, x, y;
  cin >> n >> k >> r;
  vector<circle> c(n);
  forn(i, n){
    cin >> x >> y;
    c[i] =  circle(pt(x, y), r);
  }

  vector<ld> v = intercircles(c);
  ld ans = 0;
  for1(i, sz(v)-1){
    if(i < sz(v)-1) v[i] -= v[i+1];
    ld p = 1 - pow(1 - 1.*i/n, k);
    ans += p * v[i];
  }
  cout << ans << el;
}