struct p3{
  ld x, y, z;
  p3() {}
  p3 (ld x, ld y, ld z):x(x), y(y), z(z){}

  p3 operator*(ld f){ return p3(x*f, y*f, z*f);}
  p3 operator/(ld f){ return p3(x/f, y/f, z/f);}
  p3 operator-(p3 p){ return p3(x-p.x, y-p.y, z-p.z);}
  p3 operator+(p3 p){ return p3(x+p.x, y+p.y, z+p.z);}
  p3 operator%(p3 p){ return p3(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);}    /// (|p||q|sin(ang))* normal
  ld operator|(p3 p){ return x*p.x + y*p.y + z*p.z;}
  
  bool operator==(p3 p){ return tie(x,y,z) == tie(p.x,p.y,p.z);}
  bool operator!=(p3 p){ return !operator==(p);}
  bool operator<(p3 p){ return tie(x,y,z) < tie(p.x,p.y,p.z);}
};
p3 zero = p3(0,0,0);
int sgn(ld x){ return (0 < x) - (x < 0);}

///BASICS
ld sq(p3 p){  return p|p;}
ld abs(p3 p){ return sqrt(sq(p));}
p3 unit(p3 p) { return p/abs(p);}
///ANGLES
ld ang(p3 p, p3 q){         ///[0, pi]
  ld co = (p|q)/abs(p)/abs(q);
  return acos(max(-1.0, min(1.0, co)));
}
ld small_ang(p3 p, p3 q){   ///[0, pi/2]
  ld co = abs(p|q)/abs(p)/abs(q);
  return acos(min(co, 1.0))
}
///3D - ORIENT
ld orient(p3 p, p3 q, p3 r, p3 s){  return (q-p)%(r-p)|(s-p);}
bool coplanar(p3 p, p3 q, p3 r, p3 s){
  return abs(orient(p, q, r, s)) < eps;
}
bool skew(p3 p, p3 q, p3 r, p3 s){        ///skew := neither intersecting/parallel
  return abs(orient(p, q, r, s)) > eps;   ///lines: PQ, RS
}
ld orient_norm(p3 p, p3 q, p3 r, p3 n){   ///n := normal to a given plane PI
  return (q-p)%(r-p)|n;/// equivalent to 2D cross on PI (of ortogonal proj)
}