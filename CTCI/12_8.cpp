#include<bits/stdc++.h>
//====================================
// Name: 12.8 CTCI Vol6
// Date: 21/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: recursive copy a data structure.
//====================================

using namespace std;

struct Node{
  Node *left;
  Node *right;
  int val;

  Node(int v) : val(v), left(NULL), right(NULL) {}
  static void print(Node *root){
    if(!root)
      return;
    std::cout << root->val << std::endl;
    print(root->left);
    print(root->right);
  }

  static Node *copy_recursive(Node *cur, map<Node*,Node*> &H){
      if(!cur)
        return NULL;

      if(H.find(cur) != H.end())
        return H[cur];

      Node *node = new Node(cur->val);
      H[cur] = node;
      node->left = copy_recursive(cur->left, H);
      node->right = copy_recursive(cur->right, H);
      return node;
  }
};

int main(){

  Node *root = new Node(2);
  root->right = new Node(3);
  root->left = new Node(1);
  Node::print(root);

  map<Node*,Node*> H;
  Node *copy_of_root = Node::copy_recursive(root, H);
  Node::print(copy_of_root);
}
