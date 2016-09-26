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
typedef unsigned long long ll;

#define MOD 1000000007

vector<ll> pows;
ll power(ll x, ll y, ll p)
{
    ll res = 1;      // Initialize result

    x = mod(x,p);  // Update x if it is more than or
                // equal to p

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = mod(mod(res,p)*x,p);

        // y must be even now
        y = y>>1; // y = y/2
        x = mod(x*x,p);
    }
    return res;
}

// ((pows[a] * (v+1))-1) * pows[b]
ll f(long long a,ll b,ll v){
    if(a<0)
      a = 0;
    return mod((mod(mod(pows[a]*(v+1),MOD)-1, MOD))*pows[b], MOD);
}

int main(){


  for(ll i=0; i<=1000010; ++i)
    pows.push_back(power(2, i, MOD));

  ll n;
  cin >> n;
  vector<ll> A(n);
  for(ll i=0; i<n; ++i)
    cin >> A[i];

  ll total = mod(mod(pows[n]-1, MOD)*A[0], MOD);
  total += mod(mod(pows[n]-1, MOD)*A[n-1], MOD);
  ll inc = 1;
  long long a = n+1-4;
  ll b = 1;
  ll pid;
  if(n%2)
    pid = n/2;
  else
    pid = (n/2)-1;
  ll val;
  ll j = 1;
  ll left, right;
  for(ll i=0; i<pid; ++i){
    inc = mod(mod(inc+1, MOD)*2, MOD);
    val = f(a,b,inc);
    left = mod(val*A[j], MOD);
    right = mod(val*A[n-j-1], MOD);
    total += mod(left + right, MOD);
    a-= 2;
    b = mod(b+1, MOD);
    j++;
  }
  if(n%2)
    total -= right;

  cout << mod(total, MOD) << endl;

  return 0;
}
