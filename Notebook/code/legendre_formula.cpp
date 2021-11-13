// Complexity O(log_k (n))
// If k is prime
int fact_pow (int n, int k) {
  int x = 0;
  while(n) {
    n /= k; x += n;
  }
  return x;
}
// If k is composite k = k1^p1 * k2^p2 * ... * km^pm
// min 1..m   ai/ pi  where ai is fact_pow(n, ki)
