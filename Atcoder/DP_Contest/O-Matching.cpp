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
const int MAXN = 21;
const int mod = 1e9+ 7;

int can[MAXN][MAXN];
ll dp[int(1<<MAXN)];
int allmask;

int n;

ll go(int mask){
    int idx = __builtin_popcount(mask);
    if(idx == n) return (mask == allmask);
    ll &r = dp[mask];
    if(r!=-1) return r;
    r= 0;
    for(int i=0; i<n; ++i){ // i es mujeres, idx es hombres
        if(!((1<<i)&mask) && can[idx][i]){
            r+= go(mask|(1<<i));
            r%=mod;
        }
    }
    return r;
}

int main(){
    ri(n);
    memset(dp, -1, sizeof dp);
    forn(i,n){
        forn(j,n){
            ri(can[i][j]);
        }
    }
    allmask = (1<<n)-1;
    printf("%lld\n",go(0));

}
