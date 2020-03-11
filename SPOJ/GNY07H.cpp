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

int n;
int m=4;

ll dp[1<<4][100000][4];

ll go(int mask, int i, int j){
    if(i==n){
        return (mask==0);
    }
    if(j==m){
        return go(mask, i+1, 0);
    }
    ll &r= dp[mask][i][j];
    if(r!=-1) return r;
    r = 0;
    if(mask & (1<<j)){
        return r = go(mask ^(1<<j), i, j+1);
    }
    if(i+1<= n){
        r = go(mask | (1<<j), i, j+1);
    }
    if(j+2<= m && !(mask & (1<<(j+1))) ){
        r+= go(mask, i, j+2);
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin>> t;
    for1(test, t){
        cin>> n;
        memset(dp, -1, sizeof dp);
        cout<< test << " "<<go(0, 0, 0)<<el;
    }
}
