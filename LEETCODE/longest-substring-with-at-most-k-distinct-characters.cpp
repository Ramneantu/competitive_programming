#include<bits/stdc++.h>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int maxLen = 0;
        map<char, int> F;
        int l = 0, r = 0;
        int distinctChars = 0;
        while(l <= r && r < s.length()){
            distinctChars += (++F[s[r]] == 1); // increase distinctChars if a new char is found.
            while(distinctChars > k)    // while condition is not satisfied increase left pointer.
                distinctChars -= (--F[s[l++]] == 0);
            maxLen = max(maxLen, r-l+1); // for current l and r condition is satisfied.
            r++;
        }
        return maxLen;
    }
};

int main(){



  return 0;
}
