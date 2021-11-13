#define sz(c) ((int)c.size())
// asume que el dinic YA ESTA tirado
// asume que nodes-1 y nodes-2 son la fuente y destino
int match[maxnodes]; // match[v]=u si u-v esta en el matching, -1 si v no esta matcheado
int s[maxnodes]; // numero de la bfs del koning
queue<int> kq;
// s[e]%2==1  o si e esta en V1 y s[e]==-1-> lo agarras
void konig() {//O(n)
	forn(v,nodes-2) s[v] = match[v] = -1;
	forn(v,nodes-2)
        for(edge it: g[v])
            if (it.to < nodes-2 && it.f>0){
                match[v]=it.to; match[it.to]=v;
            }
	forn(v,nodes-2)
        if (match[v]==-1){
            s[v]=0;kq.push(v);
        }
	while(!kq.empty()) {
		int e = kq.front(); kq.pop();
		if (s[e]%2==1) {
			s[match[e]] = s[e]+1;
			kq.push(match[e]);
		} else {
			for(edge it: g[e])
                if (it.to < nodes-2 && s[it.to]==-1){
                    s[it->to] = s[e]+1;
                    kq.push(it->to);
                }
		}
	}
}
