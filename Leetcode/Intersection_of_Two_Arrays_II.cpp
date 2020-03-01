class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mapa;
        for(int i= 0; i<nums1.size(); ++i){
            mapa[nums1[i]]++;
        }
        vector<int> a;
        a.reserve(nums2.size());
        for(int i= 0; i<nums2.size(); ++i){
            if(mapa[nums2[i]]>0){
                a.push_back(nums2[i]);
                mapa[nums2[i]]--;
            }
        }
        return a;
    }
};
