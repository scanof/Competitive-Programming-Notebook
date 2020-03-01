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
const int MAXN = 1e5+200;
const double PI = acos(-1);
const double EPS= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int dos, tres, cinco, seis;
    cin>> dos>> tres>> cinco>> seis;
    int m = min(dos, min(cinco,seis));
    dos-=m;
    cinco-=m;
    seis-=m;
    int ans = 256*m;
    m = min(dos,tres);
    ans += 32 * m;
    cout<<ans<<el;
}

