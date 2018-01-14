#include "leet_code.h"
using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> res;
        for(int i=left; i<=right; ++i) {
            int n = i;
            bool is_good = true;
            while(n) {
                int c = n%10;
                if ( c == 0) {
                    is_good = false;
                    break;
                }
                if (i % c ) {
                    is_good = false;
                    break;
                }
                n /= 10;
            }
            if (is_good) {
                res.push_back(i);    
            }
        }
        return res;
    }
};
