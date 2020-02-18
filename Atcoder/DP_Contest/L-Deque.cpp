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

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const double EPS= 1e-10;
const int nax= 300;

int main(){
    int n;
    cin>>n ;
    int arr[n];
    forn(i,n) cin>> arr[i];
    ll dp[n][n];
    for(int l= n-1; l>=0 ; l--){
        for(int r= l; r<n; r++){
            if(l==r){
                dp[l][r]= arr[l];
                continue;
            }
            dp[l][r]= max(arr[l]- dp[l+1][r], arr[r]- dp[l][r-1]);
        }
    }
    cout<< dp[0][n-1]<<el;
}

