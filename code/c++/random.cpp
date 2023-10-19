// Declare random number generator
mt19937_64 rng(0); // 64 bit, seed = 0
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // 32 bit

// Use it to shuffle a vector
shuffle(all(vec), rng);

// Create int/real uniform dist. of type T in range [l, r]
uniform_int_distribution<T> / uniform_real_distribution<T> dis(l, r);
dis(rng); // generate a random number in [l, r]

int rd(int l, int r) { return uniform_int_distribution<int>(l, r)(rng);}