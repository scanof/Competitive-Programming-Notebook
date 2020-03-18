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

const int MAXN = 1e5+20;

bool seen[MAXN];
vector<int> g[MAXN];
vi ts;
vi grev[MAXN];

void dfs1(int u){
    seen[u]= true;
    for(int v: g[u]){
        if(!seen[v])
            dfs1(v);
    }
    ts.pb(u);
}

void dfs(int u){
    seen[u]= true;
    for(int v: grev[u])
        if(!seen[v])
            dfs(v);
}



void solve(int n){
    forn(i,n){
        if(!seen[i])
            dfs1(i);
    }
    reverse(ts.begin(),ts.end());
    forn(i,n){
        seen[i]= false;
    }
    int contador= 0;
    for(int v: ts){
        if(!seen[v]){
            dfs(v);
            ++contador;
        }
        if(contador==2) break;
    }
    if(contador==1) cout<< "1\n";
    else cout<< "0\n";
    forn(i,n){
        g[i].clear(); grev[i].clear();
        seen[i]= false;
    }
    ts.clear();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    while(cin>> n>> m){
        if(n+m==0) return 0;
        int v, w, p;
        forn(i,m){
            cin>> v>> w >> p;
            g[v-1].pb(w-1);
            grev[w-1].pb(v-1);
            if(p==2)  g[w-1].pb(v-1), grev[v-1].pb(w-1);
        }
        solve(n);
    }
}
