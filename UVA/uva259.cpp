// UVA 259
#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
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

const ll INF = INT_MAX;
const int MAXN = 50;

vector<int> g[MAXN];
const int source= 0, sink=1;
int cap[MAXN][MAXN];
int n, users;
int p[MAXN];
inline int convert(char ch){
    return ch-'A' + 2+10;
}


int edmonds(int n, int s, int t){
    int f, mf=0, u, w;
    while(1){
        memset(p, -1, sizeof p);
        p[s]=-2;
        queue<ii> q;
        q.push(ii(s,INF));
        f=0;
        while(!q.empty()){
            u = q.front().fi;
            w = q.front().se;
            q.pop();
            if(u==t){
                f= w;
                break;
            }
            for(int v: g[u])
                if(p[v]==-1 && cap[u][v]>0){
                    p[v]= u;
                    q.push(ii(v,min(w,cap[u][v])));
                }
        }
        if(f==0) return mf;
        else{
            int v= t;
            mf+= f;
            while(v!=s){
                cap[p[v]][v]-= f; cap[v][p[v]]+= f;
                v= p[v];
            }
        }
    }
    return mf;
}


string job;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    while(getline(cin, job)){
        forn(i,n+1){
            g[i].clear();
        }
        n=0;
        users=0;
        memset(cap, 0, sizeof cap);
        do{
            int act = convert(job[0]);
            int cantidad = job[1]-'0';
            users += cantidad;
            n=max(n,act+1);
            cap[source][act]= cantidad;
            g[source].pb(act);
            g[act].pb(source);
            for(int i = 3; i< job.size()-1; ++i ){
                int comp= job[i]-'0' +2;
                g[act].pb(comp);
                cap[act][comp] = INF;
                g[comp].pb(act);
            }
            getline(cin, job);
        }while(!job.empty());

        forn(i,10){
            cap[i+2][sink]=1;
            g[i+2].pb(sink);
            g[sink].pb(i+2);
        }

        int fl= edmonds(n,source,sink);

        if(fl<users){
            cout<< "!\n";
            continue;
        }
        fore(i,2,11){
            char x = '_';
            if(cap[sink][i]){
                fore(j,12,n){
                    if(cap[i][j]){
                        x='A';
                        x+=j-12;
                        break;
                    }
                }
            }
            cout<< x;
        }
        cout<<el;
    }
}
