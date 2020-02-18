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

const int MAXN = 6e5+100;
const int P = 40020; // Maxima cantidad de estados, |m1|+|m2|+..+|mp|
const int MAXC = 26; // Longitud del alfabeto

int sz;
string t;
int p;
string patterns[P];
int lastnodes[P];


inline int convert(char ch) { // Function for properly index characters
    return ((ch >= 'a' && ch <= 'z') ? ch-'a' : ch-'A'+26);
}

struct state{
    int link=-1;
    vector<int> out;
    int next[MAXC];
    state(){
        forn(i,MAXC) next[i]=-1;
    }
};
state st[MAXN];

void buildMatchingMachine(){
    forn(i,sz) st[i]= state();
    st[0].link=0;  sz=1;
    for (int i = 0; i < p; ++i){ // Trie
		const string &word = patterns[i];
		int cur = 0;
        for (int j = 0; j < word.size(); ++j){
			int ch = convert(word[j]);
			if (st[cur].next[ch] == -1)
				st[cur].next[ch]= sz++;
			cur = st[cur].next[ch];
		}
		st[cur].out.pb(i);
        lastnodes[i]= cur;
	}
    queue<int> q;
    for (int ch = 0; ch < MAXC; ++ch)
		if (st[0].next[ch] == -1)  st[0].next[ch] = 0;
        else{
            st[st[0].next[ch]].link = 0;
			q.push(st[0].next[ch]);
		}
    while (!q.empty()){
		int state = q.front();
		q.pop();
        for (int ch = 0; ch < MAXC; ++ch){
			if (st[state].next[ch] != -1) {
                int fail = st[state].link;
                while (st[fail].next[ch] == -1)
                      fail = st[fail].link;
                fail = st[fail].next[ch];
                int next = st[state].next[ch];
                st[next].link= fail;
                for( int a: st[fail].out){
                    st[next].out.pb(a);
                }
                q.push(next);
            }
		}
	}
}

int findNextState(int cur, int ch){
	int ans = cur;
	while (st[ans].next[ch] == -1)
		ans= st[ans].link;
	return st[ans].next[ch];
}


int bit[MAXN];

void update(int idx, int v){
    while(idx< MAXN){
        bit[idx]+= v;
        idx+= idx & (-idx);
    }
}
int query(int idx){
    int ans = 0;
    while(idx > 0){
        ans += bit[idx];
        idx -= idx & (-idx);
    }
    return ans;
}

vector<int> edg[MAXN];
int ent[MAXN] , sal[MAXN];

int cnt;
void dfs(int u){
    ent[u]= ++cnt;
    for(int v: edg[u]) dfs(v);
    sal[u]= cnt;
}



int main(){
    cin>> t;
    cin>>p;
    int a,b;
    cin>> a>> b;
    forn(i,p){
        cin>> patterns[i];
    }
    buildMatchingMachine();
    for(int i=1; i< sz; ++i){
        edg[st[i].link].pb(i);
    }
    dfs(0);
    int u= 0;
    for(char c : t){
        u = findNextState(u,convert(c));
        update(ent[u],1);
    }
    forn(i,p){
        int v= lastnodes[i];
        int ans = query(sal[v])-query(ent[v]-1);
        cout<< ans<<el;
        int ch = (a*ans + b)%26;
        u = findNextState(u,ch);
        update(ent[u],1);
    }

}
