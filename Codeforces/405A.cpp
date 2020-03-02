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
const int MAXN = 2e5+200;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n;
    cin>> n;
    int a[101][101];
    int arr[n];
    memset(a, 0, sizeof a);
    forn(i,n) cin>> arr[i];
    int m= 0;
    forn(i,n){
        int sz = arr[i];
        m= max(m, sz);
        for1(j,sz){
            a[i][j]=1;
        }
    }
    int b[101][101];
    memset(b, 0, sizeof b);

    for1(j,m){
        int sum = 0;
        forn(i,n){
            sum+= a[i][j];
            b[i][j]= sum;
        }
    }
    int i = n-1;
    for(int j= m; j>=1; --j){
        b[n-1][j]-= (n- (i+1));
        while(b[n-1][j]--){
            arr[i--] = j;
        }
    }
    forn(i,n){
        cout<< arr[i]<< " ";
    }
    cout<<el;
}

