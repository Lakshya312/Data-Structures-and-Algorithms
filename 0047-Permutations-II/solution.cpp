class Solution {
public:

    void getPermu(vector<int>&nums, vector<vector<int>>&ans , int idx){
        int n = nums.size();
        if(idx == n){
            ans.push_back(nums);
            return;
        }

        unordered_set<int>used;

        for(int i = idx ; i< n; i++){

            if (used.count(nums[i])) continue;
            used.insert(nums[i]);

            swap(nums[i], nums[idx]);
            getPermu(nums, ans, idx + 1);
            swap(nums[i], nums[idx]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        int idx = 0;
        sort(nums.begin(), nums.end());
        getPermu(nums, ans, idx);
        return ans;
    }
};
