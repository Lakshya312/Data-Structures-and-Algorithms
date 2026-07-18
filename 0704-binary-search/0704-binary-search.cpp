class Solution {
public:

    int binarySearch(vector<int>nums, int tar, int st, int end){
        if(st <= end){

            int mid = st + (end - st)/2;
            if(nums[mid] == tar) return mid;

            else if(nums[mid] < tar){
                return binarySearch(nums, tar, mid + 1, end);
            }else{
                return binarySearch(nums, tar, st, mid - 1);
            }
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int st = 0 , end = nums.size() - 1;
        return binarySearch(nums, target, st, end);
    }
};