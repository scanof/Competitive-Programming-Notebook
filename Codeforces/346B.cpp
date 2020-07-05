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
#define ri(n) scanf("%d",&n)
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int inf = 1e9;

string s, t, v;
int n,m, K;
const int nax = 102;

vector<int> get_phi(string &p) {
  int j = 0, n = (int)p.size();
  vi phi(n);
  for1(i,n-1){
    while (j > 0 && p[i] != p[j]) j = phi[j-1];
    if (p[i] == p[j]) ++j;
    phi[i] = j;
  }
  return phi;
}

int aut[nax][26];
void kmp_automaton(string &p) {
  int n = p.size()+1;
  vector<int> phi = get_phi(p);
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'A' + c != p[i]) aut[i][c] = aut[phi[i-1]][c];
      else  aut[i][c] = i + ('A' + c == p[i]);
    }
  }
}



int dp[nax][nax][nax];

int go(int i, int j, int k){
  if(k == K) return -inf;
  if(i==n || j==m){
    return 0;
  }
  int &r= dp[i][j][k];
  if(r!=-1) return r;
  r = -inf;
  if(s[i]==t[j]){
    r = max(r, 1+go(i+1,j+1,aut[k][s[i]-'A']));
  }
  r = max(r, go(i, j+1, k));
  r = max(r, go(i+1, j, k));
  return r;
}

string ans;

void build(int i, int j, int k){
  if(k == K) return ;
  if(i==n || j==m){
    cout<< ans<<el;
    return ;
  }
  int &r= dp[i][j][k];

  if(s[i]==t[j]){
    if(r==1+go(i+1,j+1,aut[k][s[i]-'A'])){
      ans.pb(s[i]);
      build(i+1,j+1,aut[k][s[i]-'A']);
      return ;
    }
  }
  if(r==go(i, j+1, k)){
    build(i, j+1, k);
    return ;
  }
  build(i+1, j, k);
  return ;
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cin>> s>> t>> v;
  n= s.size(), m = t.size();
  K = v.size();
  kmp_automaton(v);
  memset(dp, -1, sizeof dp);
  if(go(0,0,0)==0){
    cout<< 0<<el;
    return 0;
  }
  ans = "";
  build(0,0,0);
}
