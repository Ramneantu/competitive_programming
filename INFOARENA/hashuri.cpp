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
typedef unsigned long long ll;

#define PRIMES_UP_TO 1000001
ll N = PRIMES_UP_TO;
bitset<PRIMES_UP_TO/2> p;

void primes_7(ll n){
  ll lim = ll(sqrt(n)) / 2;
  n /= 2;
  for(ll i=1; i<=lim; i++){
    if(!p.test(i))
      for(ll j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
        p.set(j);
    }
}


int main(){

  freopen("hashuri.in", "r", stdin);
  freopen("hashuri.out", "w", stdout);

  primes_7(PRIMES_UP_TO);

  int n;
  scanf("%d", &n);
  ll P = 2;
  for(ll i=0; i<p.size(); ++i){
    if(!p.test(i)){
      if(2*i+1 > n)
        break;
      P = 2*i+1;
    }
  }

  vector<set<ll> > M(P);
  rep(i,0,n-1){
    int op;
    ll x;
    scanf("%d %lld\n", &op, &x);
    if(op == 1){
      M[mod(x,P)].insert(x);
    }
    else if(op == 2)
      M[mod(x,P)].erase(x);
    else{
      if(M[mod(x,P)].find(x) != M[mod(x,P)].end())
        printf("1\n");
      else
        printf("0\n");
    }
  }

  return 0;
}
