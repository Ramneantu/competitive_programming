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
typedef int ll;

#define NMAX 100001
#define POW2MAX 17

ll n, m;
vector<ll> arr;
vector<vector<ll> > RMQ;

// preprocess: O(nlog(n)), query: O(1)
vector<ll> pow2;
ll log_2(ll n){
  ll r = upper_bound(pow2.begin(), pow2.end(), n)-pow2.begin();
  ll l = lower_bound(pow2.begin(), pow2.end(), n)-pow2.begin();
  if(l == r)
    return l-1;
  return l;
}
void pre_RMQ_4(){

  pow2.push_back(1);
  rep(i,1,POW2MAX)
    pow2.push_back((1<<i));

  RMQ.resize(arr.size(), vector<ll>(POW2MAX, INF));
  rep(i,0,n-1)
    RMQ[i][0] = i;

  for(ll j=1; (1 << j)<=n; ++j)
    for(ll i=0; i+(1 << j)-1<n; ++i){
      if(arr[RMQ[i][j-1]] <= arr[RMQ[i+(1<<(j-1))][j-1]]){
        RMQ[i][j] = RMQ[i][j-1];
      }
      else
        RMQ[i][j] = RMQ[i+(1<<(j-1))][j-1];
    }
}
ll RMQ_4(ll i, ll j){
  ll k = log_2(j-i+1);
  if(arr[RMQ[i][k]] < arr[RMQ[j-(1<<k)+1][k]])
    return RMQ[i][k];
  else
    return RMQ[j-(1<<k)+1][k];
}



int main(){

  freopen("rmq.in", "r", stdin);
  freopen("rmq.out", "w", stdout);

  scanf("%d %d", &n, &m);
  arr.resize(n,0);

  rep(i,0,n-1)
    scanf("%d", &arr[i]);

  pre_RMQ_4();
  rep(i,0,m-1){
    int a,b;
    scanf("%d %d", &a, &b);
    a--;
    b--;
    printf("%d\n", arr[RMQ_4(a,b)]);
  }

  return 0;
}
