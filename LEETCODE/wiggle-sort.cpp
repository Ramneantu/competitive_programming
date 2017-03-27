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
    void wiggleSort(vector<int>& nums) {
			bool wiggled;
			do{
				wiggled = false;
				for(int i=0; i<int(nums.size())-1; ++i)
					if((i % 2 && nums[i] < nums[i+1])|| (i%2 == 0 && nums[i] > nums[i+1])){
						swap(nums[i], nums[i+1]);
						wiggled = true;
					}
			}while(wiggled);
    }
};

int main(){

	int t;
	cin >> t;
	string dummy;
	getline(cin, dummy);
	for(int i=1; i<=t; ++i){
		string s;
		getline(cin, s);
		stringstream iss(s);
		int n;
		vector<int> v;
		while(iss >> n){
			v.push_back(n);
		}
		Solution S;
		S.wiggleSort(v);
		printf("Case #%d: ", i);
		for(auto e : v)
			cout << e << " ";
		cout << "\n";
	}


  return 0;
}
