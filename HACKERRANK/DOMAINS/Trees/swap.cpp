#include<bits/stdc++.h>
using namespace std;

struct node {
    int h;
    int data;
    node *left;
    node *right;
};

void inorder(node *root){
    if(!root)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

node* new_node(int v){
    node* n=new node;
    n->left =n->right=NULL;
    n->data=v;
    n->h=0;
    return n;
}

int main() {
    int n;
    cin >> n;
    vector<vector<node*> > D(1025);
    queue<node*> Q;
    node* root=new_node(1);
    root->h=1;
    Q.push(root);
    D[1].push_back(root);
    int id=2;
    for(int i=0;i<n;++i){
        int l,r;
        cin >> l >> r;
        node* cur = Q.front(); Q.pop();
        if(l>0){
            node* n=new_node(max(cur->data+1, id));
            n->h=cur->h+1;
            D[n->h].push_back(n);
            cur->left=n;
            Q.push(n);
            id++;
        }
        if(r>0){
            node* n=new_node(max(cur->data+2,id));
            n->h=cur->h+1;
            D[n->h].push_back(n);
            cur->right=n;
            Q.push(n);
            id++;
        }
    }

    int t;
    cin >> t;
    for(int i=0; i<t; ++i){
        int k;
        cin >> k;
        bool swapped=false;
        for(int j=k; j<D.size(); j+=k){
            if(D[j].size() > 0){
                for(int l=0; l<D[j].size(); l++){
                    node* cur=D[j][l];
                    if(cur->left || cur->right){
                        swapped = true;
                        node* aux=cur->left;
                        cur->left = cur->right;
                        cur->right = aux;
                    }
                }
            }
        }
        if(swapped){
            inorder(root);
            cout << "\n";
        }
    }


//    inorder(root);
    /*
    for(int i=0; i<D.size(); ++i){
        if(D[i].size()){
            for(int j=0; j<D[i].size(); ++j)
                cout << D[i][j]->data << " ";
            cout << "\n";
        }
    }
    */


    return 0;
}
