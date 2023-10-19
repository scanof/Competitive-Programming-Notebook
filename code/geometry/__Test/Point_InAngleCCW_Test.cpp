// https://codeforces.com/problemset/gymProblem/102028/D
#include <bits/stdc++.h>

#define fi first
#define se second
#define el '\n'
#define pb push_back
#define forn(i,n) for(int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()
#define d(x) cout << #x << " " << x << el;

using namespace std;

typedef double ld;
const ld pi = acos(-1), inf = 1000000000;
struct pt {  
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}
	pt operator+(pt p){return pt(x+p.x, y+p.y);}
	pt operator-(pt p){return pt(x-p.x, y-p.y);}
	pt operator*(ld t){return pt(x*t, y*t);}
	pt operator/(ld t){return pt(x/t, y/t);}
	
	ld norm2(){return *this * *this;}
	ld norm(){return sqrt(norm2());}
	ld operator*(pt p){return x*p.x + y*p.y;}
	ld operator%(pt p){return x*p.y - y*p.x;}
  // C is: >0 on L, ==0 on AB, <0 on R
  ld side(pt p, pt q){ return (q-p) % (*this-p); }
  pt rotate(pt r){return pt(*this % r, *this * r);}
	pt rotate(ld a){return rotate(pt(sin(a), cos(a)));}
  // In interval [0, pi]
  ld min_angle(pt p){ return acos(*this*p / (norm()*p.norm())); }
  ld angle(pt a, pt b, bool CW){ // Angle< AB(*this) > in direction CW
    ld ma = (a - b).min_angle(*this - b);
    return side(a, b) * (CW ? -1 : 1) <= 0 ? ma : 2*pi - ma;
  }
  bool in_angle(pt a, pt b, pt c, bool CW=0){ 
    return angle(a, b, CW) <= c.angle(a, b, CW);}
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(20)<< fixed;
  int t; cin >> t;
  while(t--){
    int a, b, w, r, d; cin >> a>>b>>r>>d;
    ld dd = d * pi / 180;
    
    pt c(0, 0), c1(1000, 0), c2 = c1.rotate(dd);
    pt pta = pt(r+a, 0).rotate(dd);
    pt ptb = pta + pt(b, 0).rotate(dd - pi/2);
    
    ld ans = ptb.in_angle(c1, c, c2) ? (ptb - c).norm() - r : abs(ptb.x - r);
    cout << ans <<el;
  }
}