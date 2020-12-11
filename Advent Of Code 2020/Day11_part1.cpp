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

bool check(int i, int j, int n, int m){
  return i>= 0 && j>=0 && i<n && j <m;
}

int count_occ(vector<string> &g){
  int ans = 0;
  for(string x : g){
    for(char c: x){
      if(c=='#') ++ans;
    }
  }
  return ans;
}

void solve(vector<string> &g){
  int n = sz(g);
  int m = sz(g[0]);
  bool nochange = false;
  while(!nochange){
    nochange = true;
    vector<vector<bool>> change(n, vector<bool>(m, false));
    forn(i,n){
      forn(j,m){
        if(g[i][j]=='.') continue;
        int cnt = 0;
        forn(k,8){
          int x = dr[k] + i;
          int y = dc[k] + j;
          if(!check(x,y,n,n)) continue;
          if(g[x][y]=='#') ++cnt;
        }
        if(g[i][j]=='#'){
          if(cnt>=4) change[i][j] = true;
        }else{
          if(cnt==0) change[i][j] = true;
        }
      }
    }
    forn(i,n){
      forn(j,m){
        if(change[i][j]){
          nochange = false;
          if(g[i][j]=='#') g[i][j] = 'L';
          else g[i][j] = '#';
        }
      }
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout<< setprecision(20)<< fixed;
  vector<string> g;
  string s;
  while(cin>> s){
    g.pb(s);
  }
  solve(g);
  cout<< count_occ(g)<<el;
}
