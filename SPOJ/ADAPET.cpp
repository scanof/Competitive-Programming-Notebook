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

vector<int> z_function(string s){
    int n= s.size();
    vector<int> z;  z.resize(n);
    int l=0, r=0;
    for1(i,n-1){
        if(i>r) l= r= i;
        z[i]= min(r-i,z[i-l]);
        while(i + z[i]< n && s[z[i]] ==s[z[i]+i]){
            ++z[i]; l = i;  r = i + z[i];
        }
    }
    return z;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int t;
    cin>> t;
    while(t--){
        string s;
        ll k;
        cin>> s>> k;
        int n= s.size();
        vector<int> z = z_function(s);
        ll mayor= 0;
        for1(i,n-1){
            if(z[i]+i==n){
                mayor = max(mayor, (ll)z[i]);
            }
        }
        cout<< k*n - (k-1)*mayor<<el;
    }
}
