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
typedef long long ll;

#define PRIMES_UP_TO 2000001
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

  freopen("ciur.in", "r", stdin);
  freopen("ciur.out", "w", stdout);

  primes_7(PRIMES_UP_TO);
  ll N;
  scanf("%lld", &N);

  ll cnt=1;
  for(ll i=1; 2*i+1<=N; ++i)
    if(!p[i])
      cnt++;
  printf("%lld\n", cnt);


  return 0;
}
