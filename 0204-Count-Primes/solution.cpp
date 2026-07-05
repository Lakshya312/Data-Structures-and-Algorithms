class Solution {
public:
    int countPrimes(int n) {
    vector<bool>isPrime(n+1, true);
    // instead of n+1 i can do n also
    int count = 0;
    for(int i = 2; i<n; i++){
        if(isPrime[i]){
            count++;
            for(int j = i+i; j<n; j+=i){
                isPrime[j] = false;
            }
        }
    }
    return count;
    }
};
