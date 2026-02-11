#include "../template.h"

#pragma GCC optimize("O3")
//(UNCOMMENT WHEN HAVING LOTS OF RECURSIONS)\
#pragma comment(linker, "/stack:200000000")
//(UNCOMMENT WHEN NEEDED)
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

// Custom comparator for set/map
struct comp {
  bool operator()(const double& a, const double& b) const {
    return a+EPS<b;}
};
set<double,comp> w; // or map<double,int,comp>

// double inf
const double DINF=numeric_limits<double>::infinity();

int main() {
  // Ouput a specific number of digits past the decimal point,
  // in this case 5
  // #include <iomanip>
  cout << setfill(' ') << setw(3) << 2 << endl;

  cout.setf(ios::fixed); cout << setprecision(5);
  cout << 100.0/7.0 << endl;
  cout.unsetf(ios::fixed

  // Output the decimal point and trailing zeros
  cout.setf(ios::showpoint); cout << 100.0 << endl; cout.unsetf(ios::showpoint);

  // Output a + before positive values
  cout.setf(ios::showpos); cout << 100 << " " << -100 << endl; cout.unsetf(ios::showpos);

  // Output numerical values in hexadecimal
  cout << hex << 100 << " " << 1000 << " " << 10000 << dec << endl;
}
