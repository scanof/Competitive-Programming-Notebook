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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
//    cout<< setprecision(2)<< fixed;
    string s;
    while(cin>> s){
        if(s=="0") return 0;
        int n = s.size();
        ll dp[n+1];
        memset(dp,0,sizeof dp);
        dp[0]=1;
        for1(i,n){
            int j = i-1;
            if(s[j]=='0'){
                dp[i]= dp[i-2];
                continue;
            }
            dp[i]= dp[i-1];
            if(j-1>=0 && ((s[j-1]<='2' && s[j-1]>='1' && s[j]<='6') || (s[j-1]=='1'))){
                dp[i]+= dp[i-2];
            }
        }
        cout<< dp[n]<<el;
    }
}
