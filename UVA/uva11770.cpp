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

const int MAXN = 1e4+200;

vector<int> g[MAXN];
bool seen[MAXN];
vector<int> ts;

void dfs1(int u){
    seen[u]= true;
    for(int v: g[u]){
        if(!seen[v]){
            dfs1(v);
        }
    }
    ts.pb(u);
}

void dfs(int u){
    seen[u]= true;
    for(int v: g[u]){
        if(!seen[v]){
           dfs(v);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin>> t;
    int n, m;
    int u, v;
    for1(tes,t){
        cin>> n>> m;
        forn(i,n) g[i].clear();
        memset(seen, false, sizeof seen);
        ts.clear();
        forn(i,m){
            cin>> u>> v;
            g[--u].pb(--v);
        }
        forn(i,n){
            if(!seen[i]){
                dfs1(i);
            }
        }
        memset(seen, false, sizeof seen);
        int ans = 0;
        reverse(ts.begin(), ts.end());
        for(int i : ts){
            if(!seen[i]){
                dfs(i); ++ans;
            }
        }
        cout<<"Case "<<tes<<": "<< ans<<el;
    }
}

