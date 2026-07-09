class Solution {
public:
    vector<int> ans;

    void merge(vector<pair<int,int>>& arr, int st, int mid, int ed) {
        vector<pair<int,int>> temp;

        int i = st;
        int j = mid + 1;
        int rightCount = 0;

        while (i <= mid && j <= ed) {

            if (arr[i].first <= arr[j].first) {
                ans[arr[i].second] += rightCount;
                temp.push_back(arr[i]);
                i++;
            } else {
                rightCount++;
                temp.push_back(arr[j]);
                j++;
            }
        }

        while (i <= mid) {
            ans[arr[i].second] += rightCount;
            temp.push_back(arr[i]);
            i++;
        }

        while (j <= ed) {
            temp.push_back(arr[j]);
            j++;
        }

        for (int k = 0; k < temp.size(); k++) {
            arr[st + k] = temp[k];
        }
    }

    void mergeSort(vector<pair<int,int>>& arr, int st, int ed) {
        if (st >= ed)
            return;

        int mid = st + (ed - st) / 2;

        mergeSort(arr, st, mid);
        mergeSort(arr, mid + 1, ed);

        merge(arr, st, mid, ed);
    }

    vector<int> countSmaller(vector<int>& nums) {

        int n = nums.size();
        ans.assign(n, 0);

        vector<pair<int,int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        mergeSort(arr, 0, n - 1);

        return ans;
    }
};