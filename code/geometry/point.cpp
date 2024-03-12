struct pt{
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}
	pt(ld ang): x(cos(ang)), y(sin(ang)){}  // Polar unit point: ang(randians)
  // ------- BASIC OPERATORS -------  //        
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
	pt operator-(pt p){ return pt(x-p.x, y-p.y); }
	pt operator*(ld t){ return pt(x*t, y*t); }
	pt operator/(ld t){ return pt(x/t, y/t); }
	ld operator*(pt p){ return x*p.x + y*p.y; }
	ld operator%(pt p){ return x*p.y - y*p.x; }
  // ------- COMPARISON OPERATORS -------  // 
  bool operator==(pt p){ return abs(x - p.x) <= eps && abs(y - p.y) <= eps; }
	bool operator<(pt p)const{ // for sort, convex hull/set/map
		return x < p.x - eps || (abs(x - p.x) <= eps && y < p.y - eps); }
	bool operator!=(pt p){ return !operator==(p); }
  // -------------- NORMS --------------  // 
	ld norm2(){ return *this**this; }
	ld norm(){ return sqrt(norm2()); }
	pt unit(){ return *this/norm(); }
	// ------------ SIDE, LEFT------------ //
  ld side(pt p, pt q){ return (q-p) % (*this-p); }// C is: >0 L, ==0 on AB, <0 R
	bool left(pt p, pt q){ // Left of directed line PQ? (eps == 0 if integer)
		return side(p, q) > eps; } // (change to >= -eps to accept collinear)
  // -------------- ANGLES -------------- //
  ld angle(){ return atan2(y, x); } // Angle from origin, in [-pi, pi]
  ld min_angle(pt p){ return acos(*this*p / (norm()*p.norm())); } // In [0, pi]
  ld angle(pt a, pt b, bool CW){ // Angle< AB(*this) > in direction CW
    ld ma = (a - b).min_angle(*this - b);
    return side(a, b) * (CW ? -1 : 1) <= 0 ? ma : 2*pi - ma; }
  bool in_angle(pt a, pt b, pt c, bool CW=1){ // Is pt inside infinite angle ABC 
    return angle(a, b, CW) <= c.angle(a, b, CW); } // From AB to AC in CW direction
  // -------------- ROTATIONS -------------- //
	pt rot(pt p){ return pt(*this % p,*this * p); }// use ccw90(1,0), cw90(-1,0)
	pt rot(ld ang){ return rot(pt(sin(ang), cos(ang))); } // CCW, ang (radians)
	pt rot_around(ld ang, pt p){ return p + (*this - p).rot(ang); }
  pt perp(){ return rot(pt(1, 0)); }
  // -------------- SEGMENTS -------------- //
  bool in_disk(pt p, pt q){ return (p - *this) * (q - *this) <= 0; }
  bool on_segment(pt p, pt q){ return side(p, q) == 0 && in_disk(p, q); }
};
int sgn(ld x){
  if(x < 0) return -1;
  return x == 0 ? 0 : 1;
}
void segment_intersection(pt a, pt b, pt c, pt d, vector<pt>& out){ // AB y CD
  ld sa = a.side(c, d), sb = b.side(c, d);
  ld sc = c.side(a, b), sd = d.side(a, b);            // proper cut
  if(sgn(sa)*sgn(sb) < 0 && sgn(sc)*sgn(sd) < 0) out.pb((a*sb - b*sa) / (sb-sa)); 
  for(pt p : {c, d}) if(p.on_segment(a, b)) out.pb(p);
  for(pt p : {a, b}) if(p.on_segment(c, d)) out.pb(p);
}
