class Solution {
public:
    void merge(vector<int>& nums, int mid, int st, int end) {
        vector<int> temp;
        int i = st;
        int j = mid + 1;
        while (i <= mid && j <= end) {
            if (nums[i] < nums[j]) {
                temp.push_back(nums[i]);
                i++;
            } else {
                temp.push_back(nums[j]);
                j++;
            }
        }

        while (i <= mid) {
            temp.push_back(nums[i]);
            i++;
        }

        while (j <= end) {
            temp.push_back(nums[j]);
            j++;
        }

        for (int idx = 0; idx < temp.size(); idx++) {
            nums[idx + st] = temp[idx];
        }
    }

    void mergesort(vector<int>& nums, int st, int end) {
        if (st < end) {
            int mid = st + (end - st) / 2;
            // Left Part
            mergesort(nums, st, mid);

            // Right Part
            mergesort(nums, mid + 1, end);

            // sort and merge the array
            merge(nums, mid, st, end);
        }
    }

    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size() - 1;
        mergesort(nums, 0, n);
        return nums;
    }
};