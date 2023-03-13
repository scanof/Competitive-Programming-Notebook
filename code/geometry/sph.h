p3 sph_deg(ld r, ld lat, ld lon){
  lat *= pi/180, lon *= pi/180;
  return p3(r*cos(lat)*cos(lon), r*cos(lat)*sin(lon), r*sin(lat));
}
p3 sph(ld r, ld lat, ld lon){
  return p3(r*cos(lat)*cos(lon), r*cos(lat)*sin(lon), r*sin(lat));
}

int sph_ln_inter(p3 o, ld r, ln3 l, pair<p3,p3> &out){
  ld h2 = r*r - l.sq_dist(o);
  if(h2 < 0) return 0;  ///no intersection
  p3 p = l.proj(o);
  p3 h = l.d*sqrt(h2)/abs(l.d);   ///media cuerda
  out = {p-h, p+h};
  return 1 + (h2>0);
}
///if A,B not in sphere -> takes radial projections (from O)
ld sph_dist(p3 o, ld r, p3 a, p3 b){ return r * angle(a-o, b-o); }
///Accepts A==B, Denies opposite to each other (seg not well defined)
bool valid_seg(p3 a, p3 b){ return a%b != zero || (a*b) > 0; }

int sgn(ld x){
  if(x<0) return -1;
  else if(abs(x) <= eps) return 0;
  return 1;
}

bool proper_inter(p3 a, p3 b, p3 c, p3 d, p3 &out){
  p3 ab = a%b, cd = c%d;
  int oa = sgn(cd*a),  ob = sgn(cd*b),
      oc = sgn(ab*c),  od = sgn(ab*d);
  out = ab%cd * od;
  return (oa != ob && oc != od && oa != oc);
}

bool on_seg(p3 a, p3 b, p3 p){    ///segment = [A,B]
  p3 n = a%b;
  if(n == zero){
    return a%p == zero && (a*p) > 0;
  }
  return (n*p) == 0 && (n*(a%p)) >= 0 && (n*(b%p)) <= 0;
}

struct dir_set : vector<p3> {
  using vector::vector; ///import constructors
  void insert(p3 p){
    for(p3 q : *this)
      if(p%q == zero) return;
    pb(p);
  }
};

dir_set seg_inter(p3 a, p3 b, p3 c, p3 d){
  assert(valid_seg(a, b) && valid_seg(c, d));
  p3 out;
  if(proper_inter(a, b, c, d, out)) return {out};
  dir_set s;
  if(on_seg(c, d, a)) s.insert(a);
  if(on_seg(c, d, b)) s.insert(b);
  if(on_seg(a, b, c)) s.insert(c);
  if(on_seg(a, b, d)) s.insert(d);
  return s;
}

ld ang_sph(p3 a, p3 b, p3 c){ return ang(a%b, a%c);}
ld oriented_ang_sph(p3 a, p3 b, p3 c){
  if((a%b*c) >= 0)
    return ang_sph(a, b, c);
  else
    return 2*pi - ang_sph(a, b, c);
}

ld area_sph(ld r, vector<p3> &p){       ///for solid angle -> r = 1
  int n = sz(p);
  ld sum = -(n-2)*pi;
  forn(i,n)
    sum += oriented_ang_sph(p[(i+1)%n], p[(i+2)%n], p[i]);
  return r*r*sum;
}

int winding_number(vector<vector<p3>> &faces){
  ld sum = 0;
  for(vector<p3> f: faces)
    sum += remainder(area_sph(1, f), 4*pi);
  return round(sum / (4*pi));
}
