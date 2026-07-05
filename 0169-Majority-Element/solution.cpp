class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int freq = 1, ans = nums[0];
        int n = nums.size();
        for(int i = 1; i < n; i++){
            if(freq == 0){
                ans = nums[i];
            }
            if(nums[i] == ans){
                freq++;
            }else{
                freq--;
            }
        }

        int count = 0;
        for(int val : nums){
            if(val == ans){
                count++;
            }
        }

        if(count > (n/2)){
            return ans;
        }else{
            return -1;
        }

        return ans;
    }
};
