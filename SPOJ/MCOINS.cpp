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
const int MAXN = 1e6+20;

bool dp[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    int moves[3];
    moves[0]= 1;
    cin>> moves[1]>> moves[2];
    cin>> n;
    dp[0]= false;
    for1(i,MAXN-1){
        bool win= false;
        forn(j,3){
            if(i- moves[j]>=0 && dp[i-moves[j]]==false){
                win= true;
            }
        }
        dp[i]= win;
    }
    while(n--){
        int m;
        cin>> m;
        cout<< (dp[m] ? 'A' : 'B');
    }
    cout<<el;
}
