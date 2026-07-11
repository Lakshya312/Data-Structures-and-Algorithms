class Solution {
public:
    vector<int> ans;

    void merge(vector<pair<int, int>>& arr, int st, int end,
               int mid) {
        vector<pair<int, int>> temp;
        int count = 0, i = st, j = mid + 1;

        while (i <= mid && j <= end) {
            if (arr[i].first <= arr[j].first) {
                ans[arr[i].second] += count;
                temp.push_back(arr[i]);
                i++;
            } else {
                count++;
                temp.push_back(arr[j]);
                j++;
            }
        }

        while (i <= mid) {
            ans[arr[i].second] += count;
            temp.push_back(arr[i]);
            i++;
        }

        while (j <= end) {
            temp.push_back(arr[j]);
            j++;
        }

        for (int idx = 0; idx < temp.size(); idx++) {
            arr[idx + st] = temp[idx];
        }
    }

    void CountPair(vector<pair<int, int>>& arr, int st,
                   int end) {
        if (st < end) {
            int mid = st + (end - st) / 2;

            // left
            CountPair(arr, st, mid);

            // right
            CountPair(arr, mid + 1, end);

            merge(arr, st, end, mid);
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> arr;
        ans.assign(n, 0);
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        CountPair(arr, 0, n - 1);

        return ans;
    }
};