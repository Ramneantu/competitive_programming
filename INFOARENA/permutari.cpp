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

int n;
vector<int> sol;
vector<bool> seen;
void bk(int k){
  if(k == n){
    rep(i,0,sol.size()-1)
      printf("%d ", sol[i]);
    printf("\n");
  }
  else{
    rep(i,1,n)
      if(!seen[i]){
        sol[k] = i;
        seen[i] = true;
        bk(k+1);
        seen[i] = false;
      }
  }
}


int main(){

  freopen("permutari.in", "r", stdin);
  freopen("permutari.out", "w", stdout);

  scanf("%d", &n);
  sol.resize(n);
  seen.resize(n,false);
  rep(i,0,seen.size()-1)
    seen[i] = false;
  bk(0);

  return 0;
}
