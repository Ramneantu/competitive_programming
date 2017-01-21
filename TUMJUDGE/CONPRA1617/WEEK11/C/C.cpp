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

inline bool cmp(ii a, ii b){
  if(a.fst == b.fst)
    return a.snd > b.snd;
  return a.fst < b.fst;
}

inline bool cmp2(ii a, ii b){
  if(a.snd == b.snd)
    return a.fst < b.fst;
  return a.snd > b.snd;
}

int LIS(vector<ii>& F){
  int res = 0;
  vector<int> dp(sz(F),0);
  dp[0] = 1;
  rep(i,1,sz(F)-1){
    int maxi = 0;
    rep(j,0,i-1){
      //printf("%d,%d %d,%d\n", F[j].fst, F[j].snd, F[i].fst, F[i].snd);
      if(F[j].fst <= F[i].fst && F[j].snd > F[i].snd)
        maxi = max(maxi, dp[j]);
    }
    dp[i] = 1+maxi;
  }
  rep(i,0,sz(F)-1)
    res = max(res, dp[i]);
  return res;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n; cin >> n;
    vector<ii> F(n);
    rep(i,0,n-1)
      cin >> F[i].fst >> F[i].snd;

    sort(F.begin(), F.end(), cmp);
    int res = LIS(F);

    DBG(
      rep(i,0,sz(F)-1)
        cout << F[i].fst << " " << F[i].snd << endl;
      cout << "\n";
    )

    /*
    sort(F.begin(), F.end(), cmp2);
    DBG(rep(i,0,sz(F)-1)
      cout << F[i].fst << " " << F[i].snd << endl;)
    res = max(res, LIS(F));
    */

    printf("Case #%d: %d\n", _t, res);
  }

  return 0;
}
