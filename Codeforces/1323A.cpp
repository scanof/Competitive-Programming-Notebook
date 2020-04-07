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
  int t;
  cin>> t;
  while(t--){
    int n;
    cin>> n;
    int fodd = -1, sodd=-1, even = -1;
    int num;
    for1(i,n){
      cin>> num;
      if(num&1){
        sodd= fodd;
        fodd= i;
      }else{
        even = i;
      }
    }
    if(even!=-1){
      cout<< 1<<el<< even<<el;
    }else if(fodd!=-1 && sodd!=-1){
      cout<< 2<< el<<fodd<< " "<<sodd<< el;
    }else{
      cout<<-1<<el;
    }
    
  }
  
}
