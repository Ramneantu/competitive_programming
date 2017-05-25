#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

#define NMAX 775148
int main(){


// Find largest prime of n = 600851475143
// any number n has at most one prime greater than sqrt(n)
// by finding all primes up to sqrt(n) and dividing n by all their powers,
// the resulting number will be the last prime or 1.
bitset<NMAX> primes;
ll n = 600851475143;

cout << n << endl;

// sieve of erastotenes
// we do not store the even i's becaseu they are not prime
// so primes[i] = 0, if 2*i-1 is prime
ll lim = ll(sqrt(NMAX));
for(ll i=2; i<=lim; ++i){
  if(!primes.test(i)){
    for(ll j = i+i; j<primes.size(); j+=i)
      primes.set(j);
  }
}

ll largest_prime_factor = 1;
for(ll i=2; i<primes.size(); ++i){
  if(!primes.test(i)){
    if(n%i == 0){
      if(largest_prime_factor < i)
        largest_prime_factor = i;
      while(n%i == 0 && n >= 1){
        cout << "n: " << n << endl;
        n /= i;
      }
    }
  }
}

// n is either 1 or a prime
if(n != 1){
  if(n > largest_prime_factor)
    largest_prime_factor = n;
}

  cout << largest_prime_factor << endl;

  return 0;
}
