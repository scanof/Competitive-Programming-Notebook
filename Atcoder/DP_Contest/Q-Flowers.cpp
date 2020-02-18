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
const int MAXN = 2e5+20;
const double EPS= 1e-10;



struct FenwickTree { // index-1
    vector<ll> ft;
    FenwickTree(int n){
        ft.assign(n + 1, 0);
    } // init n + 1 zeroes

    ll rsq(int b) { // returns RSQ(1, b)
        ll maxi = 0; for (; b; b -= (b&(-b)) ) maxi = max(maxi,ft[b]);
        return maxi;
    }
    void adjust(int k, ll v) { // note: n = ft.size() - 1
        for (; k < (int)ft.size(); k += (k&(-k))) ft[k] = max(v,ft[k]);
    }
};

int h[MAXN];
ll a[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>> n;
    int m=0;
    forn(i,n){
        cin>> h[i];
        m= max(m,h[i]);
    }
    forn(i,n) cin>> a[i];
    FenwickTree f = FenwickTree(m+10);
    forn(i,n){
        ll v= f.rsq(h[i]);
        f.adjust(h[i],a[i]+v);
    }
    cout<< f.rsq(m+9)<<el;
}
