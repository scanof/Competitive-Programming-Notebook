class Solution {
public:
    int findComplement(int num) {
        int bits = __builtin_popcount(num);
        int x = 0, i = 0;
        while(bits){
            if(num & (1<<i)) bits--;
            else x|= (1<<i);
            ++i;
        }
        return x;
    }
};
