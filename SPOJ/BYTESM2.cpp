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
const int MAXN = 20;
const double PI = acos(-1);
const double EPS= 1e-10;
const ll limite = 1e16;

ll dp[1<<20];
int n;
int grid[20][20];

int dr[]= {1,1,1};
int dc[]= {0,-1,1};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(20)<< fixed;
    int t;
    cin>> t;
    while(t--){
        int n, m;
        cin>> n>> m;
        int grid[n][m];
        forn(i,n){
            forn(j,m) cin>> grid[i][j];
        }
        int dp[n][m];
        memset(dp, 0, sizeof dp);
        forn(i,m){
            dp[n-1][i]= grid[n-1][i];
        }
        for(int i=n-2; i>=0 ; --i){
            forn(j,m){
                forn(k,3){
                    int x = dr[k]+ i, y = dc[k] + j;
                    if(x < n && x>= 0 && y <m && y>=0){
                        dp[i][j]= max(dp[i][j], grid[i][j] + dp[x][y]);
                    }
                }
            }
        }
        int ans = 0;
        forn(i,m){
            ans = max(ans, dp[0][i]);
        }
        cout<< ans<< el;
    }
}
