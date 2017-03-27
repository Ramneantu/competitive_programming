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

		string reduce(string s){
			string r;
			if(s.empty())
				return r;
			int offset = s[0] - 'a';
			for(auto c : s){
				int ord = c - 'a' - offset;
				if(ord < 0)
					ord += 26;
				r += char(int('a') + ord);
			}
			return r;
		}

    vector<vector<string>> groupStrings(vector<string>& strings) {
			vector<vector<string> > res;
			map<int, map<string, vector<string> > > H;
			for(auto s : strings){
				int len = s.length();
				string red_s = reduce(s);
				H[len][red_s].push_back(s);
			}

			for(auto h : H){
				for(auto v : h.second)
					res.push_back(v.second);
			}
			return res;
    }
};

int main(){

	int t;
	cin >> t;
	string dummy;
	getline(cin, dummy);
	for(int i=1;i<=t; ++i){
		string s;
		getline(cin, s);
		stringstream iss(s);
		string w;
		vector<string> ss;
		while(iss >> w){
			ss.push_back(w);
		}
		Solution S;
		auto res = S.groupStrings(ss);
		printf("Case #%d:\n", i);
		for(auto vs : res){
			for(auto s : vs)
				cout << s << " ";
			cout << "\n";
		}
	}


  return 0;
}
