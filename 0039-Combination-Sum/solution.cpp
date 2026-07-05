class Solution {
public:
    void solve(vector<int>& array, int i, vector<int>& combine, vector<vector<int>>& ans, int tar){

        int n = array.size();

        // base case
        if(tar == 0){
            ans.push_back(combine);
            return;
        }

        // stop condition
        if(i == n || tar < 0){
            return;
        }

        // TAKE (reuse allowed)
        combine.push_back(array[i]);

        solve(array, i, combine, ans, tar - array[i]);

        // BACKTRACK
        combine.pop_back();

        // SKIP
        solve(array, i + 1, combine, ans, tar);
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;

        solve(candidates, 0, combine, ans, target);

        return ans;
    }
};
