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


int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,c; cin >> n >> c;
    vector<int> coins(n);
    rep(i,0,n-1)
      cin >> coins[i];

    vector<long> dp(c+1,0);
    vector<long> prev(c+1,-1);
    dp[0] = 0;
    rep(i,1,c){
      long mi = INT_MAX;
      int choice = -1;
      rep(j,0,sz(coins)-1){
        if(coins[j]<=i && dp[i-coins[j]]<mi){
          mi = dp[i-coins[j]];
          choice = j;
        }
      }
      dp[i] = mi+1;
      prev[i] = choice;
    }

    DBG(
      cout << "dp: ";
      rep(i,0,sz(dp)-1)
        cout << dp[i] << " ";
      cout << "\n";
      cout << "prev: ";
      rep(i,0,sz(prev)-1)
        cout << prev[i] << " ";
      cout << "\n";
    )

    printf("Case #%d: ", _t);
    //recover
    if(dp[c] >= INT_MAX){
      rep(i,0,n-1)
        cout << 0 << " ";
    }
    else{
      vector<int> H(n,0);
      int i = c;
      while(i>0){
        H[prev[i]]++;
        i -= coins[prev[i]];
      }
      rep(i,0,sz(H)-1)
        cout << H[i] << " ";
    }
    cout << "\n";
  }

  return 0;
}
