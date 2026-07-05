class Solution {
public:

    void getPermu(vector<int>&nums, vector<vector<int>>&ans , int idx){
        int n = nums.size();
        if(idx == n){
            ans.push_back(nums);
            return;
        }

        for(int i = idx; i< n; i++){
            swap(nums[idx], nums[i]);
            getPermu(nums, ans, idx+1);
            swap(nums[idx], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        int idx = 0;
        getPermu(nums, ans, idx);
        return ans;
    }
};
