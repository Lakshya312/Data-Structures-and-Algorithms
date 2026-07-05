class Solution {
public:
    string removeOccurrences(string st, string part) {
        while(st.length()>0 && st.find(part) < st.length()){
        st.erase(st.find(part), part.length());
    }
    return st;
    }
};
