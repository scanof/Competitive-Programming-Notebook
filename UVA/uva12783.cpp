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

const ll INF = LONG_LONG_MAX;
const int MAXN = 1e3+20;
const double PI = acos(-1);
const double EPS= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

vi g[MAXN];
int num[MAXN], low[MAXN];
bool seen[MAXN];
int n;
vector<ii> ans;
int timer;

void dfs(int u, int p=-1){
    seen[u]= true;
    int children = 0;
    low[u] = num[u]= timer++;
    for(int v: g[u]){
        if(v==p) continue;
        if(seen[v]){
            low[u]= min(low[v], low[u]);
        }else{
            dfs(v,u);
            low[u]= min(low[v], low[u]);
            if(low[v]> num[u]){
                ans.pb(ii(min(u,v), max(u,v)));
            }
            children++;
        }
    }
    if(p==-1 && children>1){
        //CUTPOINT
    }
}

void solve(){
    ans.clear();
    timer = 0;
    memset(num, -1, sizeof num);
    memset(seen, false, sizeof seen);
    memset(low, -1, sizeof low);
    forn(i,n){
        if(!seen[i]) dfs(i);
    }
    sort(ans.begin(), ans.end());
    cout<< ans.size();
    for(ii x: ans){
        cout<<" "<< x.fi<< " "<<x.se;
    }
    cout<<el;
    forn(i,n) g[i].clear();
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int m;
    while(cin>> n>> m && n+m!=0){
        int u, v;
        forn(i,m){
            cin>> u>> v;
            g[u].pb(v);
            g[v].pb(u);
        }
        solve();
    }

}
