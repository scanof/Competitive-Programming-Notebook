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
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<long long,long long> pll;
typedef tuple<long double,int,int> tdii;
const double PI = atan(1)*4;
const int MAXN = 405;
const double EPS = 1e-9;
pll dp[MAXN][MAXN]; //NUMERO  -  COSTO

int main (){
    ll n, c;
    cin>>n;
    forn(i,n){
        cin>>c;
        dp[0][i]=pll(c,0);
    }
    forn(i,n-1){
        c = dp[0][i].fi+dp[0][i+1].fi;
        dp[1][i]=pll(c,c);
    }

    fore(i,2,n-1){
        forn(j,n-i){
            c = LONG_LONG_MAX;
            forn(k, i){
                c=min(c, dp[i-1-k][j].se+dp[i-1-k][j].fi+dp[k][i+j-k].se+dp[k][i+j-k].fi);
            }
            dp[i][j] = pll(dp[i-1][j].fi+dp[0][i+j].fi,c);
        }
    }
    cout<<dp[n-1][0].se<<el;
}
