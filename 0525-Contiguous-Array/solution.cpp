class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int>m;
        m[0] = -1;
        int n = nums.size();
        int prefixSum = 0;
        int length = 0;
        for(int j=0; j<n ;j++){
            prefixSum += nums[j] == 0 ? -1:1;

            if(m.find(prefixSum) != m.end()){
                int l = j - m[prefixSum];
                length = max(l, length);
            }else{
                m[prefixSum] = j;
            }
        }

        return length;
        
    }
};
