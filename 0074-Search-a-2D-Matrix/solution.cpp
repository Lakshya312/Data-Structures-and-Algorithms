class Solution {// time complexity = O(log(m*n))
public:
    bool searchInRow(vector<vector<int>> mat, int target, int tarRow){
        int col = mat[0].size();
        int st = 0, ed = col - 1;
        while(st <= ed){
            int mid = st + (ed - st)/2;
            if(target == mat[tarRow][mid]){
                return true;
            }else if(target > mat[tarRow][mid]){
                st = mid + 1;
            }else{
                ed = mid - 1;
            }
        }
        return false;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size() - 1;
        int col = matrix[0].size() - 1;
        int sr = 0, er = matrix.size() - 1;
        
        while(sr <= er){
            int midRow = sr + (er - sr) / 2;
            if(target >= matrix[midRow][0] && target <= matrix[midRow][col]){
                return searchInRow(matrix, target, midRow);
            }else if(target <= matrix[midRow][0]){
                //upper row
                er = midRow - 1;
            }else if(target >= matrix[midRow][col]){
                //lower row
                sr = midRow + 1;
            }
        }
        return false;
    }
};
