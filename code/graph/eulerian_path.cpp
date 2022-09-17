int n;
int edges = 0;
int out[nax], in[nax];

// Directed version (uncomment commented code for undirected)
struct edge {
	int v;
//	list<edge>::iterator rev;
	edge(int v):v(v){}
};
list<edge> g[nax];
void add_edge(int a, int b){
  out[a]++;
  in[b]++;
	++edges;
	g[a].push_front(edge(b));//auto ia=g[a].begin();
//	g[b].push_front(edge(a));auto ib=g[b].begin();
//	ia->rev=ib;ib->rev=ia;
}
vi p;
void go(int u){
	while(sz(g[u])){
		int v=g[u].front().v;
		//g[v].erase(g[u].front().rev);
		g[u].pop_front();
		go(v);
	}
	p.push_back(u);
}

vi get_path(int u){   
	p.clear();
	go(u);
	reverse(all(p));
	return p;
}

/// for undirected uncomment and check for path existance
bool eulerian(vi &tour) { /// directed graph
  int one_in = 0, one_out = 0, start = -1;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    if(out[i] && start == -1) start = i;
    if(out[i] - in[i] == 1) one_out++, start = i;
    else if(in[i] - out[i] == 1) one_in++;
    else ok &= in[i] == out[i];
  }
  ok &= one_in == one_out && one_in <= 1;
  if (ok) {
    tour = get_path(start);
    if(sz(tour) == edges + 1) return true;
  }
  return false;
}