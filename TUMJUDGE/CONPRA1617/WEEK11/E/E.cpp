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

inline long CCC(vector<int>& sums, int a, int b, int i, int j){
  long s = sums[j]-(i>0 ? sums[i-1] : 0);
  DBG(printf("[%d,%d], s: %ld\n", i,j,s);)
  if(s <= a)
    return 0;
  if(s <= b)
    return sqr(s-a);
  return INT_MAX;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n,a,b; cin>>n>>a>>b;
    vector<int> cs(n,0);
    vector<int> sums(n,0);
    rep(i,0,sz(cs)-1){
      cin>>cs[i];
      sums[i] = (i>0 ? sums[i-1] : 0) + cs[i];
    }

    DBG(
      cout<<"a: " << a << " b: " << b << endl;
      cout<<"sums: ";
      rep(i,0,sz(sums)-1)
        cout<<sums[i]<<" ";
      cout<<"\n";
    )

    vector<vector<long> > dp(n, vector<long>(n+1, INT_MAX));

    rep(i,0,n-1)
      dp[i][0] = CCC(sums,a,b,0,i);

    rep(j,1,n){
      DBG(
        cout<<"dp for " << j << " visits:\n";
        rep(_i,0,n-1){
          rep(_j,0,n)
            cout<<dp[_i][_j]<<" ";
          cout<<"\n";
        })
      rep(i,0,n-1){
        rep(k,0,i){
          long c = CCC(sums,a,b,i-k+1,i);
          if(c >= INT_MAX)
            break;
          dp[i][j] = min(dp[i][j], dp[i-k][j-1] + c);
        }
      }
    }

    DBG(
      cout<<"dp:\n";
      rep(_i,0,n-1){
        rep(_j,0,n)
          cout<<dp[_i][_j]<<" ";
        cout<<"\n";
      })


    long res = INT_MAX;
    rep(j,0,n)
      if(dp[n-1][j] != INT_MAX){
        res = dp[n-1][j];
        break;
      }
    printf("Case #%d: ", _t);
    if(res >= INT_MAX)
      cout<<"impossible\n";
    else
      cout<<res<<"\n";
  }

  return 0;
}
