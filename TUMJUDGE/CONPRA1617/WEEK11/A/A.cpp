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
    int m, n; cin >> m >> n;
    vector<vector<int> > Is;
    rep(i,0,n-1){
        int p,l,s; cin >> p >> l >> s;
        vector<int> _tmp(3,0);
        _tmp[0] = i;
        _tmp[1] = l;
        _tmp[2] = s;
        rep(j,0,p-1)
          Is.pb(_tmp);
    }
    vector<vector<int> > dp(sz(Is), vector<int>(m+1,0));

    DBG(
      rep(i,0,sz(Is)-1)
        cout << Is[i][1] << " " << Is[i][2] << endl;
    )

    rep(j,Is[0][1],m)
      dp[0][j] = Is[0][2];

    rep(i,1,sz(Is)-1){
      rep(j,0,m){
          if(Is[i][1] > j)
            dp[i][j] = dp[i-1][j];
          else
              dp[i][j] = max(dp[i-1][j], Is[i][2] + dp[i-1][j-Is[i][1]]);
      }
    }
    cout << "Case #" << _t << ": ";

    DBG(
      cout <<"\n";
      rep(i,0,sz(Is)-1){
        rep(j,0,m)
          cout << dp[i][j] << " ";
        cout << "\n";
      }
    )

    // find max
    ll maxim = 0;
    int pos = -1;
    rep(j,0,m)
      if(maxim < dp[Is.size()-1][j]){
        maxim = dp[Is.size()-1][j];
        pos = j;
      }
    DBG(cout << "maxim: "  << maxim << endl;)
    int i = sz(Is)-1;
    int j = pos;
    while(i > 0 && j >= 0){
      if(dp[i-1][j] < dp[i][j]){
        cout << Is[i][0]+1 << " ";
        j -= Is[i][1];
      }
      i--;
    }
    if(dp[i][j] >= Is[i][1])
      cout << Is[i][0]+1;
    cout << "\n";
  }

  return 0;
}
