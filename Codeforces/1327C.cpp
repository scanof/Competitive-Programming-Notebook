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
const int nax = 210;
const double mpi = acos(-1);
const double eps= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};



int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
//    cout<< setprecision(20)<< fixed;
    int n, m, k;
    cin>> n>> m>> k;
    int x, y;
    forn(i,2*k){
        cin>> x>> y;
    }
//    cout<< n+m + n*m<<el;
    int ans= 0;
    string s;
    forn(i,n){
        ++ans;
        s+= "U";
    }
    forn(i,m){
        ++ans;
        s+= "L";
    }
    forn(i,n){
        forn(j,m-1){
            ++ans;
            if(i%2==0){
                s+= "R";
            }else{
                s+= "L";
            }
        }
        if(i==n-1) continue;
        ++ans;
        s+= "D";
    }
    cout<<ans<<el;
    cout<<s<<el;
}
