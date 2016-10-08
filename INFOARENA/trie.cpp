#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>

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

inline int i2c(char c){ return c-'a'; }

struct Trie{
    int cnt;
    int freq;
    vector<Trie*> children;
};

Trie *root;


Trie *new_trie(){
  Trie* node = new Trie;
  node->cnt= node->freq = 0;
  node->children.resize(26,NULL);
  return node;
}

void add(Trie* trie, char *w){
  if(*w == '\0')
    trie->cnt++;
  else{
    if(trie->children[i2c(*w)] == NULL){
        trie->children[i2c(*w)] = new_trie();
        trie->freq++;
    }
    add(trie->children[i2c(*w)], w+1);
  }
}

int del(Trie* trie, char *w){
  if(*w == '\0'){
    trie->cnt--;
  }
  else{
    int res = del(trie->children[i2c(*w)], w+1);
    if(res == 1){
      trie->children[i2c(*w)] = NULL;
      trie->freq--;
    }
  }
  if(trie->cnt == 0 && trie->freq == 0 && trie != root){
    delete trie;
    return 1;
  }
  return 0;
}

int prefix(Trie* trie, char *w, int k){
  if(*w == '\0' || trie->children[i2c(*w)] == NULL)
    return k;
  return prefix(trie->children[i2c(*w)], w+1, k+1);
}

int find(Trie* trie, char *w){
  if(*w == '\0')
    return trie->cnt;
  if(trie->children[i2c(*w)] != NULL)
    return find(trie->children[i2c(*w)], w+1);
  return 0;
}


int main(){

  freopen("trie.in", "r", stdin);
  freopen("trie.out", "w", stdout);

  root = new_trie();

  int op;
  char s[21];
  while(scanf("%d %s\n", &op, s) != EOF){
    if(op == 0){
      add(root, s);
    }
    else if(op == 1){
      del(root,s);
    }
    else if(op == 2){
      printf("%d\n", find(root,s));
    }
    else if(op == 3){
      printf("%d\n", prefix(root,s,0));
    }
  }


  return 0;
}
