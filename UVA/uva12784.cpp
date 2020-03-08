#include <bits/stdc++.h>

#define forn(i,n) for(int i= 0; i<n; ++i)
#define for1(i,n) for(int i= 1; i<=n; ++i)
#define fore(i,l,r) for(int i= l; i<=r; ++i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " "<< x<< el;
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> tiii;

const int MAXN = 1e3+20;

int in[MAXN];
vi g[MAXN];
vi gr[MAXN];
bool seen[MAXN];
bool det = false;
int w;
vi ts;

void dfs1(int u){
    seen[u]= true;
    for(int v: g[u]){
        if(!seen[v]) dfs1(v);
    }
    ts.pb(u);
}

void dfs2(int u){
    seen[u] = true;
    for(int v: gr[u]){
        if(!seen[v]) dfs2(v);
    }
}

void checkCycle(int n){
    det = false,
    memset(seen, false, sizeof seen);
    forn(i,n){
        if(!seen[i]) dfs1(i);
    }
    memset(seen, false, sizeof seen);
    reverse(ts.begin(), ts.end());
    w = 0;
    for(int i: ts){
        if(!seen[i]) dfs2(i),++w;
    }
    if(w!=n) det = true;
}

void dfs(int u){
    seen[u]= true;
    if(g[u].size()==0){
        if(w == -1 || w==u){
            w= u;
        }else{
            det = true;
            return ;
        }
    }
    for(int v: g[u]){
        if(!seen[v])
            dfs(v);
    }
}

int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<<fixed;
    int n, m, u, v;
    set<ii> s;

    while(cin>> n>> m){
        if(n+m==0) return 0;
        memset(in, 0, sizeof in);
        s.clear();
        forn(i,n) g[i].clear(), gr[i].clear();
        ts.clear();
        forn(i,m){
            cin>> u>> v;
            if(s.count(ii(u,v))) continue;
            s.insert(ii(u,v));
            in[v]++;
            g[u].pb(v);
            gr[v].pb(u);
        }
        checkCycle(n);
        if(det){
            cout<< 0<<el;
            continue;
        }
        memset(seen, false, sizeof seen);
        int k = 0;
        forn(i,n){
            if(in[i]==0){
                w= -1;
                dfs(i);
            }
        }
        forn(i,n){
            if(!seen[i]){
                det = true;
            }
        }
        if(det){
            cout<< 0<<el;
        }else{
            cout<< 1<<el;
        }
    }
}
