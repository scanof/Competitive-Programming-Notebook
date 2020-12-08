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
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define allr(v) v.rbegin(),v.rend()

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int inf = 1e9;
const int nax = 1e5+200;
const ld pi = acos(-1);
const ld eps= 1e-9;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

vector<pair<string,int>> steps;
int n;

int finish(){
  int i = 0, acc = 0;
  vector<bool> seen(n);
  while(i<n){
    if(seen[i]){
      return -1e9;
    }
    seen[i] = true;
    if(steps[i].fi == "nop") ++i;
    else if(steps[i].fi == "acc"){
      acc += steps[i].se;
      ++i;
    }else{
      i+= steps[i].se;
    }
  }
  if(i>=n){
    return acc;
  }else return -1e9;
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout<< setprecision(20)<< fixed;
  string s;
  int x;

  while(cin>> s>> x){
    steps.pb({s,x});
  }
  n = sz(steps);
  forn(i,n){
    if(steps[i].fi=="nop"){
      steps[i].fi = "jmp";
      x = finish();
      if(x!=-1e9){
        break;
      }
      steps[i].fi = "nop";
    }else if(steps[i].fi=="jmp"){
      steps[i].fi = "nop";
      x = finish();
      if(x!=-1e9){
        break;
      }
      steps[i].fi = "jmp";
    }
  }


  cout<< x<<el;

}
