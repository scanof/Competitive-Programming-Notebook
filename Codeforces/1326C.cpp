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

const ll inf = LONG_LONG_MAX;
const int nax = 1e5+200;
const double mpi = acos(-1);
const double eps= 1e-10;
const int mod =998244353 ;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(20)<< fixed;
    int n, k;
    cin>>n>>k;
    int a[n];
    int ans = 1;
    int len = 0;
    ll suma= 0;
    bool first = false;
    forn(i,n){
        cin>> a[i];
        if(a[i]> n-k){
            suma+= a[i];
            if(first) ans= (1LL*ans*len)%mod;
            len=0;
            first = true;
        }
        ++len;
    }
    cout<< suma <<" "<< ans%mod<< el;
}
