class Solution {
public:
    
    vector<vector<int>> a;
    int tam = 0;
    void dfs(vector<int> b, vector<int> s){
        if(b.size()==tam){
            a.push_back(b);
            return ;
        }
        int n= s.size();
        for(int i= 0; i<n; ++i){
            vector<int> x = b;
            x.push_back(s[i]);
            vector<int> y = s;
            y.erase(find(y.begin(),y.end(),s[i]));
            dfs(x, y);
        }
    }
    
    
    vector<vector<int>> permute(vector<int>& nums) {
        tam = nums.size();
        vector<int> b;
        dfs(b, nums);
        return a;
    }
    
};
