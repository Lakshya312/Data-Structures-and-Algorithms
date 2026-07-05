class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    vector<vector<int>>ans;

    for(int l = 0; l<n; l++){

        if(l > 0 && nums[l] == nums[l-1]) continue;

        for(int i=l+1;i <n; i++){

            if(i > l+1 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n - 1;
            while(j < k){
                long long sum = 1LL*nums[l] + nums[i] + nums[j] + nums[k];

                if(sum > target) k--;
                else if(sum < target) j++;
                else {//sum == target
                    ans.push_back({nums[l], nums[i], nums[j], nums[k]});
                    j++; k--;
                    while(j<k && nums[j] == nums[j-1]) j++;
                    while(j < k && nums[k] == nums[k+1]) k--;
                }
            }
        }
    }
    return ans;
}
};
