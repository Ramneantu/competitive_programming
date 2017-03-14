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
#include <iomanip>

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

int main(){

  vector<vector<int> > M;

  string s;
  int i=0;
  while(getline(cin, s)){
    stringstream iss(s);
    int val;
    M.push_back(vector<int>());
    while(iss >> val){
        M[M.size()-1].push_back(val);
    }
  }

  vector<vector<int> > opt = M;
  rep(i,1,opt.size()-1){
    opt[i][0] += opt[i-1][0];
    opt[i][opt[i].size()-1] += opt[i-1][opt[i-1].size()-1];
  }
  rep(i,1,opt.size()-1)
    rep(j,1,opt[i].size()-2)
      opt[i][j] = max(opt[i-1][j-1], opt[i-1][j]) + M[i][j];

  cout << *max_element(opt.back().begin(), opt.back().end()) << endl;

  return 0;
}
