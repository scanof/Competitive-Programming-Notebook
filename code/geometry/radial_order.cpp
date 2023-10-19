typedef double ld;
struct pt{
  ld x, y; 
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator-(pt p){ return pt(x-p.x, y-p.y); }
  ld operator%(pt p){ return x*p.y - y*p.x; }
  int cuad(){
    if(x > 0 && y >= 0) return 0;
    if(x <= 0 && y > 0) return 1;
    if(x < 0 && y <= 0) return 2;
    if(x >= 0 && y < 0) return 3;
    return -1; // x == 0 && y == 0
  }
};
bool cmp(pt p1, pt p2){ // Around Origin(0, 0):  -->  sort(all(pts), cmp); 
  int c1 = p1.cuad(), c2 = p2.cuad();
  return c1 == c2 ? p1.y*p2.x < p1.x*p2.y : c1 < c2; 
} // Around const pt O(x, y):
//  -->  sort(all(pts), [&](pt& pi, pt& pj){ return cmp(pi - O, pj - O); });