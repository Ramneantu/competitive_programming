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

		int apply(int a, int b, int c, int x){
			return a*x*x + b*x + c;
		}

		void apply(int a, int b, int c, vector<int>& nums){
			for(auto& e : nums)
				e = a*e*e + b*e + c;
		}

		void transformConvex(vector<int>& nums, vector<int>& res, int a, int b, int c, int l, int r){
			while(l >= 0 && r < nums.size()){
				int yr = apply(a,b,c,nums[r]);
				int yl = apply(a,b,c,nums[l]);
				if(yl < yr){
						res.push_back(yl);
						l--;
				}
				else{
					res.push_back(yr);
					r++;
				}
			}
			while(l >= 0){
				res.push_back(apply(a,b,c,nums[l]));
				l--;
			}
			while(r < nums.size()){
				res.push_back(apply(a,b,c,nums[r]));
				r++;
			}
		}

		void transformConcave(vector<int>& nums, vector<int>& res, int a, int b, int c, int l, int r){
			while(l <= r){
				int yr = apply(a,b,c,nums[r]);
				int yl = apply(a,b,c,nums[l]);
				if(yl < yr){
						res.push_back(yl);
						l++;
				}
				else{
					res.push_back(yr);
					r--;
				}
			}
		}

    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
			vector<int> res;

			if(a == 0){
				res = nums;
				apply(a,b,c,res);
				if(b < 0)
					reverse(res.begin(), res.end());
			}
			else{
				float minp = -b*1.0 / (2*a);
				int l,r;
				if(a > 0){
					l = int(nums.size())-1, r = nums.size();
					for(int i=0; i<nums.size(); ++i)
						if(nums[i] >= minp){
							l = i-1, r = i;
							break;
						}
					transformConvex(nums, res, a, b, c, l, r);
				}
				else{
					l = 0, r = nums.size()-1;
					transformConcave(nums, res, a, b, c, l, r);
				}
			}
			return res;
    }
};

int nextInt(){
	int n;
	cin >> n;
	string dummy;
	getline(cin, dummy);
	return n;
}

void read(vector<int>& v, int& a, int& b, int& c){
	string s;
	getline(cin, s);
	stringstream iss(s);
	int n;
	while(iss >> n)
		v.push_back(n);
	a = nextInt();
	b = nextInt();
	c = nextInt();
}

int main(){

	int t;
	cin >> t;
	string dummy;
	getline(cin, dummy);
	for(int i=1; i<=t; ++i){
		vector<int> v;
		int a,b,c;
		read(v,a,b,c);

		// solve
		Solution S;
		auto res = S.sortTransformedArray(v,a,b,c);
		printf("Case #%d: ", i);
		for(auto e : res)
			cout << e << " ";
		cout << "\n";
	}


  return 0;
}
