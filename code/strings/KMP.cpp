vi get_phi(string &s) { // O(|s|)
  int j = 0, n = sz(s); vi pi(n);
  for1(i,n-1){
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    j += (s[i] == s[j]);
    pi[i] = j;
  }
  return pi;
}
void kmp(string &t, string &p){ // O(|t| + |p|)
  vi phi = get_phi(p);
  int matches = 0;
  for(int i = 0, j = 0; i < sz(t); ++i ) {
    while(j > 0 && t[i] != p[j] ) j = phi[j-1];
    if(t[i] == p[j]) ++j;
    if(j == sz(p)) {
      matches++;
      j = phi[j-1];
    }
  }
}
/// Automaton
/// Complexity O(n*C) where C is the size of the alphabet
int aut[nax][26];
void kmp_aut(string &p) {
  int n = sz(p);
  vi phi = get_phi(p);
  forn(i, n+1) {
    forn(c, 26) {
      if (i==n || (i>0 && 'a'+c!= p[i])) aut[i][c] = aut[phi[i-1]][c];
      else  aut[i][c] = i + ('a'+c == p[i]);
    }
  }
}

/// Automaton
int wh[nax+2][MAXC];	//wh[i][j] = a donde vuelvo si estoy en i y pongo una j
void build(string &s){
	int lps=0;
	wh[0][s[0]-'a'] = 1;
	fore(i,1,sz(s)){
		fore(j,0,MAXC-1) wh[i][j]=wh[lps][j];
		if(i<sz(s)){
			wh[i][s[i]-'a'] = i+1;
			lps = wh[lps][s[i]-'a'];
		}
	}
}
