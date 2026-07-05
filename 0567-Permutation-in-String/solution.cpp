class Solution {
public:
    bool isFrequency(int freq[], int windFreq[]){
        for(int i = 0; i<26; i++){
            if(freq[i] != windFreq[i]){
                return false;
            }
        }
        return true;
    }

    bool checkInclusion(string s1, string s2) {
        int freq[26] = {0};
        // saving the frequency of char in s1 to freq array
        for(int ch: s1){
            freq[ch - 'a']++;
        }

        //window size
        int windowSize = s1.length();
        for(int i = 0; i< s2.length();i++){
            int windIdx = 0, idx = i;
            int windFreq[26] = {0};

            while(windIdx < windowSize && idx < s2.length()){
                windFreq[s2[idx] - 'a']++;
                windIdx++;idx++;
            }
            if(isFrequency(freq, windFreq)){
                return true;
            }
        }

        return false;
    }
};
