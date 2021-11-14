p3 vec_area2(vector<p3> &p){  ///normal vector to the surface
  p3 a = zero;
  forn(i, n)
    a = a + p[i]%p[(i+1)%sz(p)];
  return a;
}
ld area(vector<p3> &p){
  return abs(vec_area2(p))/2.0;
}

struct edge{
  int v;
  bool same;    ///:= is common edge in same order?
};

void reorient(vector<vector<p3>> &faces){ ///given a series of faces, make orientations (normal vec's) consistent
  int n = sz(faces);
  ///Find common edges + create adjacency graph
  vector<vector<edge>> g(n);
  map<pair<p3,p3>, int> es;
  forn(u, n){
    int m = sz(faces[u]);
    forn(i, m){
      p3 a = faces[u][i], b = faces[u][(i+1)%m];
      ///let's look at edge [a, b];
      if(es.count({a,b})){          ///seen in same order
        int v = es[{a,b}];
        g[u].pb({v, true});
        g[v].pb({u, true});
      } else if(es.count({b,a})){  ///seen in diff order
        int v = es[{b,a}];
        g[u].pb({v, false});
        g[v].pb({u, false});
      } else{                       ///not seen yet
        es[{a,b}] = u;
      }
    }
  }
  ///bfs to find which faces should be flipped
  vector<bool> seen(n, false), flip(n);
  flip[0] = false;
  queue<int> q;  q.push(0);
  while(sz(q)){
    int u = q.front();  q.pop();
    for(edge e: g[u]){
      if(seen[e.v]) continue;
      seen[e.v] = true;
      flip[e.v] = flip[u]^e.same; ///If the edge was in same order
      q.push(e.v);                ///one of the two should be flipped
    }
  }
  ///perform the flips
  forn(i, n){
    if(flip[i])
      reverse(all(faces[u]));
  }
}

ld volume(vector<vector<p3>> &faces){
  ld vol = 0;
  for(vector<p3> f: faces){
    vol += (vec_area2(f)*f[0]);
  }
  return abs(vol)/6.0;        ///could be <0 if normals point to inside
}
