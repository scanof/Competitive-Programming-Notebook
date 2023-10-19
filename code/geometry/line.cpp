// Add point.cpp Basic operators
struct line{
  pt v;  ld c;
  line(){}
  line(pt p, pt q): v(q - p), c(v % p){}
  line(pt v, ld c): v(v), c(c){}
  line(ld a, ld b, ld c): v({b, -a}), c(c){}
  bool operator<(line l){ return v % l.v > 0; } 
  bool operator/(line l){ return v % l.v == 0; } // abs() <= eps
  pt operator^(line l){ // LINE - LINE Intersection
    if(*this / l) return pt(inf, inf);  // PARALLEL
    return (l.v*c - v*l.c) / (v % l.v); 
  }
  ld side(pt p){ return v % p - c; }
  bool has(pt p){ return v % p == c; }
  pt proj(pt p) { return p - v.perp() * side(p) / v.norm2(); }
  pt refl(pt p) { return proj(p) * 2 - p; }
  bool cmp_proj(pt p, pt q){ return v * p < v * q; }
  ld dist(pt p){ return abs(side(p)) / v.norm(); }
  ld dist2(pt p){ return side(p) * side(p) / double(v.norm2()); } 
  
  bool operator==(line l){ return *this / l && c == l.c; }
	ld angle(line l){ return v.min_angle(l.v); }   ///angle bet. 2 lines
  line perp_at(pt p) { return {p, p + v.perp() }; }
  line translate(pt t) { return {v, c + (v % t)}; }
  line shift_left(ld dist){ return {v, c + dist * v.norm()}; }
};