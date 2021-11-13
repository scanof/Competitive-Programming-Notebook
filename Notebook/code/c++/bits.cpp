mask |= (1<<n) // PRENDER BIT-N
mask ^= (1<<n) // FLIPPEAR BIT-N
mask &= ~(1<<n) // APAGAR BIT-N
if(mask&(1<<n)) // CHECKEAR BIT-N
T = mask&(-mask); // LSO
__builtin_ffs(mask); // INDICE DEL LSO
//  iterar sobre los subconjuntos del conjunto S
for(int subset= S; subset; subset= (subset-1) & S)
for (int subset=0;subset=subset-S&S;) 	 // Increasing order
