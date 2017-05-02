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
    int divide(int dividend, int divisor) {
			if(divisor == 0 || (dividend == INT_MIN && divisor == -1))
				return INT_MAX;
			int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
			long long divn = labs(dividend);
			long long divi = labs(divisor);

			int res = 0;
			while(divn >= divi){
				long long tmp = divi, mult = 1;
				while(divn >= (tmp << 1)){
					mult <<= 1;
					tmp <<= 1;
				}
				divn -= tmp;
				res += mult;
			}
			return (sign > 0 ? res : -res);
		}
};

int main(){

	cout << INT_MIN << " " << INT_MAX << endl;

	int T;
	cin >> T;
	for(int t=1; t<=T; ++t){
		int x,y;
		cin >> x >> y;
		Solution S;
		printf("x: %d, y: %d\nCase #%d: %d\n\n", x,y, t, S.divide(x,y));
	}

  return 0;
}
