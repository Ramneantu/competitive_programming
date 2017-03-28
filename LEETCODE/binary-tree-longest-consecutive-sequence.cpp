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

TreeNode* readTree(){
	string line, s, l, r;
	getline(cin, line);
	stringstream iss(line);
	stack<TreeNode*> S;
	iss >> s;
	TreeNode *root = new TreeNode(stoi(s));
	S.push(root);
	while(!S.empty()){
		TreeNode* node = S.top(); S.pop();
		iss >> l >> r;
		if(!r.empty() && r.compare("null") != 0){
			TreeNode* n = new TreeNode(stoi(r));
			node->right = n;
			S.push(n);
		}
		if(!l.empty() && l.compare("null") != 0){
			TreeNode* n = new TreeNode(stoi(l));
			node->left = n;
			S.push(n);
		}
		l.clear(), r.clear();
	}
	return root;
}

void printTree(TreeNode* root){
	if(!root)
		return;
	printTree(root->left);
	cout << root->val << " ";
	printTree(root->right);
}

class Solution {
public:
	int bestLen = 0;
	int longestConsecutiveHelper(TreeNode* root){
    	if(!root)
    		return 0;
    	int left = longestConsecutiveHelper(root->left);
    	int right = longestConsecutiveHelper(root->right);
    	int maxLen = 1;
    	if(root->left && root->val+1 == root->left->val)
    		maxLen = 1 + left;
    	if(root->right && root->val+1 == root->right->val)
    		maxLen = max(maxLen, 1+right);
    	bestLen = max(bestLen, maxLen);
    	return maxLen;
	}
    int longestConsecutive(TreeNode* root) {
        return max(bestLen, longestConsecutiveHelper(root));
    }
};

int main(){

	int T;
	cin >> T;
	string dummy;
	getline(cin, dummy);
	for(int t=1; t<=T; ++t){
		TreeNode *root = readTree();
		Solution S;
		printf("Case #%d: %d\n", t, S.longestConsecutive(root));
	}
}
