class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int,int>m;
        m[0] = 1;
        int prefixSum = 0;
        int count = 0;
        for(int x:nums){
            prefixSum += x;
            int diff = prefixSum - goal;

            if(m.find(diff) != m.end()){
                count += m[diff];
            }

            m[prefixSum]++;
        }
        return count;
    }
};
