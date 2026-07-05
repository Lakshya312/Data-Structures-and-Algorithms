class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxarea = 0, n = height.size();
        int lp = 0, rp = n - 1;

        while(lp < rp){
            int w = rp - lp;
            int ht = min(height[lp], height[rp]);
            int area =  w*ht;
            maxarea = max(area, maxarea);

            height[lp] > height[rp] ? rp-- : lp++;
        }
        return maxarea;
    }
};
