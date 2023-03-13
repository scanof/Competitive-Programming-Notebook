struct pt {  // for 3D add z coordinate
	ld x,y;
	pt(){}
	pt(ld x, ld y):x(x),y(y){}
  
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	pt unit(){return *this/norm();}
	
  bool operator==(pt p){return abs(x-p.x)<=eps && abs(y-p.y)<=eps;}
	bool operator!=(pt p){ return !operator==(p);}
	bool operator<(pt p)const{ // for convex hull/set/map
		return x<p.x-eps||(abs(x-p.x)<=eps&&y<p.y-eps);
  }
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ld t){return pt(x*t,y*t);}
	pt operator/(ld t){return pt(x/t,y/t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
	ld operator%(pt p){return x*p.y-y*p.x;}
	ld angle(pt p){ ///[0, pi]
		ld co = *this*p/(norm()*p.norm());
		return acos(max(-1.0L, min(1.0L, co)));
  }
	bool left(pt p, pt q){  // is it to the left of directed line pq?
		return (q-p)%(*this-p)>eps; // (> -eps to return 1 when collinear)
  }
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(ld a){return rot(pt(sin(a),cos(a)));}
	pt rotp(ld a, pt p){  // Rotate "this" pt around "p", "a" radians
    pt aux = (*this - p).rot(a);
    return aux + p;
  }
};
pt ccw90(1,0), cw90(-1,0);
// C: >0 left, ==0 on AB, <0 right
ld orient(pt a, pt b, pt c){  return (b-a)%(c-a);}
// ANGLES
ld small_ang(pt p, pt q){   ///[0, pi] ([0, 180])
  ld co = (p*q) / (p.norm()*q.norm());
  return acos(max(-1.0L, min(co, 1.0L)));
}
ld ang_CW(pt a, pt b, pt c){ ///Vertex = B,  from BA -> BC (CW)
  if(orient(a,b,c) >= 0) return small_ang(a-b, c-b);
  return 2*pi - small_ang(a-b, c-b);
}
ld ang_CCW(pt a, pt b, pt c){ ///Vertex = B,  from BA -> BC (CCW)
  if(orient(a,b,c) <= 0) return small_ang(a-b, c-b);
  return 2*pi - small_ang(a-b, c-b);
}
///is P inside ang ABC (CW)
bool in_ang_CW(pt a, pt b, pt c, pt p){ return ang_CW(a, b, p) <= ang_CW(a, b, c);}
///is P inside ang ABC (CCW)
bool in_ang_CCW(pt a, pt b, pt c, pt p){ return ang_CCW(a, b, p) <= ang_CCW(a, b, c);}