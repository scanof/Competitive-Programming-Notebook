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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int mod = 1e9 + 7;

int n;
string s;
const int MAXN = 3010;

int dp[MAXN][MAXN];


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>> n;
    cin>> s;
    dp[1][1]= 1;
    for(int len= 2; len<=n; ++len){
        int suma = 0;
        for(int i= 1; i<=len; ++i){
            suma+= dp[len-1][i];
            suma%=mod;
            dp[len-1][i] = suma;
        }
        for(int num= 1; num<=len; ++num){
            int l, r;
            if(s[len-2]=='<'){
                l= 1; r= num-1;
            }else{
                l= num; r= len;
            }
            dp[len][num] += (dp[len-1][r]- dp[len-1][l-1] + mod )%mod;

        }
    }
    int ans =0;
    for1(i,n){
        ans+=dp[n][i];
        ans%=mod;
    }
    cout<<ans<<el;
}
