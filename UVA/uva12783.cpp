#include <bits/stdc++.h>

#define forn(i,n) for(int i= 0; i<n; ++i)
#define for1(i,n) for(int i= 1; i<=n; ++i)
#define fore(i,l,r) for(int i= l; i<=r; ++i)
#define pb push_back
#define el '\n';
#define d(x) cout<< #x<< " "<< x<< el;

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;


vi g[1001];
bool seen[1001];
int timer, num[1001], low[1001];
vector<ii> ans;
void tarjan(int v, int p) {
    seen[v] = true;
    num[v] = low[v] = timer++;
    int children=0;
    for(int to: g[v]) {
        if(to == p) continue;
        if(seen[to]) {
            low[v] = min(low[v], num[to]);
        } else {
            tarjan(to, v);
            low[v] = min(low[v], low[to]);
            if(low[to] > num[v])
                ans.push_back(ii(min(v, to),max(v, to) ));
        }
    }
}




int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    while(n!=0 && m!=0) {
        timer  = 0;
        memset(seen, false, sizeof seen);
        memset(low, -1, sizeof low);
        memset(num, -1, sizeof num);
        int src, dst;

        forn(i, m) {
            cin >> src >> dst;
            g[src].push_back(dst);
            g[dst].pb(src);
        }


        forn(i, n) {
            if(!seen[i])
                tarjan(0, -1);
        }
        cout << ans.size();
        sort(ans.begin(), ans.end());
        for(ii a: ans) {
            cout << " "<<a.first << " " << a.second;
        }
        cout << endl;
        ans.clear();
        forn(i,n) g[i].clear();
        cin >> n >> m;

    }
}




