// Complexity O(N*2^N)
const int N;
int dp[1<<N][N+1];
int F[1<<N];
int A[1<<N];
// ith bit is ON S(mask, i) = S(mask, i-1)
// ith bit is OFF S(mask,i) = S(mask, i-1) + S(mask^(1<<i), i-1)
//iterative version
forn(mask,(1<<N)){
	dp[mask][0] = A[mask];	//handle base case separately (leaf states)
	forn(i,N){
		if(mask & (1<<i))
			dp[mask][i+1] = dp[mask][i] + dp[mask^(1<<i)][i];
		else
			dp[mask][i+1] = dp[mask][i];
	}
	F[mask] = dp[mask][N];
}
//memory optimized, super easy to code.
forn(i,(1<<N)) F[i] = A[i];
forn(i,N)
  forn(mask,(1<<N)){
    if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
  }
