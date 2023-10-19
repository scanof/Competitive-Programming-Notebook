// https://leetcode.com/problems/min-cost-to-connect-all-points

#define all(v) v.begin(), v.end()
#define sz(v) int(v.size())

typedef vector<int> vi;

class Solution {
public:
  struct dsu{
    vi p, r; int comp;
    dsu(int n): p(n), r(n, 1), comp(n){iota(all(p), 0);}
    int find_set(int i){return p[i] == i ? i : p[i] = find_set(p[i]);}
    bool is_same_set(int i, int j){return find_set(i) == find_set(j);}
    void union_set(int i, int j){
      if((i = find_set(i)) == (j = find_set(j))) return;
      if(r[i] > r[j]) swap(i, j);
      r[j] += r[i];  r[i] = 0;
      p[i] = j;  --comp;
    }
  };

  struct edge{
    int u, v, w;
    edge(int u, int v, int w): u(u), v(v), w(w){}
    bool operator < (const edge &o) const{ return w < o.w;}
  };
  vector<edge> g;

  int kruskal(int n){
    sort(all(g));  dsu uf(n); 
    int ans = 0;
    for(auto&[u, v, w]: g){
      if(!uf.is_same_set(u, v)){
        uf.union_set(u, v);
        ans += w;
      }
    }
    return ans;
  }

  int dist(vi& p1, vi& p2){return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);}
  
  int minCostConnectPoints(vector<vi>& points) {
    for(int i = 0; i < sz(points); ++i)
      for(int j = i+1; j < sz(points); ++j)
        g.push_back({i, j, dist(points[i], points[j])});
    return kruskal(sz(points));
  }
};