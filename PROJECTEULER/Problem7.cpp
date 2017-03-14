#include <bitset>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cassert>

using namespace std;

#define PRIMES_UP_TO 1000001
typedef unsigned long long ll;

ll n = PRIMES_UP_TO;
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

  primes_7(n);

  int ct = 1;
  for(ll i=1; i<p.size(); ++i){
    if(!p.test(i)){
      ct++;
    }
    if(ct == 10001){
      cout << 2*i+1 << endl;
      break;
    }
  }

  return 0;
}
