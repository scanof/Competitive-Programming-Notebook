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