#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

struct dsu{ // 0-indexed
    vi p, r; int numSets;
    void init(int n) {
        p.assign(n, 0); r.assign(n, 1); numSets = n;
        forn(i,n) p[i] = i;
    }
    int findSet(int i) { return (p[i]==i)? i: (p[i]=findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        int x = findSet(i), y = findSet(j);
        if (x != y) {
            if (r[x] > r[y]){
                p[y] = x;
                r[x]+=r[y]; r[y]= 0;
            }else {
                p[x] = y;
                r[y]+=r[x]; r[x]= 0;
            } numSets--;
        }
    }
};

struct pt{
  int x,y;
};

bool dist(pt &a, pt &b){
  return abs(a.x-b.x)+ abs(a.y-b.y) <=1000;
}

bool merges(vector<pt> &pts){
  dsu uf;
  int n= pts.size();
  uf.init(n);
  for(int i= 0; i<n; ++i){
    for(int j= i+1; j<n; ++j){
      if(dist(pts[i], pts[j])){
        uf.unionSet(i,j);
      }
    }
  }
  return uf.isSameSet(0,n-1);
}

int main(){
  int t;
  cin>> t;
  int n;
  while(t--){
    cin>> n;
    n+=2;
    vector<pt> pts(n);
    forn(i,n){
      cin>> pts[i].x>> pts[i].y;
    }
    if(merges(pts)) cout<< "happy"<<el;
    else cout<< "sad"<<el;
  }
}


