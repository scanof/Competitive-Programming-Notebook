int sgn2(ld x){return x<0?-1:1;}
struct ln {
	pt p, pq; //POINT + DIRECTION
	ln(pt p, pt q) : p(p), pq(q-p){}
	ln(ld a, ld b, ld c) : p(b == 0 ? pt(-c/a, 0) : pt(0, -c/b)), pq(pt(b, -a)){} ///ax + by + c = 0
	ln(){}
	bool has(pt r){return dist(r)<=eps;} ///check if point belongs
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))<=eps;} ///check if point belongs to segment PQ
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<=eps;} // 3D
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<=eps;} /// PARALLEL CHECK
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ /// intersection ln-ln
		if(*this/l) return pt(inf,inf);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
		return r;
	}
	ld angle(ln l){return pq.angle(l.pq);}   ///angle bet. 2 lines
	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} /// 1=L, 0= on, -1=R
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt refl(pt r){return proj(r)*2-r;}
	ld dist(pt r){return (r-proj(r)).norm();}
	ld dist2(pt r){return (r - proj(r)).norm2();}
//	ls dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
	ln rot(auto a){return ln(p,p+pq.rot(a));} /// 2D respecto a P
  ln perp_at(pt r){return ln(r, r+pq.rot(ccw90));}
  bool cmp_proj(pt r, pt s){return pq*r<pq*s;}
  int cmp_int(pt r, pt s){
    if(pq*r < pq*s)
      return -1;
    else
      return (pq*r == pq*s ? 0 : 1);
  }
  ln trans(pt d){ return ln(p + d, pq);}    ///d = dir. vec
};

ln bisec(ln l, ln m){ /// angle bisector
	pt p=l^m;
	return ln(p, p+l.pq.unit()+m.pq.unit());
}
ln bisec(pt p, pt q){ /// segment bisector (2D) (mediatriz)
	return ln((p+q)*.5,p).rot(ccw90);
}

///Segments
bool in_disk(pt a, pt b, pt p){return (a-p)*(b-p) <= 0;}
bool on_seg(pt a, pt b, pt p){ return orient(a,b,p) == 0 && in_disk(a,b,p);}
bool proper_inter(pt a, pt b, pt c, pt d, pt &out){
  ld oa = orient(c,d,a),
     ob = orient(c,d,b),
     oc = orient(a,b,c),
     od = orient(a,b,d);
  if(oa*ob<0 && oc*od<0){
    out = (a*ob - b*oa) / (ob-oa);
    return true;
  }
  return false;
}
struct cmpX {
  bool operator()(pt a, pt b){
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }
};

set<pt,cmpX> seg_inter(pt a, pt b, pt c, pt d){ ///AB, CD
  pt out;
  if(proper_inter(a,b,c,d,out)) return {out};
  set<pt,cmpX> s;
  if(on_seg(c,d,a)) s.insert(a);
  if(on_seg(c,d,b)) s.insert(b);
  if(on_seg(a,b,c)) s.insert(c);
  if(on_seg(a,b,d)) s.insert(d);
  return s;
}

ld seg_pt(pt a, pt b, pt p){  ///DISTANTCE FROM P -> SEG. AB
  if(a!=b){
    ln l(a,b);
    /// a <= proj(p) && proj(p) <= b
    if(l.cmp_proj(a,p) && l.cmp_proj(p,b)) return l.dist(p);
  }
  return min((p-a).norm(), (p-b).norm());
}

ld seg_seg(pt a, pt b, pt c, pt d){  ///DISTANCE FROM SEG. AB -> SEG. CD
  pt aux;
  if(proper_inter(a,b,c,d,aux)) return 0;
  return min({seg_pt(a,b,c),seg_pt(a,b,d),seg_pt(c,d,a), seg_pt(c,d,b)});
}

//ld dist(ln l1, ln3 l2){      ///for 3D
//  p3 n = l1.d%l2.d;
//  if(n == zero){  ///parallel
//    return l1.dist(l2.o);
//  }
//  return abs((l2.o - l1.o)|n)/abs(n);
//}

///AGREGAR COMO ENCONTRAR LOS PUNTOS
