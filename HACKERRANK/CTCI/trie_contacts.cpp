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

struct Trie{
    int cnt;
    vector<Trie*> children;
};

Trie *init(){
    Trie *trie = new Trie;
    trie->cnt = 0;
    trie->children.resize(26,NULL);
    return trie;
}

void add(Trie* trie, string name){
    for(int i=0; i<name.size(); ++i){
        char c = name[i]-'a';
        if(trie->children[c] == NULL){
            Trie* node = new Trie;
            node->cnt=0;
            node->children.resize(26,NULL);
            trie->children[c] = node;
        }
        trie = trie->children[c];
        trie->cnt++;
    }
}

int find(Trie *trie, string partial){
    int cnt;
    int i;
    for(i=0; i<partial.size(); ++i){
        char c = partial[i]-'a';
        if(trie->children[c] == NULL)
            break;
        else{
            trie = trie->children[c];
            cnt = trie->cnt;
        }
    }
    if(i <= partial.size()-1)
        cnt = 0;
    return cnt;
}


int main(){
    int n;
    cin >> n;
    Trie* root = init();
    bool find_op = false;
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        if(op == "add"){
            add(root, contact);
        }
        else if(op == "find"){
            if(find_op)
              cout << endl;
            find_op = true;
            cout << find(root, contact);
        }
    }
    return 0;
}
