// Complejidad O(n^3)
int d[nax][nax];
void floyd(){
  // Hay que saber inicializar el array d.
  forn(k,n){
    forn(u,n){
      forn(v,n){
        d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
      }
    }
  }
}
