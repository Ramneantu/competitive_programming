#include<bits/stdc++.h>

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

#define PRIMES_UP_TO 1000000
#define MOD 9973
bitset<PRIMES_UP_TO/2> p;
vector<ll> primes;


void primes_7(ll n){
  ll lim = ll(sqrt(n)) / 2;
  n /= 2;
  for(ll i=1; i<=lim; i++){
    if(!p.test(i))
      for(ll j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
        p.set(j);
    }
  primes.push_back(2);
  for(ll i=1; i<n; ++i){
    if(!p.test(i))
      primes.push_back(2*i+1);
  }
}




int main(){

  freopen("ssnd.in", "r", stdin);
  freopen("ssnd.out", "w", stdout);

  ll N = PRIMES_UP_TO;
  primes_7(N);

  int t;
  scanf("%d", &t);
  while(t--){
    ll n;
    scanf("%lld", &n);

    ll prod = 1;
    ll sum = 1;
    ll i=0;
    ll d, pd;
    ll lim = ll(sqrt(n)+1);
    for(; i<primes.size() && sqr(primes[i]) <= n; ++i){
      if(n%primes[i] == 0){
        d = 0;
        pd = primes[i];
        while(n > 0 && n%primes[i] == 0){
          d++;
          pd *= primes[i];
          n/= primes[i];
        }
        sum *= (d+1);
        prod *= (pd-1)*1.0/(primes[i]-1);
      }
    }
    if(n > 1){
      sum *= 2;
      prod *= (n*n-1)*1.0/(n-1);
    }
    printf("%lld %lld\n", sum % MOD, prod % MOD);
  }
  return 0;
}
