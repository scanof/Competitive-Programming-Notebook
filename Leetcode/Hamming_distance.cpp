class Solution {
public:
    int hammingDistance(int x, int y) {
        x^=y;
        return __builtin_popcount(x);
    }
};
