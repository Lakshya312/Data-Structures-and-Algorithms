class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        m[0] = -1;
        int n = nums.size();
        int prefixSum = 0;

        for(int x = 0; x<n; x++){
            prefixSum += nums[x];
            int rem = prefixSum % k;
            if(m.find(rem) != m.end()){
                if(x - m[rem] >= 2){
                    return true;
                }
            }else{
                m[rem] = x;
            }
        }
        return false;
    }
};
