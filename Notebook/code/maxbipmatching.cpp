// O (V*E)
vi g[nax], seen, match;
int Aug(int l) {                 // return 1 if an augmenting path is found
  if (seen[l]) return 0;      // return 0 otherwise
  seen[l] = 1;
  for (int r: g[l])
    if (match[r] == -1 || Aug(match[r])){
      match[r] = l; return 1;                           // found 1 matching
    }
  return 0;                                                  // no matching
}

int MCBM(int n, int vleft){
  int ans = 0;
  match.assign(n, -1);    // V is the number of vertices in bipartite graph
  forn(l,vleft) {         // vleft : vi with indices of vertices
    seen.assign(n, 0);                    // reset before each recursion
    ans += Aug(l);
  }
  return ans;
}
