class Solution {
public:
    bool isPali(string parts) {
        string s = parts;
        reverse(s.begin(), s.end());
        return s == parts;
    }

    void getAllParts(string s, vector<string>& partitions,
                     vector<vector<string>>& ans) {
        if (s.length() == 0) {
            ans.push_back(partitions);
            return;
        }

        for (int i = 0; i < s.length(); i++) {
            string parts = s.substr(0, i + 1);
            if (isPali(parts)) {
                partitions.push_back(parts);
                getAllParts(s.substr(i + 1), partitions, ans);
                partitions.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> partitions;
        vector<vector<string>> ans;

        getAllParts(s, partitions, ans);
        return ans;
    }
};