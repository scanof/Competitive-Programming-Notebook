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

const int MAXS = 1e5+20; // Maxima cantidad de estados, |m1|+|m2|+..+|mp|
const int MAXC = 26; // Longitud del alfabeto

int sz; // cantidad de estados
string text;
int p;
string patterns[MAXS]; // Text, patterns
int cnt[MAXS], l[MAXS]; // for single pattern single wildcard matching

inline int convert(char ch) { // Function for properly index characters
    return ((ch >= 'a' && ch <= 'z') ? ch-'a' : ch-'A'+26);
}

struct state{
    int link=-1;
    vector<int> out;
    int next[MAXC];
    state(){
        forn(i,MAXC){
            next[i]=-1;
        }
    }
};
state st[MAXS];

void buildMatchingMachine(){
    forn(i,sz) st[i]= state();
    st[0].link=0;
    sz=1;
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
	}
    queue<int> q;
    for (int ch = 0; ch < MAXC; ++ch)
		if (st[0].next[ch] == -1){
			st[0].next[ch] = 0;
        }else{
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

int findNextState(int currState, char nextInput){
	int ans = currState;
	int ch = convert(nextInput);
	while (st[ans].next[ch] == -1)
		ans= st[ans].link;

	return st[ans].next[ch];
}

void searchWords(string text){
	buildMatchingMachine();
    int currState = 0, tmp;
	for (int i = 0; i < text.size(); ++i){
		currState = findNextState(currState, text[i]);
		for(int x : st[currState].out){
            tmp = i-((int)patterns[x].size())-l[x]+1;
            if (tmp >= 0) ++cnt[tmp];
        }
	}
}

int k, x, c;

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout<< setprecision(2)<< fixed;
	string pat;
	while(cin>> text>> pat){
        if (text.size() < pat.size()) {
            cout << '0' << el;
            continue;
        }
        for (k = 0, x = 0, p = 0; x < (int)pat.size(); ++x)
            if (pat[x] == '?') {
                if (x-k > 0) {
                    patterns[p] = pat.substr(k, x-k);
                    l[p++] = k;
                }
                k = x+1;
            }
        if (x-k > 0) {
            patterns[p] = pat.substr(k, x-k);
            l[p++] = k;
        }
        if(!p) cout << (text.size()-pat.size()+1) << el;
        else {
            forn(i, text.size()-pat.size()+1) cnt[i] = 0;
            searchWords(text);
            c = 0;
            forn(i, text.size()-pat.size()+1) if (cnt[i] == p) ++c;
            cout << c << el;
        }
    }
}
