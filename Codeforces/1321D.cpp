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
const int MAXN = 3e5+200;

vi g[MAXN];
vi gr[MAXN];
int dist[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n, m, u,v;
    cin>>n>>m;
    forn(i,m){
        cin>>u>> v;
        g[u].pb(v);
        gr[v].pb(u);
    }
    int k;
    cin>>k;
    int path[k];
    forn(i,k) cin>> path[i];
    int s = path[0], t= path[k-1];
    queue<int> q;
    q.push(t);
    while(!q.empty()){
        u = q.front();
        q.pop();
        for(int v: gr[u]){
            if(dist[v]==0 && v!=t){
                dist[v]= dist[u]+1;
                q.push(v);
            }
        }
    }
    int ans1 = 0, ans2= 0;
    for(int i= 0; i<k-1; ++i){
        int cur = path[i], next= path[i+1];
        if(dist[next]+1!= dist[cur]){
            ++ans1;
        }else{
            for(int v: g[cur]){
                if(dist[next]== dist[v] && next!=v){
                    ++ans2;
                    break;
                }
            }
        }
    }
    cout<< ans1<<" "<<ans2+ans1<< el;

}
