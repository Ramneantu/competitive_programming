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

#define XORMAX 4098
#define VMAX 3001

int main(){


  vector<ll> A(4,0);
  for(int i=0; i<4; ++i)
      cin >> A[i];
  sort(A.begin(), A.end());


  vector<ll> all_pairs(VMAX,0);
  for(int i=1;i<=A[0]; ++i)
      for(int j=i; j<=A[1]; ++j)
          all_pairs[j]++;
  for(int i=1; i<VMAX; ++i)
      all_pairs[i] += all_pairs[i-1];

  vector<vector<ll> > M(XORMAX,vector<ll>(VMAX,0));
  for(int i=1; i<=A[0]; ++i)
    for(int j=i; j<=A[1]; ++j){
      M[i^j][j]++;
    }

  for(int i=0; i<XORMAX; ++i)
    for(int j=1; j<VMAX; ++j)
        M[i][j] += M[i][j-1];

  ll total = 0;
  for(int i=1; i<=A[2]; ++i)
    for(int j=i; j<=A[3]; ++j)
      total += all_pairs[i] - M[i ^ j][i];


  cout << total << endl;

  return 0;
}
