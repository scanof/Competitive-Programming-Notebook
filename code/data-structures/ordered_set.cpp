#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set; 
// Para multiset cambiar less<int> por less_equal<int>
// METHODS
tree.find_by_order(k) // returns pointer to the k-th smallest element
tree.order_of_key(x)  // returns how many elements are smaller than x
tree.find_by_order(k) == tree.end() // true, if element does not exist
