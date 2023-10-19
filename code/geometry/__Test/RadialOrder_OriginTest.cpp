//https://codeforces.com/group/DA7Y6pkafQ/contest/452264/problem/C
#include <bits/stdc++.h>

#define forn(i,n) for(int i = 0; i < n; ++i)
#define for1(i,n) for(int i = 1; i <= n; ++i)
#define el '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef long long ll;

struct pt{
  ll x, y; 
  pt(){}
  pt(ll x, ll y) :x(x), y(y){}
  pt operator-(pt p){ return pt(x-p.x, y-p.y); }
  ll operator%(pt p){ return x*p.y - y*p.x; }
  int cuad(){
    if(x > 0 && y >= 0) return 0;
    if(x <= 0 && y > 0) return 1;
    if(x < 0 && y <= 0) return 2;
    if(x >= 0 && y < 0) return 3;
    return -1; // x == 0 && y == 0
  }
  ll side(pt p, pt q){ return (q-p) % (*this - p); }
};
bool cmp(pt p1, pt p2){
  int c1 = p1.cuad(), c2 = p2.cuad();
  return c1 == c2 ? p1.y*p2.x < p1.x*p2.y : c1 < c2; 
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  const pt O(0, 0);
  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    vector<pt> pts(n);
    forn(i, n) cin >> pts[i].x >> pts[i].y;
    sort(all(pts), cmp); // Sort around Origin

    int l = 0, r = 0, ans = n;
    while(l < n){
      while((r+1)%n != l && pts[(r+1)%n].side(O, pts[l]) >= 0) r = (r+1) % n;
      int cur = r-l+1 + (r >= l ? 0 : n);
      ans = min({ans, cur, n-cur});
      ++l;
    }
    cout << ans << el;
  }
}