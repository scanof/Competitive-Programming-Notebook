// https://codeforces.com/gym/104114/problem/B
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define fored(i,l,r) for(int i=r; i>=l; --i)
#define sz(v) int(v.size())
#define el '\n'
#define pb push_back
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << " : " << x << el;

using namespace std;

typedef long long ld;

struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator+(pt p){return pt(x+p.x, y+p.y);}
  pt operator-(pt p){return pt(x-p.x, y-p.y);}
  pt operator*(ld t){return pt(x*t, y*t);}
  ld operator*(pt p){return x*p.x + y*p.y;}
  ld operator%(pt p){return x*p.y - y*p.x;}

  bool operator<(pt p){ return x == p.x ? y < p.y : x < p.x; }
  int cuad(){
    if(x > 0 && y >= 0) return 0;
    if(x <= 0 && y > 0) return 1;
    if(x < 0 && y <= 0) return 2;
    if(x >= 0 && y < 0) return 3;
    return -1; // x == 0 && y == 0
  }
  ld side(pt p, pt q){return (q - p) % (*this - p);}
  bool left(pt p, pt q){
    ld cs = side(p, q);
    if(cs > 0) return 1;
    else if(cs < 0) return 0;
    return (q - p) * (*this - p) > 0;
  }
};

// CCW order, excludes collinear points
// Change .side(r[sz(r)-2], p[i]) > 0 to include collinear
vector<pt> chull(vector<pt>& p){ 
  if(sz(p) < 3) return p;
  vector<pt> r;
  sort(all(p));  // first x, then y
  forn(i,sz(p)){ // lower hull
    while(sz(r) > 1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  int k = sz(r);
  fored(i, 0, sz(p)-1){ // upper hull
    while(sz(r) > k+1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  return r;
}

bool has(vector<pt>& pol, pt& p){
  if(sz(pol) == 1) return 0;
  int cnt = 0;
  forn(i, sz(pol)) cnt += p.side(pol[i], pol[(i+1) % sz(pol)]) >= 0;
  return cnt == sz(pol);
}

bool cmp(pt p1, pt p2){ // Around Origin(0, 0):  -->  sort(all(pts), cmp); 
  int c1 = p1.cuad(), c2 = p2.cuad();
  return c1 == c2 ? p1.y*p2.x < p1.x*p2.y : c1 < c2; 
} 

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m;
  vector<pt> cho, str;
  cin >> n >> m;
  cho.resize(n);  str.resize(m);

  forn(i, n + m){
    string x, y; cin >> x >> y;
    x = x.substr(2);
    x = x + string(6 - sz(x), '0');
    y = y.substr(2);
    y = y + string(6 - sz(y), '0');
    if(i < n) cho[i] = pt(stoi(x), stoi(y));
    else str[i-n] = pt(stoi(x), stoi(y));
  }

  str = chull(str);
  vector<pt> tmp;
  forn(i, n) if(!has(str, cho[i])) tmp.pb(cho[i]);
  cho.swap(tmp);

  int ans = 0;
  forn(i, sz(str)){
    pt O = str[i], b = str[(i+1) % sz(str)], c = str[(i-1 + sz(str)) % sz(str)];
    sort(all(cho), [&](pt& pi, pt& pj){ return cmp(pi - O, pj - O); }); // Sort around pt O
    
    int l = 0, r = 0;
    while(l < sz(cho)){
      while((r+1) % sz(cho) != l && cho[(r+1) % sz(cho)].left(O, cho[l])){
        r = (r+1) % sz(cho);
      }
      if(sz(str) == 1 || (!c.left(O, cho[l]) && !b.left(O, cho[l]))){
        int cur = (r >= l ? r-l+1 : r+sz(cho)-l+1);
        ans = max(ans, cur);
      }
      if(l == r) ++r;
      ++l;
    }
  }
  cout << ans << el;
}