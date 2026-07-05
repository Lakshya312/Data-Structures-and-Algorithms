class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];

        do{
            slow = nums[slow];//+1
            fast = nums[nums[fast]];//+2
        }while(slow != fast);

        slow = nums[0];

        while(slow != fast){
            slow = nums[slow]; // +1
            fast = nums[fast];// +1
        }

        return slow; //or return fast
    }
};
