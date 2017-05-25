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
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

struct Trie{
    int depth;
    Trie* parent;
    unordered_map<char, Trie*> children;
};

void add_to_trie(string word, Trie* root){
  int i=0;
  Trie* last = root;
  while(i<word.length()){
    if(root->depth != -1)
      last = root;
    unordered_map<char,Trie*>::iterator it = root->children.find(word[i]);
    if(it != root->children.end())
      root = it->second;
    else{
      Trie* node = new Trie;
      node->parent = NULL;
      node->depth = -1;
      if(i == word.length()-1){
        node->depth = i+1;
        node->parent = last;
      }
      root->children.insert(make_pair(word[i], node));
      root = node;
    }
    i++;
  }
}

string s;
void display_trie(Trie* root){
  if(root->depth > 0)
      cout << s.substr(0, root->depth) << " : " << root->depth << endl;
  if(root->children.empty())
    return;
  for(unordered_map<char, Trie*>::iterator it=root->children.begin(); it!=root->children.end(); ++it)
    display_trie(it->second);
}

Trie* max_node;
void find_max_repeated_substr(Trie* root){
  if(root->children.empty())
    return;
  if(root->depth > max_node->depth)
    max_node = root;
  for(unordered_map<char, Trie*>::iterator it=root->children.begin(); it!=root->children.end(); ++it)
    find_max_repeated_substr(it->second);
}


Trie* init_trie(){
  Trie* root = new Trie;
  root->depth = 0;
  return root;
}


int main(){

  Trie* root = init_trie();
  int m;
  cin >> s >> m;
  for(int i=s.size()-1; i>=0; --i){
    //cout << "add to trie: " << s.substr(i) << endl;
    add_to_trie(s.substr(i), root);
  }
  //display_trie(root);

  max_node = new Trie;
  max_node->depth = 0;
  find_max_repeated_substr(root);

  int max_len;
  if(max_node->depth == 0){
    //cout << s << " : " << s.length() << endl;
    max_len = s.length();
  }
  else{
    while(max_node->parent != root){
      max_node = max_node->parent;
    }

    //cout << s.substr(0, max_node->depth) << " : " << max_node->depth << endl;
    max_len = s.substr(0, max_node->depth).size();
  }

  cout << m / max_len<< endl;


  return 0;
}
