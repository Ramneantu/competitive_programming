#include<bits/stdc++.h>

using namespace std;

#define PRIMES_UP_TO 10000001
typedef unsigned long long ll;


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

ll triangle_number(ll n){
  if(n%2 == 0)
    return (n/2) * (n+1);
  else
    return ((n+1)/2) * n;
}

void get_factors_and_powers(ll n, vector<pair<int, int> > &factors){
  ll lim = ll(sqrt(n) / 2);
  for(ll i=1; i<=lim; ++i){
    if(!p.test(i)){
      int fac = 2*i+1;
      int pows = 0;
      while(n % fac == 0 && n > 0){
        n /= fac;
        pows++;
      }
      //cout << n << " " << fac << " " << pows << endl;
      if(pows)
        factors.push_back(make_pair(fac, pows));
    }
  }
  int pows = 0;
  while(n % 2 == 0 && n > 0){
    n /= 2;
    pows++;
  }
  if(pows)
    factors.push_back(make_pair(2, pows));
  if(n != 1)
      factors.push_back(make_pair(n, 1));
}

ll nr_of_divisors(vector<pair<int, int> > factors){
  ll divs = 1;
  for(int i=0; i<factors.size(); ++i)
    divs *= (1+get<1>(factors[i]));
  return divs;
}

int main(){

  ll n = PRIMES_UP_TO;

  // generate primes
  primes_7(n);


  // find first number with #divisors > 500
  for(int i=1; i<=100000; ++i){
    vector<pair<int, int> > factors;
    get_factors_and_powers(triangle_number(i), factors);
    if(nr_of_divisors(factors) > 500){
      cout << triangle_number(i) << endl;
      break;
    }
    factors.clear();
  }



  return 0;
}
