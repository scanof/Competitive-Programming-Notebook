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

const int INF = 1e8;
const int MAXN = 500;
const double PI = acos(-1);
const double EPS= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

ii dp[MAXN][MAXN];


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>> n;
    int a[n];
    forn(i,n){
        cin>> a[i];
    }
    forn(i,n){
        forn(j,n){
            dp[i][j] = ii(INF, INF);
        }
    }
    forn(i,n){
        dp[i][i]= ii(1, a[i]);
    }
    for(int l = 1; l<n; ++l){
        for(int i = 0; i<n-l; i++) {
            int j = i+l;
            for(int k = i; k<j; k++) {
                int cost = ((dp[i][k].se != dp[k+1][j].se) || (dp[i][k].se == INF-2 || dp[k+1][j].se==INF-2));
                int nuevo = 0;
                if(cost == 1){
                    nuevo = dp[i][k].fi + dp[k+1][j].fi;
                }else{
                    nuevo = max(dp[i][k].fi, dp[k+1][j].fi);
                }
                if(nuevo < dp[i][j].fi){
                    dp[i][j].fi = nuevo;
                    if(cost == 1) dp[i][j].se = INF- 2;
                    else dp[i][j].se = dp[k+1][j].se + 1;
                }
            }
        }
    }
    cout<< dp[0][n-1].fi<<el;
}
