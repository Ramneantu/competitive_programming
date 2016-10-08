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
typedef long ll;

int main(){

  freopen("ssm.in", "r", stdin);
  freopen("ssm.out", "w", stdout);

  ll n;
  scanf("%ld", &n);
  vector<ll> A(n,0);
  rep(i,0,n-1)
    scanf("%ld", &A[i]);

  ll bestsum = A[0];
  ll bestpos = 0;
  vector<ll> P(n,0);
  ll cursum = A[0];
  P[0] = 0;
  for(ll i=1; i<n; ++i){
    if(cursum + A[i] < A[i]){
      cursum = A[i];
      P[i] = i;
    }
    else{
      cursum += A[i];
      P[i] = P[i-1];
    }
    if(cursum > bestsum){
      bestsum = cursum;
      bestpos = i;
    }
  }

  printf("%ld %ld %ld\n", bestsum, P[bestpos]+1, bestpos+1);

  return 0;
}
