class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        //find the pivot
        int piv = -1;
        for(int i = n-2; i >=0; i--){
            if(nums[i] < nums[i+1]){
                piv = i;
                break;
            }
        }

        if(piv == -1){
            reverse(nums.begin(), nums.end());
            return;
        }

        //next larger element
        for(int i = n-1; i >piv; i--){
            if(nums[i] > nums[piv]){
                swap(nums[i], nums[piv]);
                break;
            }
        }
        //reverse the rest of the part of the arrary
        // reverse(nums.begin() + piv + 1, nums.end());

        int st = piv + 1, e = n - 1;
        while(st <= e){
            swap(nums[st], nums[e]);
            st ++; e--;
        }

    }
};
