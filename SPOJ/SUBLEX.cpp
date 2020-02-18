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
ll words[MAXN];
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
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
        }
    }
    last = cur;
}


void dfs(int v){ // ocurrencias forma 1
    if(occ[v] != 0) return;
    occ[v] = words[v]= terminal[v];
    for(auto e:st[v].next){
        dfs(e.se);
        occ[v] += occ[e.se];
        words[v] += words[e.se] + occ[e.se];
    }
    words[v] -= occ[v]-1;
}

// OCURRENCIAS FORMA 2
//int cnt[MAXN],id[MAXN];
//void bucketsort() {
//	memset(cnt,0,sizeof(cnt));
//	for1(i,sz) ++cnt[st[i].len];
//    for1(i,sz) cnt[i] += cnt[i-1];
//	for1(i,sz) id[cnt[st[i].len]--] = i;
//}
//void topogao() {
//	bucketsort();
//	fored(i,1,sz){
//		int u = id[i],link = st[u].link;
//		st[link].cnt += st[u].cnt;
//	}
//}
////

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    cin>> s;
    sa_init();
    ll n= s.size();
    forn(i, n) sa_extend(s[i] );
    int v = last;
    while(v>0){  // ocurrencias forma 1
        terminal[v] = 1;
        v = st[v].link;
    }
    dfs(0);
    int t;
    cin>> t;
    ll k;
    ll distinct= words[0];
    while(t--){
        cin>> k;
        if(k>=distinct) continue;
        int v= 0;
        while(k>0){
            ll acc = 0;
            for(auto x: st[v].next){
                ll temp= acc;
                acc+= words[x.se];
                if(k<=acc){
                    k-= temp + 1;
                    cout<< x.fi;
                    v= x.se;
                    break;
                }
            }
        }
        cout<<el;
    }
}
