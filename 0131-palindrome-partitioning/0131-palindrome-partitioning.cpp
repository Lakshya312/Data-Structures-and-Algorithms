class Solution {
public:

    bool isPalindrome(string &s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }

    void backtrack(string &s, int start,
                   vector<string> &curr,
                   vector<vector<string>> &ans) {

        if (start == s.size()) {
            ans.push_back(curr);
            return;
        }

        for (int end = start; end < s.size(); end++) {

            if (isPalindrome(s, start, end)) {

                curr.push_back(s.substr(start, end - start + 1));

                backtrack(s, end + 1, curr, ans);

                curr.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> curr;

        backtrack(s, 0, curr, ans);

        return ans;
    }
};