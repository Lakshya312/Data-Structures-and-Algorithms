class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int>m;
        m[0] = 1; // for index -1 and when prefixsum == k
        int prefixSum = 0;
        int count = 0;
        for(int j: nums){
            prefixSum += j;
            int value = prefixSum - k;

            if(m.find(value) != m.end()){
                count += m[value];
            }

            m[prefixSum] ++;
        }

        return count;
    }
};
