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
    vector<int> findPermutation(string s) {
    	vector<int> p(s.size()+1);
			iota(p.begin(), p.end(),1);

			int desc_len = 0, i = 0;
			for(i=0; i<s.size(); ++i){
				if(s[i] == 'D')
					desc_len++;
				else{
					reverse(p.begin()+i-desc_len, p.begin()+i+1);
					desc_len = 0;
				}
			}
			if(desc_len > 0)
				reverse(p.begin()+i-desc_len, p.begin()+i+1);
			return p;
    }
};

int main(){

	int t;
	cin >> t;
	for(int _t=1; _t<=t; _t++){
		string s;
		cin >> s;
		Solution S;
		auto p = S.findPermutation(s);
		cout << "Case #" << _t << ": ";
		for(auto e : p)
			cout << e << " ";
		cout << "\n";
	}

  return 0;
}
