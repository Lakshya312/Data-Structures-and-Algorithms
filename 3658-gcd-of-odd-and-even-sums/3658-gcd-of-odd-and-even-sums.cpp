class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sumOdd = 1, sumEven = 2;
        for (int i = 1; i < n; i++) {
            sumOdd += 2*i + 1;
            sumEven += 2*i + 2;
        }

        while (sumOdd > 0 && sumEven > 0) {
            if (sumOdd >= sumEven) {
                sumOdd %= sumEven;
            } else {
                sumEven %= sumOdd;
            }
        }

        return sumOdd > 0 ? sumOdd : sumEven;
    }
};