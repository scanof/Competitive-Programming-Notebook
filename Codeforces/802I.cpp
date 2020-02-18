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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;


struct state {
    int len, link;
    map<char, int> next;
};

const int MAXN = 1<<21;
state st[MAXN];
int sz, last;
int terminal[MAXN]; // ocurencias forma 1
int occ[MAXN]; // ocurrencias forma 1
//int words[MAXN]; // number of words occur

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
//    st[0].cnt= 0;
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
//            st[clone].cnt=0;
        }
    }
    last = cur;
}

void dfs(int v){ // ocurrencias forma 1
    if(occ[v] != 0) return;
    occ[v] = terminal[v];
    for(auto e:st[v].next){
        dfs(e.se);
        occ[v] += occ[e.se];
    }
}
vector<int> g[MAXN];

void calc(int v){
    if(terminal[v]!=0) return ;
    for(auto x: g[v]){
        if(x==0){
            terminal[v]+=1;
            continue;
        }
        if(terminal[x]==0){
            calc(x);
        }
        terminal[v]+= terminal[x];
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        forn(i,sz){
            st[i]= state();
            occ[i]= terminal[i]=0;
            g[i].clear();
        }
        sz=0;
        string s;
        cin>>s;
        sa_init();
        int n=s.size();
        forn(i,n){
            sa_extend(s[i]);
        }
        int v=last;
        while(v>0){
            terminal[v]=1;
            v= st[v].link;

        }
        dfs(0);
        v= -1;
        forn(i,sz){
            if(st[i].next.empty()){
                v= i;
            }
            for(auto x: st[i].next){
                g[x.se].pb(i);
            }
            terminal[i]=0;
        }
        calc(v);
        ll ans = 0;
        forn(i,sz){
            ans+= (1LL*terminal[i]*occ[i]*occ[i]);
        }
        cout<<ans<<el;
    }
}
