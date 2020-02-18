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

const int MAXN= 5000+10;
string s;

bool lens[MAXN][MAXN];
int pfila[MAXN][MAXN];
int q, l, r;


void manacher(){
    int d1[MAXN];
    memset(d1, 0, sizeof d1);
    int l=0, r=-1, n=s.size();
    forn(i, n){
        int k=(i>r? 1 : min(d1[l+r-i], r-i));
        while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) ++k;
        d1[i] = k--;
        if(i+k > r) l=i-k, r=i+k;
    }
    l=0, r=-1;
    for(int lon=1; lon<=n; lon+=2)
        forn(i,n)
            if(d1[i]*2>=lon)
                lens[lon][i-lon/2+1]=true;

    memset(d1,0,sizeof d1);
    forn(i, n){
        int k=(i>r? 0 : min(d1[l+r-i+1], r-i+1))+1;
        while(i+k-1<n && i-k>=0 && s[i+k-1]==s[i-k]) k++;
        d1[i] = --k;
        if(i+k-1 > r) l=i-k, r=i+k-1;
    }
    for(int lon=2; lon<=n; lon+=2)
        forn(i,n)
            if(d1[i]*2>=lon)
                lens[lon][i-lon/2+1]=true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>> s;
    int n= s.size();
    manacher();
    for(int i=1 ; i<=n; ++i){
        for(int j=1; j<=n-i+1; ++j){
            q = (lens[i][j] ? 1 : 0);
            pfila[i][j]= q + pfila[i-1][j];
        }
    }
    for(int j=1; j<=n; ++j){
        for(int i=1; i<=n-j+1; ++i){
            pfila[i][j]+=pfila[i+1][j-1];
        }
    }
    int dp[n+1];
//    int sumfilas[n+1];
//    sumfilas[0]=0;
    memset(dp, 0, sizeof dp);
    for(int i= 1; i<n+1; ++i){
        r=i;
        for(int j= 1; j<=i; ++j){
            q= (lens[r][j] ? 1 : 0);
            dp[i]+= q;
            r--;
        }
    }
    q= 0;
    for1(i,n){
        q+= dp[i];
        dp[i]= q;
    }
    cin>> q;
    while(q--){
        cin>> l>> r;
        cout<< dp[r]- pfila[r-l+2][l-1] << el;
    }
}
