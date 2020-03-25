#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(ll i=1; i<= n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ll> vi;
const double PI = atan(1)*4;
const int nax = 2e5+10;
const double EPS = 1e-9;
int t, tam,ciclo,n,cur, pi,ans = INT_MAX, colIn;
int p[nax], col[nax];
bool seen[nax];


int dfs(int s, vector<int> &c, int ta, bool &sameC){
    if(seen[s]){
        return ta;
    }
    seen[s]=true;
    c.pb(col[s]);
    if(ta>=1){
        if(c[ta]!=c[ta-1]) sameC=false;
    }
    return dfs(p[s], c, ta+1, sameC);
}
bool found;

vector<int> div(int ciclo){
    double r = ceil(sqrt(ciclo));
    vector<int> ans;
    fore(i,2, r){
        if(ciclo%i==0){
            ans.pb(i);
            if(i!=(ciclo/i))ans.pb((ciclo/i));
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>>t;
    while(t--){
        ans =INT_MAX;
        cin>>n;
        forn(i,n){
            seen[i] = false;
            cin>>p[i];
            p[i]--;
        }
        forn(i,n) cin>>col[i];

        bool sameC;
        forn(i,n){
            vector<int> c;
            if(!seen[i]){
                sameC = true;
                ciclo = dfs(i, c, 0, sameC);
                ans = min(ans, ciclo);
                if(sameC) {
                    ans=1;
                    break;
                }
                vector<int> d = div(ciclo);
                forn(j,ciclo){
                    forn(k, d.size()){
                        if(j> d[k]) continue;
                        if(ans<=d[k]) break;
                        colIn = c[j];
                        forn(l, ciclo/d[k] + 1){
                            if(c[(j+l*d[k])%ciclo]!=colIn) break;
                            if(l==(ciclo/d[k]-1)) ans = min(ans,d[k]);
                        }
                    }
                }
            }
        }
        cout<<ans<<el;
    }
}
