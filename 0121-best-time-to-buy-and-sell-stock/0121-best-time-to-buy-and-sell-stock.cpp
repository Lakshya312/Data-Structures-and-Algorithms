class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxprofit = 0;
        int bestbuy = prices[0], n = prices.size();
        for(int i = 1; i<n; i++){

            if(bestbuy <= prices[i]){
                int profit = prices[i] - bestbuy;
                maxprofit = max(maxprofit, profit);
            }

            bestbuy = min(bestbuy, prices[i]);
        
        }
    return maxprofit;
    }
};