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

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int n;
  cin>> n;
  vector<int> a(n);
  forn(i,n) cin>> a[i];
  int product = 1;
  bool fix_it = false;
  ll ans = 0;
  forn(i,n){
    if(abs(a[i]-1)<abs(a[i]+1)){
      ans+= abs(a[i]-1);
    }else if(abs(a[i]-1)>abs(a[i]+1)){
      ans+= abs(a[i]+1);
      product*=-1;
    }else{
      fix_it = true;
      ans+= 1;
    }
  }
  if(fix_it){
    cout<< ans<< el;
    return 0;
  }
  if(product<0){
    cout<< ans+2<<el;
    return 0;
  }
  cout<< ans<<el;
  return 0;
}
