class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int>m;
        m[0] = 1;
        int prefixSum = 0;
        int count = 0;
        for(int j: nums){
            prefixSum += j;
            int rem = prefixSum % k;

            if(rem<0) rem+= k;

            if(m.find(rem) != m.end()){
                count += m[rem];
            }
            m[rem]++;
        }

        return count;
    }
};
