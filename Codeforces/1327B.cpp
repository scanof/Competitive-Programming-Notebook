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

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

vi g[nax];
int match[nax];
int matchd[nax];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(20)<< fixed;
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>> n;
        for1(i,n){
            g[i].clear();
            match[i] = matchd[i] = 0;
        }
        int mat = 0;
        for1(i,n){
            int m;
            cin>> m;
            int num;
            while(m--){
                cin>> num;
                if(!match[num] && !matchd[i]){
                    matchd[i]= num;
                    match[num]= i;
                    mat++;
                }
                g[i].pb(num);
            }
        }
        if(mat== n){
            cout<< "OPTIMAL"<<el;
            continue;
        }
        int prin= 0;
        int da = 0;
        for(int i=n; i>=1; --i){
            if(!match[i] && !prin ){
                prin= i;
            }
            if(!matchd[i] && !da){
                da= i;
            }
        }
        cout<< "IMPROVE"<<el;
        cout<< da << " "<< prin<<el;


    }
}
