class Solution {
public:
    bool isSafe(vector<string> &board, int row, int col, int n) {
        // vertical
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q')
                return false;
        }

        // upper - right
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q')
                return false;

        // upper - left
        for (int i = row, j = col; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 'Q')
                return false;

        return true;
    }

    void nQueen(vector<vector<string>>& ans, vector<string>& board, int row,
                int n) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                nQueen(ans, board, row + 1, n);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));

        nQueen(ans, board, 0, n);

        return ans;
    }
};