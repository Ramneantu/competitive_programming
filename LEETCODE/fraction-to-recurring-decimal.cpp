#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<iostream>
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
    string fractionToDecimal(int numerator, int denominator) {
			string res;
			bool decimalPlaced = false;
			vector<int> digits(10,0);
			while(numerator){
				if(numerator < denominator){
					res += '0';
					if(!decimalPlaced)
						res += ',';
					decimalPlaced = true;
					numerator *= 10;
				}
				else{

				}
			}


			4 / 333 = 0,0
			40


			return res;
    }
};

int main(){

	int T;
	cin >> T;
	for(int t=1; t<=T; ++t){
		int num, denom;
		cin >> num >> denom;
		Solution S;
		printf("Case #%d: %s\n", t, S.fractionToDecimal(num, denom).c_str());
	}

  return 0;
}
