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
typedef pair<string,int> psi;

const int MAXS = 2e6+20; // Maxima cantidad de estados, |m1|+|m2|+..+|mp|
const int MAXC = 26; // Longitud del alfabeto

int f[MAXS]; // funcion de fallo
int g[MAXS][MAXC]; // transiciones
int cantNodos=1; // cantidad de e   stados
int out[MAXS];
int p;
queue<psi> qs;
vector<string> patterns;
string t;
inline int convert(char ch) { // Function for properly index characters
    return ((ch >= 'a' && ch <= 'z') ? ch-'a' : ch-'A'+26);
}

inline void buildMatchingMachine(){
	memset(g, -1, sizeof g);
	for(int i=0; i<MAXS; i++) out[i] = INT_MAX;
	memset(f, -1, sizeof f);
	f[0]=0;
	int &states = cantNodos;
	for (int i = 0; i < p; ++i){ // Trie
		const string &word = patterns[i];
		int currState = 0;
		for (int j = 0; j < word.size(); ++j){
			int ch = convert(word[j]);
			if (g[currState][ch] == -1)
				g[currState][ch] = states++;
			currState = g[currState][ch];
		}
		out[currState] = min(out[currState],i);
	}
	for (int ch = 0; ch < MAXC; ++ch)
		if (g[0][ch] == -1)
			g[0][ch] = 0;
	queue<int> q;
	for (int ch = 0; ch < MAXC; ++ch){
		if (g[0][ch] != 0){
			f[g[0][ch]] = 0;
			q.push(g[0][ch]);
		}
	}
	while (!q.empty()){
		int state = q.front();
		q.pop();
		for (int ch = 0; ch < MAXC; ++ch){
			if (g[state][ch] != -1) {
				int fail = f[state];
				while (g[fail][ch] == -1)
					fail = f[fail];
				fail = g[fail][ch];
				f[g[state][ch]] = fail;
				out[g[state][ch]] = min(out[g[state][ch]], out[fail]);
				q.push(g[state][ch]);
			}
		}
	}
}

inline int findNextState(int currState, char nextInput){
	int ans = currState;
	int ch = convert(nextInput);

	while (g[ans][ch] == -1)
		ans= f[ans];

	return g[ans][ch];
}

inline void searchWords(){
	buildMatchingMachine();
	while(!qs.empty()){
		t= qs.front().fi;
		p= qs.front().se;
		qs.pop();

		int currState = 0;
		for (int i = 0; i < t.size() && p!=-1; ++i){
			currState = findNextState(currState, t[i]);
			if(out[currState]<p){
				cout<< "YES\n";
				p=-1;
			}
		}
		if(p!=-1){
			cout<< "NO\n";
		}
	}
}



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin>> n;
	patterns.reserve(n);
	while(n--){
		int op;
		cin>> op;
		if(op==0){
			cin>> t;
			patterns.pb(t);
			p++;
		}else{
			cin>> t;
			qs.push(psi(t,p));
		}
	}
	searchWords();
	return 0;
}
