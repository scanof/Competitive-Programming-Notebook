// https://www.spoj.com/problems/DYNACON1/
#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'

struct Node { // Splay tree. Root's pp contains tree's parent.
  Node *p = 0, *pp = 0, *c[2] = {0, 0};
  bool flip = 0;
  Node(){}
  void fix() { forn(i, 2) if(c[i]) c[i]->p = this; }
  inline int up() { return p ? p->c[1] == this : -1; }
  void push() {
    if (!flip) return;
    flip = 0,  swap(c[0], c[1]);
    forn(i, 2) if(c[i]) c[i]->flip ^= 1;
  }
  void rot(int i, int b) {
    int h = i ^ b;
    Node *x = c[i],  *y = b == 2 ? x : x->c[h],  *z = b ? y : x;
    if ((y->p = p)) p->c[up()] = y;
    c[i] = z->c[i^1];
    if(b < 2) x->c[h] = y->c[h^1],  z->c[h^1] = b ? x : this;
    y->c[i^1] = b ? this : x;
    fix(),  x->fix(),  y->fix();
    if(p) p->fix();
    swap(pp, y->pp);
  }
  void splay() { // Splay *this up to the root. Finishes without flip set.
    for(push(); p; ) {
      if(p->p) p->p->push();
      p->push(),  push();
      int c1 = up(),  c2 = p->up();
      if(c2 == -1) p->rot(c1, 2);
      else p->p->rot(c2, c1 != c2);
    }
  }
  Node* first() { return push(), c[0] ? c[0]->first() : (splay(), this); }
}; // Return the MIN of the subtree rooted at this, splayed to the top.
 
struct LinkCut {
  vector<Node> node;
  LinkCut(int n) : node(n) {}
  Node* get(Node* u) { /// Move u to root aux tree. 
    u->splay();
    while (Node* pp = u->pp) {
      pp->splay(),  u->pp = 0;
      if(pp->c[1]) pp->c[1]->p = 0,  pp->c[1]->pp = pp;
      pp->c[1] = u,  pp->fix(),  u = pp;
    }
    return u;  // Return the root of the root aux tree.
  }
  bool connected(int u, int v) { // are u, v in the same tree?
    return get(&node[u])->first() == get(&node[v])->first(); 
  }
  void link(int u, int v) { // add an edge (u, v)
    assert(!connected(u, v)),  makeRoot(&node[u]),  node[u].pp = &node[v];
  }
  void cut(int u, int v) { // remove an edge (u, v)
    Node *x = &node[u], *top = &node[v];
    makeRoot(top),  x->splay(),  assert(top == (x->pp ? : x->c[0]));
    if(x->pp) x->pp = 0;
    else x->c[0] = top->p = 0,  x->fix();
  }  
  void makeRoot(Node* u) { /// Move u to root of represented tree.
    get(u),  u->splay();
    if(u->c[0]) {
      u->c[0]->p = 0;
      u->c[0]->flip ^= 1;
      u->c[0]->pp = u;
      u->c[0] = 0,  u->fix();
    }
  }
};

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  LinkCut lc(n);
  forn(_, q){
    string t; cin >> t;
    int u, v; cin >> u >> v; --u, --v;
    if(t == "add") lc.link(u, v);
    else if(t == "rem") lc.cut(u, v);
    else cout << (lc.connected(u, v) ? "YES" : "NO") << el;
  }
}