#include<bits/stdc++.h>
/**
TAGS: binary-search, counting
**/

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

int main(){

  ll t;
  cin >> t;
  vector<ll> A;
  ll two = 1;
  ll total = 0;
  for(int i=0;total <= 1000000000001;++i){
    ll el = 3*two;
    two <<= 1;
    total += el;
    A.push_back(total);
  }
  ll k = ((upper_bound(A.begin(), A.end(), t)-A.begin()) + (lower_bound(A.begin(), A.end(), t)-A.begin()))/2;
  cout << 3*(ll(pow(2,k+1))) - t - 2 << endl;


  return 0;
}
