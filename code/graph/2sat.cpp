// Complexity O(V+E)
int N;
vi low, num, comp, g[nax];
vector<bool> truth;
int scc, timer;
stack<int> st;
void tjn(int u) {
  low[u] = num[u] = timer++; st.push(u); int v;
  for(int v: g[u]) {
    if(num[v]==-1) tjn(v);
    if(comp[v]==-1) low[u] = min(low[u], low[v]);
  }
  if(low[u]==num[u]) {
    do{ v = st.top(); st.pop(); comp[v]=scc;
    }while(u != v);
    ++scc;
  }
}
bool solve_2SAT() {
  int n = 2*N;
  timer = scc= 0;
  num = low = comp = vi(n,-1);
  forn(i,n)
    if(num[i]==-1) tjn(i);
  truth = vector<bool>(N, false);
  forn(i,N) {
    if (comp[i] == comp[i + N]) return false;
    truth[i] = comp[i] < comp[i + N];
  }
  return true;
}
int neg(int x){
  if(x<N) return x+N;
  else return x-N;
}
void add_edge(int x, int y){
  g[x].pb(y);
}
void add_disjuntion(int x, int y){
  add_edge(neg(x), y);
  add_edge(neg(y), x);
}
void implies(int x, int y) {
  add_edge(x,y);
  add_edge(neg(y),neg(x));
}
void make_true(int u) { add_edge(neg(u), u); }
void make_false(int u) { make_true(neg(u)); }
void make_eq(int x, int y){
  implies(x, y);
  implies(y, x);
}
void make_dif(int x, int y){
  implies(neg(x), y);
  implies(neg(y), x);
}