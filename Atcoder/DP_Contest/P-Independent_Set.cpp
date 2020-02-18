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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const double EPS= 1e-10;
int n;
vector<int> g[MAXN];
pll dp[MAXN]; // fi: blanco, se: negro
bool seen[MAXN];
const int mod = 1e9+7;

pll dfs(int a, int parent){
    pll ans = pll(1,1);
    for(int b : g[a]){
        if(b!= parent){
            pll p = dfs(b, a);

            ans.fi = (ans.fi* (p.fi + p.se))%mod;
            ans.se = (ans.se* p.fi )%mod;
        }
    }
    return ans;
}

int main(){
    cin>> n;
    if(n==1){
        cout<< 2<<el;
        return 0;
    }
    int x, y;
    forn(i,n-1){
        cin>> x>> y;
        x; y;
        g[x].pb(y);
        g[y].pb(x);
    }
    pll a =dfs(1,-1);
    cout<< (a.fi+ a.se)%mod<<el;

}


