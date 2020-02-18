#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define per(i,a,b) for(int i=(b)-1;i>=(a);i--)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const double EPS= 1e-10;

vector<ii> pare;

struct state {
    int len, link;
    map<char, int> next;
//    int cnt = 1;
};
const int MAXN = 1<<21;
state st[MAXN];
bool seen[MAXN];
int sz, last;
int terminal[MAXN]; // ocurencias forma 1
int occ[MAXN]; // ocurrencias forma 1

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
//    st[0].cnt= 0;
    pare.reserve(MAXN);
    ++sz;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
//            st[clone].cnt= 0;
        }
    }
    last = cur;
}

string s, p, pp;
int t, n, m, l, r, v;
ll ans;
vector<int> cual;



void dfs(int v){ // ocurrencias forma 1
    if(occ[v] != 0) return;
    occ[v] = terminal[v];
    for(auto e:st[v].next){
        dfs(e.se);
        occ[v] += occ[e.se];
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>> s;
    sa_init();
    n= s.size();
    forn(i,n){
        sa_extend(s[i]);
    }
//    topogao();
    int v = last;
    while(v>0){  // ocurrencias forma 1
        terminal[v] = 1;
        v = st[v].link;
    }
    cin>> t;
    while(t--){
        cin>> p;
        m= p.size();
        forn(i,m){
            p+= p[i];
        }
        v = 0;
        ans = 0;
        l=0, r=0;
        while(r< p.size()){
            if(r-l==m){
                if(!seen[v]){
                    dfs(v);
                    ans+= occ[v];
                    cual.pb(v);
                    seen[v] = true;
                }
            }
            if(r-l<m && st[v].next.find(p[r])!= st[v].next.end()){
                v= st[v].next[p[r]];
                ++r;
            }else{
                if(l==r) break;
                ++l;
                if(st[st[v].link].len >= r-l) v = st[v].link;
            }
        }
        cout<< ans<<el;
        forn(i,cual.size()){
            seen[cual[i]] = false;
        }
        cual.clear();
    }
}
