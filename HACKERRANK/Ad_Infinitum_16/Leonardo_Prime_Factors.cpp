#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#include <bitset>
#include <utility>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef unsigned long long ll;

#define PRIMES_UP_TO 10000001
bitset<PRIMES_UP_TO/2> p;

ll primes_7(ll n){
  ll lim = ll(sqrt(n)) / 2;
  n /= 2;
  for(ll i=1; i<=lim; i++){
    if(!p.test(i))
      for(ll j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
        p.set(j);
    }
  return p.size() - p.count();
}


int main(){


  // generate primes
  primes_7(10000001);
  vector<pair<int, ll> > factors;
  ll prod = 2;
  int nr_factors = 1;
  ll lim = 1000000000000000000;
  // the maximum number of factors a number between [1...N] can have is when all factors have exponents = 1,
  // so keep a product of primes, starting from 2, and stop when product is greater than 10^18.
  factors.push_back(make_pair(nr_factors, prod));
  for(int i=1; i<p.size(); ++i)
    if(!p.test(i)){
      nr_factors++;
      if(prod * (2*i+1) > lim)
        break;
      prod *= (2*i+1);
      factors.push_back(make_pair(nr_factors, prod));
    }

  int t;
  cin >> t;
  while(t--){
    ll n;
    cin >> n;
    int res = 15;
    for(int i=0; i<factors.size(); ++i)
      if(get<1>(factors[i]) > n){
        res = get<0>(factors[i]) - 1;
        break;
      }
    cout << res << endl;
  }


  return 0;
}
