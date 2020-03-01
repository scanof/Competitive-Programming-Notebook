class Solution {
public:
    bool static compare(int a, int b){
        int b1 = 0, b2= 0;
        for(int i=0; i<32; ++i){
            if(a & (1<<i)) ++b1;
            if(b & (1<<i)) ++b2;
        }
        if(b1<b2) return true;
        else if(b1==b2) return a<b;
        return false;
    }
    
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), compare);
        return arr;
    }
};
