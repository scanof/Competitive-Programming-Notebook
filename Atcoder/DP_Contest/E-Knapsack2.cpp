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

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const double EPS= 1e-10;

int n, W;
ll dp[MAXN][110];
ll V;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>> n >> W;

    pair<int, ll> pare[n];
    forn(i,n){
        ll a; int b;
        cin>> a>> b;
        pare[i+1]= make_pair(b,a);
        V+= b;
    }
    sort(pare, pare+n);
    forn(i,V+1){
        forn(j,n+1){
            dp[i][j]= 1e11;
        }
    }
    for1(j,n){
        for1(i,V){
            dp[i][j]= min(dp[i][j], dp[i][j-1]);
            if(pare[j].fi==i){
                dp[i][j]=  min(dp[i][j-1], pare[j].se);
            }else if(i-pare[j].fi>=0 && dp[i- pare[j].fi][j]!=1e11){
                dp[i][j]=  min(dp[i][j-1], pare[j].se + dp[i-pare[j].fi][j-1]);
            }
        }
    }
    int valor= 1;
    for1(i,V){
        if(dp[i][n] && dp[i][n]<=W ){
            valor= max(i,valor);
        }
    }
    cout<< valor<<el;
}

