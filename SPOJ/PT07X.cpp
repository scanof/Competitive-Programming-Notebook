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

const int MAXN = 1e5+200;
vi g[MAXN];
int dp[MAXN][2];

int dfs(int u, int p){
    dp[u][1]= 1;
    dp[u][0]= 0;
    for(int v: g[u]){
        if(v==p) continue;
        dfs(v, u);
        dp[u][1] += min(dp[v][0],dp[v][1]);
        dp[u][0] += dp[v][1];
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>> n;
    int u, v;
    forn(i,n-1){
        cin>> u>> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,0);
    cout<< min(dp[1][1], dp[1][0])<<el;
}

