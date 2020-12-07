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
const int nax = 1e3+200;
const ld pi = acos(-1);
const ld eps= 1e-9;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

unordered_map<string, int> mp;
int idx = 0;

int ans = 0;
vi g[nax];
bool seen[nax];

void dfs(int u){
  seen[u] =  true;
  ++ans;
  for(int v: g[u]){
    if(!seen[v]){
      dfs(v);
    }
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  string tmp;
  while(getline(cin, tmp)){
    stringstream ss(tmp);
    string s1, s2, x;
    ss >> s1 >> s2 >> x;
    assert(x=="bags");
    ss >> x;
    s1 += " "+ s2;
    int u;
    if(!mp.count(s1)) mp[s1] = idx++;
    u = mp[s1];
    int num;
    while(ss >> num>> s1 >> s2 >> x){
      s1 += " "+ s2;
      int v;
      if(!mp.count(s1)) mp[s1] = idx++;
      v = mp[s1];
      g[v].pb(u);
    }
  }
  int u = mp["shiny gold"];
  dfs(u);
  cout<< ans-1<<el;
}
