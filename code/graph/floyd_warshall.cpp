// Complejidad O(n^3)
int dist[nax][nax];
void floyd(){
  // Hay que saber inicializar el array d.
  forn(k,n){
    forn(u,n){
      forn(v,n){
        dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
      }
    }
  }
}
