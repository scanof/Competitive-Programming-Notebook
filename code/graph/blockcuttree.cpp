struct edge {
	int u, v, comp; //A que componente biconexa pertenece
	bool bridge; //Si la arista es un puente
};

vector<int> g[nax]; //Lista de adyacencia
vector<edge> e; //Lista de aristas
stack<int> st;
int low[nax], num[nax], cont;
int art[nax]; //Si el nodo es un punto de articulacion
//vector<vector<int>> comps; //Componentes biconexas
//vector<vector<int>> tree; //Block cut tree
//vector<int> id; //Id del nodo en el block cut tree
int nbc; //Cantidad de componentes biconexas
int N, M; //Cantidad de nodos y aristas

void add_edge(int u, int v){
	g[u].pb(sz(e)); g[v].pb(sz(e));
	e.pb({u, v, -1, false});
}
void dfs(int u, int p = -1) {
	low[u] = num[u] = cont++;
	for (int i : g[u]) {
		edge &ed = e[i];
		int v = ed.u^ed.v^u;
		if(num[v]<0){
			st.push(i);
			dfs(v, i);
			if (low[v] > num[u]) ed.bridge = true; //bridge
			if (low[v] >= num[u]) {
				art[u]++; //articulation
				int last; //start biconnected
//				comps.pb({});
				do {
					last = st.top(); st.pop();
					e[last].comp = nbc;
//					comps.back().pb(e[last].u);
//					comps.back().pb(e[last].v);
				} while (last != i);
				nbc++; //end biconnected
			}
			low[u] = min(low[u], low[v]);
		} else if (i != p && num[v] < num[u]) {
			st.push(i);
			low[u] = min(low[u], num[v]);
		}
	}
}

void build_tree() {
	tree.clear(); id.resize(N); tree.reserve(2*N);
	forn(u,N)
		if (art[u]) id[u] = sz(tree); tree.pb({});
	for (auto &comp : comps) {
    sort(all(comp));
    comp.resize(unique(all(comp)) - comp.begin());
		int node = sz(tree);
		tree.pb({});
		for (int u : comp) {
			if (art[u]) {
				tree[id[u]].pb(node);
				tree[node].pb(id[u]);
			}else id[u] = node;
		}
	}
}
void doit() {
	cont = nbc = 0;
//	comps.clear();
	forn(i,N) {
		g[i].clear(); num[i] = -1; art[i] = 0;
	}
	forn(i,N){
    if(num[i]<0) dfs(i), --art[i];
	}
}
