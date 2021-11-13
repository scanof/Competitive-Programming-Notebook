struct ln3{   ///Remove "3" if not 2D needed
  p3 d, o;    ///direction, origin
  ln3(){}
  ln3(p3 p, p3 q) : d(q-p), o(p){}    ///given 2 points
  ln3(plane p1, plane p2){            ///given 2 planes
    d = p1.n%p2.n;
    o = (p2.n%p1.d - p1.n%p2.d)%d/sq(d);
  }
  ld sq_dist(p3 p){ return sq(d%(p-o)/sq(d));}
  ld dist(p3 p){ return sqrt(sq_dist(p));}
  bool cmp_proj(p3 p1, p3 p2){ return (d|p1) < (d|p2);}
  int cmp(p3 p, p3 q){
    if((d|p) < (d|q)){
      return -1;
    } else if((d|p) == (d|q)){
      return 0;
    } else{
      return 1;
    }
  }
  p3 proj(p3 p){ return o + d*(d|(p-o))/sq(d);}
  p3 refl(p3 p){ return proj(p)*2 - p;}
  p3 inter(plane p){ return o - d*p.side(o)/(d|p.n);}
};

///LN3 - LN3
ld dist(ln3 l1, ln3 l2){
  p3 n = l1.d%l2.d;
  if(n == zero){  ///parallel
    return l1.dist(l2.o);
  }
  return abs((l2.o - l1.o)|n)/abs(n);
}

p3 closest(ln3 l1, ln3 l2){    ///closest point ON line l1 TO line l2
  p3 n2 = l2.d%(l1.d%l2.d);
  return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2));
}
ld angle (ln3 l1, ln3 l2){
  return small_angle(l1.d, l2.d);
}
bool parallel(ln3 l1, ln3 l2){
  return l1.d%l2.d == zero;
}
bool perp(ln3 l1, ln3 l2){
  return (l1.d|l2.d) == 0;
}

///PLANE - LN3
ld angle(plane p, ln3 l){
  return pi/2 - small_angle(p.n, l.d);
}
bool parallel(plane p, ln3 l){
  return (p.n|l.d) == 0;
}
bool perp(plane p, ln3 l){
  return p.n%l.d == zero;
}
ln3 perp_at(plane p, p3 o){
  return line(o, o+p.n);
}
plane perp_at(ln3 l, p3 o){
  return plane(l.d, o);
}
