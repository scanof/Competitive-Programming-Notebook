struct pt {  // for 3D add z coordinate
	ld x,y;
	pt(ld x, ld y):x(x),y(y){}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<=eps&&abs(y-p.y)<=eps;}
	bool operator!=(pt p){ return !operator==(p);}
	bool operator<(pt p)const{ // for convex hull/set/map
		return x<p.x-eps||(abs(x-p.x)<=eps&&y<p.y-eps);}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ld t){return pt(x*t,y*t);}
	pt operator/(ld t){return pt(x/t,y/t);}
	///DOT
	ld operator*(pt p){return x*p.x+y*p.y;}
//	pt operator%(pt p){ // 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	ld angle(pt p){ ///[0, pi]
		ld co = *this*p/(norm()*p.norm());
		return acos(max(-1.0L, min(1.0L, co)));
  }
	pt unit(){return *this/norm();}
	ld operator%(pt p){return x*p.y-y*p.x;}
	/// 2D from now on
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>eps;
  }
	int left_int(pt p, pt q){ // is it to the left of directed line pq?
		ld cro = (q-p)%(*this-p);
		if(cro < eps)
      return -1;
		else
      return (abs(cro) <= eps ? 0 : 1);
  }
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(ld a){return rot(pt(sin(a),cos(a)));}
	pt rotp(ld a, pt p){
    pt aux = (*this - p).rot(a);
    return aux + p;
  }
};

pt ccw90(1,0), cw90(-1,0);

int sgn(ld x){
  if(x<0)
    return -1;
  else if(abs(x) <= eps)
    return 0;
  else
    return 1;
}

//pt zero = pt(0,0,0); //for 3D

ld orient(pt a, pt b, pt c){  ///C: >0 left, ==0 on AB, <0 right
  return (b-a)%(c-a);
}

ld small_angle(pt p, pt q){   ///[0, pi] ([0, 180])
  return acos(max(-1.0L, min((p*q)/(p.norm()*q.norm()), 1.0L)));
}

ld dir_ang_CW(pt a, pt b, pt c){ ///Vertex = B,  from BA -> BC (CW)
  if(orient(a,b,c) >= 0){
    return small_angle(a-b, c-b);
  } else{
    return 2*pi - small_angle(a-b, c-b);
  }
}

ld dir_ang_CCW(pt a, pt b, pt c){ ///Vertex = B,  from BA -> BC (CCW)
  if(orient(a,b,c) <= 0){
    return small_angle(a-b, c-b);
  } else{
    return 2*pi - small_angle(a-b, c-b);
  }
}

bool in_angle_CW(pt a, pt b, pt c, pt p){    ///is P inside ang(ABC) CW
  return dir_ang_CW(a, b, p) <= dir_ang_CW(a, b, c);
}

bool in_angle_CCW(pt a, pt b, pt c, pt p){    ///is P inside ang(ABC) CW
  return dir_ang_CCW(a, b, p) <= dir_ang_CCW(a, b, c);
}

///3D - ORIENT
ld orient(pt p, pt q, pt r, pt s){  return (q-p)%(r-p)|(s-p);}
bool coplanar(pt p, pt q, pt r, pt s){
  return abs(orient(p, q, r, s)) < eps;
}
bool skew(pt p, pt q, pt r, pt s){        ///skew := neither intersecting/parallel
  return abs(orient(p, q, r, s)) > eps;   ///lines: PQ, RS
}
ld orient_norm(pt p, pt q, pt r, pt n){   ///n := normal to a given plane PI
  return (q-p)%(r-p)|n;/// equivalent to 2D cross on PI (of ortogonal proj)
}
