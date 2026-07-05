class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int row, int col, char digit) {
        // Row & column
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == digit) return false;
            if (board[i][col] == digit) return false;
        }

        // 3×3 box
        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[boxRow + i][boxCol + j] == digit)
                    return false;
            }
        }

        return true;
    }

    bool sudokuSolver(vector<vector<char>>& board, int row, int col) {
        if (row == 9) return true;

        if (col == 9) {
            return sudokuSolver(board, row + 1, 0);
        }

        if (board[row][col] != '.') {
            return sudokuSolver(board, row, col + 1);
        }

        for (char dig = '1'; dig <= '9'; dig++) {
            if (isSafe(board, row, col, dig)) {
                board[row][col] = dig;

                if (sudokuSolver(board, row, col + 1))
                    return true;

                board[row][col] = '.';
            }
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        sudokuSolver(board, 0, 0);
    }
};

