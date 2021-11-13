struct plane{   ///ax + by + cz = d <=> n|(x, y, z) = d (all points with p|n = d)
  p3 n; ld d;   ///normal, offset
  plane() {}
  plane(p3 n, ld d) : n(n), d(d) {}
  plane(p3 n, p3 p) : n(n), d(n|p) {}                 ///given normal, point
  plane(p3 p, p3 q, p3 r) : plane((q-p)%(r-p), p) {}  ///given 3 points (uses previous line!!)
  ///point operators
  ld side(p3 p){ return (n|p) - d;}     ///>0 side pointed by n (above), ==0 on plane, <0 below
  ld dist(p3 p){ return abs(side(p))/abs(n);}
  bool has(pt p){return dist(p) <= eps;}
  p3 proj(p3 p){ return p - n*side(p)/sq(n);}
  p3 refl(p3 p){ return p - n*2*side(p)/sq(n);}
  ///translations
  plane translate(p3 t){ return plane(n, d+(n|t));}
  plane shift_up(ld dis) { return plane(n, d+dis*abs(n));}
};

///PLANE - PLANE
ld angle(plane p1, plane p2){
  return small_angle(p1.n, p2.n);
}
bool parallel(plane p1, plane p2){
  return p1.n%p2.n == zero;
}
bool perp(plane p1, plane p2){
  return (p1.n|p2.n) == 0;
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
