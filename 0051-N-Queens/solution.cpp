class Solution {
public:

    bool isSafe(vector<string> &board, int row, int col, int n) {
        // Check horizontal (row)
        for (int j = 0; j < n; j++) {
            if (board[row][j] == 'Q') {
                return false;
            }
        }

        // Check vertical (column)
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }

        // Check left diagonal (upper-left)
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        // Check right diagonal (upper-right)
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        return true;
    }

    void nQueen(vector<string>&board, vector<vector<string>> &ans, int row, int n){
        if(row == n) {
            ans.push_back({board});
            return;
        }
        
        for(int col = 0; col < n; col++){
            if(isSafe(board, row, col, n)){
                board[row][col] = 'Q';
                nQueen(board, ans, row+1, n);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector <string>board(n, string(n,'.'));
        int row = 0;
        vector<vector<string>>ans;
        nQueen(board, ans, row, n);
        return ans;
    }
};
