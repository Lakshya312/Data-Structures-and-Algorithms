class Solution {
public:
    bool isValid(vector<vector<int>>& grid, int row, int col, int expVal,
                 int n) {
        if (row >= n || col >= n || row < 0 || col < 0 ||
            grid[row][col] != expVal)
            return false;

        if (expVal == (n * n - 1))
            return true;

        bool a1 = isValid(grid, row - 2, col + 1, expVal + 1, n);
        bool a2 = isValid(grid, row - 2, col - 1, expVal + 1, n);
        bool a3 = isValid(grid, row + 2, col + 1, expVal + 1, n);
        bool a4 = isValid(grid, row + 2, col - 1, expVal + 1, n);
        bool a5 = isValid(grid, row - 1, col - 2, expVal + 1, n);
        bool a6 = isValid(grid, row + 1, col - 2, expVal + 1, n);
        bool a7 = isValid(grid, row - 1, col + 2, expVal + 1, n);
        bool a8 = isValid(grid, row + 1, col + 2, expVal + 1, n);

        return a1 || a2 || a3 || a4 || a5 || a6 || a7 || a8;
    }

    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        return isValid(grid, 0, 0, 0, n);
    }
};