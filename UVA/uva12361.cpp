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

inline int convert(char ch){
    if( ch<'a'){
        return ch-'#'+26;
    }else return ch-'a';
}

struct state {
    int len, link;
    int terminal = 1;
    int next[26+60];
    state(){
        forn(i,26+60) next[i]=-2;
    }
    int cnt = 0; // ocurrencias forma
    set<int> good;
};

const int MAXN = 2e6+500;
state st[MAXN];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].cnt= 0;
    ++sz;
    last = 0;
}

void sa_extend(int c) {
    int cur = sz++;
    st[cur]= state();
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && st[p].next[c]==-2) {
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
            st[clone]= state();
            st[clone].len = st[p].len + 1;
            forn(i,26+60 )st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
            st[clone].cnt=0;
        }
    }
    last = cur;
}

void dfs(int v){ // ocurrencias forma 1
    if(st[v].cnt != 0) return;
    st[v].cnt = st[v].terminal;
    forn(i,26+60){
        int next = st[v].next[i];
        if(next!=-2){
            if(i<26){
                dfs(next);
                st[v].cnt+= st[next].cnt;
                for(int num: st[next].good){
                    st[v].good.insert(num);
                }
            }else{
                st[v].good.insert(i-26);
            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    int q;
    while(cin>> q){
        if(q==0) return 0;
        sz=0;
        st[0]= state();
        sa_init();
        forn(i,q){
            cin>> s;
            forn(j,s.size()){
                sa_extend(convert(s[j]) );
            }
            sa_extend(convert('#'+i) );
        }

        int v = last;
        while(v>0){  // ocurrencias forma 1
            st[v].terminal = 1;
            v = st[v].link;
        }
        dfs(0);
        set<set<int>> cant;
        for1(j,sz-1){
            cant.insert(st[j].good);
        }
        cout<<cant.size()-1<<el;

    }
}
