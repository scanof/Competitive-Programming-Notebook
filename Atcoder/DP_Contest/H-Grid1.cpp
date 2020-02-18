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
const int MAXN = 1e3+20;
const double EPS= 1e-10;
const ll MOD = 1e9+7;
int h,w;
string pt[MAXN];
ll dp[MAXN][MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>> h>> w;
    string s;
    forn(i,h){
        cin>> pt[i+1];
    }
    queue<ii> q;
    q.push(ii(1,1));
    dp[1][1]=1;
    while(!q.empty()){
        int x = q.front().fi;
        int y = q.front().se;
        q.pop();
        if(x+1<=h && pt[x+1][y-1]=='.'){
            if(dp[x+1][y]==0) q.push(ii(x+1,y));
            dp[x+1][y]+= dp[x][y]%MOD;
        }
        if(y+1<=w && pt[x][y]=='.'){
            if(dp[x][y+1]==0) q.push(ii(x,y+1));
            dp[x][y+1]+= dp[x][y]%MOD;

        }
    }
    cout<< dp[h][w]%MOD<<el;
}

