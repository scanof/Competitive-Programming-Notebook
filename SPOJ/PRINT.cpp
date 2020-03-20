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

// O(n)
// pr contains prime numbers
// lp[i] == 0 if i is prime
// else lp[i] is minimum prime factor of i
const int MAXN = 1e6+1;
int lp[MAXN+1];
vector<int> pr; // It can be sped up if change for an array

void sieve(int N){
    fore(i,2,N){
        if (lp[i] == 0) {
            lp[i] = i;
            pr.pb(i);
        }
        for (int j=0, mult= i*pr[j]; j<(int)pr.size() && pr[j]<=lp[i] && mult<=N; ++j, mult= i*pr[j])
            lp[mult] = pr[j];
    }
}
bool marked[MAXN];

void segment(int a, int b){
    memset(marked, false, sizeof marked);
    for(int j: pr){
        ll i= 1LL*j*j;
        if(i>b) break;
        if(i<a) i = (a/j)*j;
        for(;i<=b; i+=j){
            if(i-a<0) continue;
            marked[i-a]=true;
        }
    }
    for(int i= a; i<=b; ++i){
        if(!marked[i-a]){
            cout<< i<<el;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    sieve(MAXN);
    int t;
    cin>> t;
    int a, b;
    while(t--){
        cin>>a>>b;
        segment(a,b);
    }
}
