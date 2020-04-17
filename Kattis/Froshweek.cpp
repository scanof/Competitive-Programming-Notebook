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

struct ST{
  int n;
  vi t, a;
  ST(){}
  ST(vector<int> &arr){
    a = arr;
    n = (int) a.size();
    t.resize(n<<2);
    build(1,0, n-1);
  }
  void build(int v, int tl, int tr){
    if(tl==tr){
      t[v]= a[tl];
      return ;
    }
    int tm = (tl+ tr)>>1;
    build(v<<1, tl, tm);
    build(v<<1|1, tm+1, tr);
    t[v] = t[v<<1] + t[v<<1|1];
  }

  int query(int v, int tl, int tr, int l, int r){
    if(l>r) return 0;
    if(l==tl && r== tr) return t[v];
    int tm= (tl+ tr)>>1;
    return query(v<<1, tl, tm, l, min(r,tm)) +
          query(v<<1|1, tm+1, tr, max(l,tm+1), r);
  }

  void update(int v, int tl, int tr, int pos, int val){
    if(tl==tr){
      t[v]= a[tl] += val;
      return ;
    }
    int tm = (tl+ tr)>>1;
    if(pos<= tm){
      update(v<<1, tl, tm, pos, val);
    }else{
      update(v<<1|1, tm+1, tr, pos, val);
    }
    t[v] = t[v<<1] + t[v<<1|1];
  }
};



int main(){
  int n;
  cin>> n;
  vector<int> a(n);
  map<int,int> mapa;
  forn(i,n){
    cin>> a[i];
  }
  vector<int> b = a;
  sort(a.begin(),a.end());
  int idx = 0;
  forn(i,n)
    if(!mapa.count(a[i]))
      mapa[a[i]] = idx++;
  vector<int> c(idx+5);
  ST st(c);
  int m = idx+4;
  ll ans = 0;
  reverse(b.begin(),b.end());
  forn(i,n){
    idx = mapa[b[i]];
    st.update(1,0,m,idx,1);
    ans+= st.query(1,0,m,0,idx-1);
  }
  cout<<ans<<el;
}


