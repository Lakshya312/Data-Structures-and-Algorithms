class Solution {
public:
    bool isAlphaNumeric(char st){
        if((tolower(st) >= 'a' && tolower(st)<='z')|| 
        (st >= '0' && st<='9'))
        {
            return true;
        }else{
            return false;
        }
    }

    bool isPalindrome(string st) {
        int n = st.size();
        int i = 0, j = n-1;
        bool isPalindrome = true;
        while(i <= j){
            if(!isAlphaNumeric(st[i])){
                i++;
                continue;
            }
            if(!isAlphaNumeric(st[j])){
                j--;
                continue;
            }

            if(tolower(st[i]) == tolower(st[j])){
                i++;
                j--;
            }else{
                return false;
            }

        }
        return true;
    }
};
