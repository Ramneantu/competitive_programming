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
#define vout(A,l,r) rep(i,l,r) cout << A[i] << " ";
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

int d, p, u, v;
bool isvalid(double x){
  int left = floor(u/x);
  double new_v = v;
  if(v < left*x + x)
    new_v = left*x + x; // check that if the last pole on the left of the canyon is enough appart from the end of the canyon.
  int right = floor((d-new_v) / x);
  if(right < 0)
    right = -1;
  if((right + left + 2) >= p)
    return true;
  return false;
}

double binsearch(){
  double l = double(0);
  double r = double(d);
  double mid;
  while(r-l >= 0.000001){
    mid = (l+r)*0.5;
    if(isvalid(mid)) // the distance is too small, we need to increase the distance between poles.
      l = mid;
    else
      r = mid; // the distance between poles is too large.
  }
  return mid;
}

int main(){

  int t;
  cin >> t;
  rep(_t,1,t){
    cin >> d >> p >> u >> v;
    printf("Case #%d: %.10f\n", _t, binsearch());
  }


  return 0;
}
