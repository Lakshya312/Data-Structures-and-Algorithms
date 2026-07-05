class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int st = 0, ed = n - 1;

        if(n == 1){
            return nums[0];
        }

        while (st <= ed){
            int mid = st + (ed - st)/2;

            if(mid == 0 && (nums[mid] != nums[mid + 1])){
                return nums[mid];
            }

            if(mid == n-1 && (nums[mid] != nums[mid - 1])){
                return nums[mid];
            }

            if((nums[mid] != nums[mid - 1]) && (nums[mid] != nums[mid +1])){
                return nums[mid];
            }

            if(mid % 2 == 0){
                if (nums[mid-1] == nums[mid]){
                    ed = mid -1;
                }else{
                    st = mid + 1;
                }
            }else{
                if(nums[mid - 1] == nums[mid]){
                    st = mid + 1;
                }else{
                    ed = mid - 1;
                }
            }
        }
        return -1;
    }
};
