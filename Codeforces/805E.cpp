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

const int MAXN = 3e5+200;
int n, m;
vi ice[MAXN]; // grafo de iceores
vi g[MAXN]; // grafo original
int col[MAXN];
bool used[MAXN];


void dfs(int u, int p){
    int rem = 1;
    for(int v: ice[u]) used[col[v]]=true;
    for(int v: ice[u]){
        if(col[v]) continue;
        while(used[rem]) ++rem;
        col[v]= rem++;
    }
    for(int v: ice[u]) used[col[v]]= false;
    for(int v: g[u])
        if(v!=p) dfs(v,u);
}

int main(){
    ri(n), ri(m);
    int cap;
    int u, v;
    int capmax = 1;
    forn(i,n){
        ri(cap);
        capmax = max(capmax, cap);
        forn(j,cap){
            ri(u);
            ice[i].pb(u);
        }
    }
    forn(i,n-1){
        ri(u), ri(v);
        g[--u].pb(--v), g[v].pb(u);
    }
    dfs(0,-1);
    printf("%d\n",capmax);
    for1(i,m){
        printf("%d ",max(1,col[i]));
    }
    printf("\n");

}
