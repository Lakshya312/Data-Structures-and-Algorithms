class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int st = 1, end = n - 2;
        while (st <= end)
        {
            int mid = st + (end - st)/2;
            if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]){
                return mid;
            }
            if(arr[mid - 1] < arr[mid] ){
                st = mid + 1;
            }
            if(arr[mid + 1] < arr[mid]){
                end = mid - 1;
            }
        }
        
        return -1;
    }
};
