typedef long double ld;
const ld eps = 1e-10, inf = 1e50;
struct pt {  // for 3D add z coordinate
  ld x,y;
  pt(){}
  pt(ld x, ld y):x(x),y(y){}
  
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
  pt operator-(pt p){return pt(x-p.x,y-p.y);}
  pt operator*(ld t){return pt(x*t,y*t);}
  pt operator/(ld t){return pt(x/t,y/t);}
  ld operator*(pt p){return x*p.x+y*p.y;}
  ld operator%(pt p){return x*p.y-y*p.x;}
  
  ld norm2(){return *this**this;}
  ld norm(){return sqrt(norm2());}
  pt unit(){return *this/norm();}
};
struct ln {
  pt p,pq;
  ln(){}
  ln(pt p, pt q):p(p),pq(q-p){}
  bool operator/(ln l){return abs(pq.unit()%l.pq.unit()) <= eps;}
  pt operator^(ln l){ // intersection
    if(*this/l) return pt(inf,inf);
    pt r = l.p+l.pq * ((p-l.p)%pq / (l.pq%pq));
    return r;
  }
};

// polygon intersecting left side of halfplanes (CCW order) 
struct hp:public ln{
  ld angle;
  hp(){}
  hp(pt a, pt b){p=a; pq=b-a; angle=atan2(pq.y, pq.x);}
  bool operator<(hp b)const{return angle < b.angle;}
  bool out(pt q){return pq%(q-p) < -eps;}
};
vector<pt> intersect(vector<hp>& b){
  vector<pt>bx={{inf,inf}, {-inf,inf}, {-inf,-inf}, {inf,-inf}};
  forn(i,4) b.pb(hp(bx[i],bx[(i+1)%4]));
  sort(all(b));
  int n=sz(b), q=1, h=0;
  vector<hp> c(sz(b)+10);
  forn(i,n){
    while(q<h && b[i].out(c[h]^c[h-1])) h--;
    while(q<h && b[i].out(c[q]^c[q+1])) q++;
    c[++h] = b[i];
    if(q<h && abs(c[h].pq%c[h-1].pq) < eps){
      if(c[h].pq*c[h-1].pq <= 0) return {};
      h--;
      if(b[i].out(c[h].p)) c[h]=b[i];
    }
  }
  while(q<h-1 && c[q].out(c[h]^c[h-1])) h--;
  while(q<h-1 && c[h].out(c[q]^c[q+1])) q++;
  if(h-q <= 1) return {};
  c[h+1] = c[q];
  vector<pt> s;
  fore(i,q,h) s.pb(c[i]^c[i+1]);
  return s;
}