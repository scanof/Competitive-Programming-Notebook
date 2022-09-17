int ans[grado1+grado2+1];

forn(c,grado1+grado2+1) ans[c] = 0;
forn(pos,grado1+1){
  forn(ter,grado2+1)
    ans[pos + ter] += pol1[pos] * pol2[ter];
}
