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
    int terminal= 0;
    int occ[3];
    state(){
        forn(i,3) occ[i]=0;
    }
    char ch;
};

const int MAXN = 7e5;
state st[MAXN];
int sz, last;

void sa_init() {
    st[0] = state();
    st[0].len = 0;
    st[0].link = -1;
    ++sz;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur] = state();
    st[cur].ch= c;
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
            st[clone] = state();
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].ch = st[q].ch;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

const int mod = 1e9 +7;
bool seen[MAXN];

void dfs(int v){ // ocurrencias forma 1
    if(seen[v]) return ;
    seen[v]= true;
    for(auto e:st[v].next){
        if(e.fi<'a'){
            st[v].occ[e.fi-'#']=1;
        }else{
            dfs(e.se);
            forn(i,3) (st[v].occ[i] += st[e.se].occ[i]%mod)%=mod;
        }
    }
}

int lens[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    sa_init();
    int minlen= INT_MAX;
    forn(j,3){
        cin>> s;
        int n= s.size();
        minlen= min(minlen, n);
        forn(i,n) sa_extend(s[i]);
        sa_extend('#'+j);
        st[last].terminal= 1;
    }
    dfs(0);
    memset(lens, 0 ,sizeof lens);
    for1(i,sz-1){
        int res = (1LL*st[i].occ[0]*st[i].occ[1]*st[i].occ[2])%mod;
        lens[st[i].len]+= res%mod;
        lens[st[i].len]%=mod;
        lens[st[st[i].link].len]-= res%mod;
        lens[st[st[i].link].len]+= mod;
        lens[st[st[i].link].len]%=mod;
    }
    int sum=0;
    for(int i=minlen; i>=1; --i){
        sum= (sum+lens[i])%mod;
        lens[i]= sum;
    }
    for1(i,minlen){
        cout<< lens[i]%mod<< " ";
    }
    cout<<el;
}
