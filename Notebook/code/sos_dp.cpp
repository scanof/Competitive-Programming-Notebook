// Complexity O(N*2^N)
const int N;
int dp[1<<N][N+1];
int F[1<<N];
int A[1<<N];
// ith bit is ON S(mask, i) = S(mask, i-1)
// ith bit is OFF S(mask,i) = S(mask, i-1) + S(mask^(1<<i), i-1)
//iterative version
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][0] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i+1] = dp[mask][i] + dp[mask^(1<<i)][i];
		else
			dp[mask][i+1] = dp[mask][i];
	}
	F[mask] = dp[mask][N];
}
//memory optimized, super easy to code.
for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i)
  for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i))
      F[mask] += F[mask^(1<<i)];
  }
