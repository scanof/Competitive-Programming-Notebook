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
    string s;
    cin>> n>> s;
    bool marked[n];

    memset(marked, false, sizeof marked);
    forn(i,n){
        if(s[i]=='.') continue;
        if(s[i]=='L'){
            int j= i-1;
            marked[i]= true;
            while(j>=0 && !marked[j]){
                marked[j]=true;
                j--;
            }
            continue;
        }
        if(s[i]=='R'){
            int j= i+1;
            marked[i]= true;
            while(j<n && !marked[j]){
                if(s[j]=='L'){
                    if((j-i+1)%2==0) marked[j]= true;
                    i= j;
                    break;
                }
                marked[j++]= true;
            }
        }
    }
    int ans = 0;
    forn(i,n){
        ans+= (!marked[i]);
    }
    cout<< ans<<el;
}

