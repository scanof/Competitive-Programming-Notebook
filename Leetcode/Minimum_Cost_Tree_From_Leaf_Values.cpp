    class Solution {

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

    typedef pair<int,int> ii;
    typedef long long ll;
    typedef pair<ll,ll> pll;
    const int INF = INT_MAX;

    public:
        int mctFromLeafValues(vector<int>& arr) {
            int n= arr.size();
            pll dp[n+1][n+1];
            forn(i,n){
                forn(j,n){
                    dp[i][j]= pll(INF,INF);
                }
            }
            for(int l= n-1; l>=0 ; --l){
                for(int r= 0; r<n; ++r){
                    if(l==r){
                        dp[l][l]= pll((ll)0, (ll)arr[l]);
                        continue;
                    }
                    for(int i=l; i<r; ++i){
                        if(dp[l][r].fi> dp[l][i].fi + dp[i+1][r].fi + dp[l][i].se*dp[i+1][r].se){
                            dp[l][r].fi= dp[l][i].fi+dp[i+1][r].fi + dp[l][i].se*dp[i+1][r].se;
                            dp[l][r].se = max(dp[l][i].se,dp[i+1][r].se) ;
                        }
                    }
                }
            }
            return dp[0][n-1].fi;
        }
    };
