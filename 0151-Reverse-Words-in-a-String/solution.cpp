class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        string str = "";
        string ans = "";
        for(int i = 0; i<s.length(); i++){
            if(s[i] != ' '){
                str += s[i];
            }else{
                if(!str.empty()){
                    reverse(str.begin(), str.end());
                    ans+= " " + str;
                    str.clear();
                }
            }
        }

        if(!str.empty()){
            reverse(str.begin(), str.end());
            ans += " " + str;
        }

        return ans.substr(1);
} 
};
