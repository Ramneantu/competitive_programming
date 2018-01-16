#include "leet_code.h"
using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i=1; i<nums.size(); i+=2) {
            res += min(nums[i-1], nums[i]);
        }
        return res;
    }
};
