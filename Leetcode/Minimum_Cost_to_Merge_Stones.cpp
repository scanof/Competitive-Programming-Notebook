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


typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef pair<ll,ii> plii;    

public:
    int mergeStones(vector<int>& stones, int K) {
        int n;
        n= stones.size();
        int prefix[n];
        int suma=0;
        forn(i,n){
            suma+= stones[i];
            prefix[i]= suma;
        }
        if ((n - 1) % (K - 1)) return -1;
        ll dp[n][n];
        forn(i,n)
            forn(j,n)  dp[i][j]= 0;
        for(int len= K; len<=n; ++len){
            for(int left= 0; left+ len<=n; ++left){
                int right= left+len-1;
                dp[left][right]= INT_MAX;
                for(int i= left; i<right; i+= K-1){
                    dp[left][right]= min(dp[left][right], dp[left][i]+ dp[i+1][right]  );
                }
                int p= prefix[right]- (left-1>=0 ? prefix[left-1]: 0);
                if((right-left)%(K-1)==0){
                    dp[left][right]+= p;
                }
            }
        }
        return (dp[0][n-1]==INT_MAX ? -1 : dp[0][n-1]);
    }
};
