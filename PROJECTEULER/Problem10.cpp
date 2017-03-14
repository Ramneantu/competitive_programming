#include <bitset>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cassert>

using namespace std;

#define PRIMES_UP_TO 2000001
typedef unsigned long long ll;

ll primes_7(ll n){
  bitset<PRIMES_UP_TO/2> p;
  ll lim = ll(sqrt(n)) / 2;
  n /= 2;
  ll sum = 0;
  for(ll i=1; i<=lim; i++){
    if(!p.test(i))
      for(ll j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
        p.set(j);
    }
  for(ll i=1; i<n; ++i){
    if(!p.test(i))
      sum += 2*i+1;
  }
  return sum+2;
}

int main(){

  ll n = PRIMES_UP_TO;
  cout << primes_7(n) << endl;

  return 0;
}
