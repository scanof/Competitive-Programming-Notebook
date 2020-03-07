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

const int MAXN = 202;

int n;
string s;

ll dp[10][2][200];

ll go(int idx, int menor, ll sum){
    if(idx==n){
        return sum;
    }
    ll &r = dp[idx][menor][sum];
    if(r!=-1) return r;
    r = 0;
    int k= (menor ? 9 : s[idx]-'0');
    for(int i=0; i<=k; ++i){
        if(k==i && !menor) r+= go(idx+1, menor, sum+i);
        else r+= go(idx+1, 1, sum+i);
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
//    cout<< setprecision(2)<< fixed;
    int a;
    string b;
    while(cin>> a>> b){
        if(a==-1) return 0;
        s= to_string(a-1);
        n = s.size();
        memset(dp, -1, sizeof dp);
        ll ans=0;
        if(a!=0) ans = -go(0, 0, 0);
        s= b;
        n = s.size();
        memset(dp, -1, sizeof dp);
        ans+= go(0, 0, 0);
        cout<< ans<<el;
    }
}
