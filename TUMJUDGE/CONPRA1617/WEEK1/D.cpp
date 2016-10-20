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

#define INF_ULL ULLONG_MAX
#define INF_LL  LLONG_MAX
#define NINF_LL LLONG_MIN
#define INF_L   LONG_MAX
#define NINF_L   LONG_MIN
#define INF_U   UINT_MAX
#define INF     INT_MAX
#define NINF     INT_MIN


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    int n;
    cin >> n;
    vector<vector<int> > A;
    rep(j,0,n-1){
      vector<int> v(5,0);
      rep(i,0,4){
        int val;
        cin >> val;
        v[i] = -val;
      }
      sort(v.begin(), v.end());
      A.pb(v);
    }
    sort(A.begin(), A.end());
    cout << "Case #" << _t << ":\n";
    for(int i=0; i<A.size(); ++i){
      for(int j=0; j<A[i].size(); ++j)
    //for(int i=A.size()-1; i>=0; --i){
      //for(int j=A[i].size()-1; j>=0; --j)
        cout << -A[i][j] << " ";
      cout << "\n";
    }
  }


  return 0;
}
