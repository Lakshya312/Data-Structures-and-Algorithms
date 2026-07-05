class Solution {
public:
    void getAllSubsets(vector<int>&arr, vector<int> &ans, int i, vector<vector<int>>&allSubsets){
    if(i == arr.size()){
        allSubsets.push_back({ans});
        return;
    }

    //inclusion
    ans.push_back(arr[i]);
    getAllSubsets(arr, ans, i + 1, allSubsets);

    ans.pop_back(); // backtracking
    //exclusion
    int next = i + 1;
    while (next < arr.size() && arr[next] == arr[i]) {
        next++;
    }
    getAllSubsets(arr, ans, next, allSubsets); 
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> allSubsets;
        vector<int>ans;
        getAllSubsets(nums, ans, 0, allSubsets);

        return allSubsets;
    }
};
