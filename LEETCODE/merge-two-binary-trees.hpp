#include "leet_code.h"
using namespace std;


 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) {
            return t1;
        }
        TreeNode* node = new TreeNode(0);
        if (!t1 && t2) {
            node->val = t2->val;
            node->left = mergeTrees(t1, t2->left);
            node->right = mergeTrees(t1, t2->right);
        }
        else if (t1 && !t2) {
            node->val = t1->val;
            node->left = mergeTrees(t1->left, t2);
            node->right = mergeTrees(t1->right, t2);
        }
        else {
            node->val = t1->val + t2->val;
            node->left = mergeTrees(t1->left, t2->left);
            node->right = mergeTrees(t1->right, t2->right);
        }

        return node;
    }
};