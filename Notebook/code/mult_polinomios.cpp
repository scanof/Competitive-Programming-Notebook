int polinomioResultante [grado1 + grado2 + 1];

forn(c,grado1 + grado2 + 1)
  polinomioResultante[c] = 0;
forn(pos,grado1 + 1){
  forn(ter, grado2 + 1){
    polinomioResultante[pos + ter] += polinomio1[pos] * polinomio2[ter];
  }
}
