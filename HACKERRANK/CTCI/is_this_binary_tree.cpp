#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;


 struct Node {
    int data;
    Node* left;
    Node* right;
 };

void inorder(Node* root, vector<int> &ino){
    if(!root)
        return;
    inorder(root->left, ino);
    ino.push_back(root->data);
    inorder(root->right, ino);
}

   bool checkBST(Node* root) {
    vector<int> ino;
    inorder(root, ino);
       for(int i=0; i<ino.size()-1; i++)
           if(ino[i] >= ino[i+1])
            return false;
    return true;
   }

int main(){


  return 0;
}
