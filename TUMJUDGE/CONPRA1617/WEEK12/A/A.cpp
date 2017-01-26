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
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
#define vout(V,a,b,msg) cout << msg << ": "; rep(i,a,b)  cout << V[i] << " "; cout << "\n";
#define fst first
#define snd second
#define debug 0
#define DBG(code) if(debug){    \
                    do{         \
                    code        \
                    }while(0);  \
                  }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int ct;

class Trie{
private:
  int cnt;
  map<char,Trie> children;
public:
  Trie(){ cnt = 0; }
  void add(char *w){
    if(*w == '\0'){
      cnt++;
      if(children.size() > 0){
        ct+=cnt;
        cnt=0;
      }
    }
    else{
      if(children.find(*w) == children.end()){
          children[*w] = Trie();
      }
      if(cnt > 0){
        ct+=cnt;
        cnt=0;
      }
      children[*w].add(w+1);
    }
  }
};

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n; cin>>n;
    Trie trie = Trie();
    ct = 0;
    rep(i,0,n-1){
      char name[501]; cin>>name;
      trie.add(name);
    }
    printf("Case #%d: %d\n", _t, ct);
  }

  return 0;
}
