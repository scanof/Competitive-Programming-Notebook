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
    int maxCoins(vector<int>& nums) {
        int n;
        n= nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int dp[n+2][n+2];
        memset(dp, 0, sizeof dp);
        for (int len = 1; len <= n; ++len)
            for (int left = 1; left <= n - len + 1; ++left) {
                int right = left + len - 1;
                d(dp[left][right]);
                for(int k= left; k<= right; ++k){
                    dp[left][right]= max(dp[left][right], nums[left-1]*nums[k]*nums[right+1]+ dp[left][k-1]+ dp[k+1][right] );
                }
                d(dp[left][right]);
                cout<<el;
            }
        return dp[1][n];
    }
};
