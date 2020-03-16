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

// O(V*E^2)
// Tener cuidado con el maxn y el inf dependiendo del problem
const int INF = 1e9;
const int MAXN = 1030;
int cap[MAXN][MAXN];
vi g[MAXN];
int p[MAXN];

int bfs(int s, int t) {
    memset(p, -1, sizeof p);
    p[s] = -2;
    queue<ii> q;
    q.push(ii(s, INF));
    while (!q.empty()) {
        int u = q.front().fi;
        int f = q.front().se;
        q.pop();
        for(int v: g[u]){
            if (p[v] == -1 && cap[u][v]) {
                p[v] = u;
                int new_f = min(f, cap[u][v]);
                if (v == t)
                    return new_f;
                q.push(ii(v, new_f));
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int mf = 0;
    int f;
    while (f = bfs(s,t)){
        mf += f;
        int v = t;
        while (v != s) {
            int prev = p[v];
            cap[prev][v] -= f;
            cap[v][prev] += f;
            v = prev;
        }
    }
    return mf;
}

void add(int u, int v){
    g[u].pb(v);
    g[v].pb(u);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, m;
    while(cin>> n>> m && n+m!=0){
        int a[n];
        // n : number of categories
        // m : number of problems
        int s = n+m+2;
        int t= s+1;
        int flow =0;
        memset(cap, 0, sizeof cap);
        forn(i,n) cin>> a[i], flow+= a[i], add(s,i), cap[s][i]= a[i];
        forn(i,m){
            int k;
            cin>> k;
            int cat;
            while(k--){
                cin>> cat;
                cat--;
                add(cat,i+n);
                cap[cat][i+n] = 1;
            }
            add(i+n, t);
            cap[i+n][t]=1;
        }
        bool works = (maxflow(s,t)==flow);
        forn(i,t+1){
            g[i].clear();
        }
        cout<< works<<el;
        if(!works) continue;
        forn(i,n){
            fore(j,n,n+m-1){
                if(cap[j][i]==1){
                    if(a[i]-- ==1) cout<< j-n+1;
                    else cout<< j-n+1<<" ";
                }
            }
            cout<<el;
        }
    }
}
