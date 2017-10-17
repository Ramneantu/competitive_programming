#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    
    
    bool is_pal(string s) {
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[int(s.size())-1-i]) {
                return false;
            }
        }
        return true;
    }
    
    string longestPalindrome(string s) {
        int max_pal_len = 1;
        int max_pal_pos = 0;
        for (int i = 0; i < int(s.size())-1; ++i) {
            for (int j = i + 1; j < s.size(); ++j) {
                if (j-i+1 > max_pal_len && is_pal(s.substr(i, j-i+1))) {
                    max_pal_len = max(max_pal_len, j-i+1);
                    max_pal_pos = i;
                }
            }
        }
        return s.substr(max_pal_pos, max_pal_len);
    }
};

int main () {

  return 0;
}
