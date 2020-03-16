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

const int INF = INT_MAX;
const int MAXN = 105;
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


int n, s, t, m, u, v, w , cas;

int main(){
    while(ri(n)!=EOF){
        if(n==0) return 0;
        memset(cap, 0, sizeof cap);
        forn(i,n+1) g[i].clear();
        ri(s); ri(t); ri(m);
        forn(i,m){
            ri(u); ri(v); ri(w);
            g[u].pb(v);
            g[v].pb(u);
            cap[u][v]+= w;
            cap[v][u]+= w;
        }
        printf("Network %d\nThe bandwidth is %d.\n\n",++cas, maxflow(s,t));
    }

}
