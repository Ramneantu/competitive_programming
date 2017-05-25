#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define NMAX 1000000002
vector<bool> primes;
vector<ll> p;

void gen_primes(ll n){
  ll lim = ll(sqrt(n))+1;
  //cout << "lim: " << lim << endl;
  n /= 2;
  primes.resize(n, true);

  int i, j;
  for (i = 1; ((i * i) << 1) + (i << 1) <= n; i += 1) {
    if (primes[i]) {
      for (j = ((i * i) << 1) + (i << 1); (j << 1) + 1 <= n; j += (i << 1) + 1) {
        primes[j] = false;
      }
    }
  }

  p.push_back(2);
  for (i=1; 2 * i + 1 <= 2*n; ++i)
      if (primes[i]) p.push_back(2*i+1);
  //cout << "gen primes finished" << endl;
  primes.erase(primes.begin(), primes.end());
}


int main(){


  /*
  // test gen_primes
  gen_primes(20);
  for(int i=0; i<p.size(); ++i)
    cout << p[i] << " ";
  cout << "\n";
  */
  gen_primes(NMAX);

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    ll n;
    cin >> n;
    ll nr_divisors = 1;
    ll n_2 = n/2 + 1;


    for(int i=0; i<p.size() && p[i] <= n_2; ++i){
      if(n%p[i] == 0){
        int fac = 0;
        ll nn = n;
        while(nn%p[i] == 0 && nn > 0){
          fac++;
          nn /= p[i];
        }
        nr_divisors *= (fac+1);
      }
    }

    cout << "Case #" << t << ": " << nr_divisors << "\n";
  }

  return 0;
}
