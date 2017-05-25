#include<bits/stdc++.h>

using namespace std;

struct node
{
    int data;
    node* left;
    node* right;
};

void preOrder(node *root) {
    if(!root)
        return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(node *root) {
    if(!root)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void inOrder(node *root) {
    if(!root)
        return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

int height(node *root)
{
    if(!root)
        return -1;
    int left = height(root->left);
    int right = height(root->right);
    if(left > right)
        return 1+left;
    else
        return 1+right;
}

/*
     3
   /   \
  5     2
 / \   / \
1   4 6   7
 \       /
  9     8

Top View : 1 -> 5 -> 3 -> 2 -> 7
*/

void top_view(node * root)
{
    vector<int> v;
    node *tree = root;
    while(tree){
        v.push_back(tree->data);
        tree = tree->left;
    }
    for(int i=v.size()-1; i>=0; --i)
        cout << v[i] << " ";
    v.clear();
    tree = root;
    while(tree){
        v.push_back(tree->data);
        tree = tree->right;
    }
    for(int i=1; i<v.size(); ++i)
        cout << v[i] << " ";

}




int main(){


  return 0;
}
