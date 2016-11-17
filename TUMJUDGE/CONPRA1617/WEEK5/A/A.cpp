#include <bitset>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <utility>
#include <cmath>

using namespace std;

#define PRIMES_UP_TO 100000002
typedef long ll;

ll N = PRIMES_UP_TO;
bitset<PRIMES_UP_TO/2> p;

void primes(ll n){
  ll lim = ll(sqrt(n)) / 2;
  n /= 2;
  for(ll i=1; i<=lim; i++){
    if(!p.test(i)){
      for(ll j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
        p.set(j);
    }
  }
}

inline bool is_prime(ll n){
  if(n < 2)
    return false;
  if(n == 2)
    return true;
  if(n > 2 && n%2 == 0)
    return false;
  return (!p.test(n/2));
}

vector<ll> tuples;
bool gold_bach_even(ll n){
  if(is_prime(n-2)){
    tuples.push_back(2);
    tuples.push_back(n-2);
    return true;
  }
  else{
    for(ll i=1; i<p.size(); ++i)
      if(!p.test(i)){
        if(2*i+1 < n && is_prime(n-2*i-1)){
          //cout << i << " " << n-(2*i+1) << endl;
          tuples.push_back(2*i+1);
          tuples.push_back(n-2*i-1);
          return true;
        }
      }
  }
  return false;
}

int main(){
   primes(N);/*
   for(int i=1; i<=p.size()-1; ++i)
    if(!p.test(i))
      cout << i << " prime: " << 2*i+1 << endl;*/
   int T;
   cin >> T;
   for(int t=1; t<=T; ++t){
      ll n;
      cin >> n;
      int j=0;
      tuples.clear();
      if(n%2){
        // try 2
        tuples.push_back(2);
        if(!gold_bach_even(n-2)){
          tuples.clear();
          tuples.push_back(2);
          tuples.push_back(2);
          if(is_prime(n-4)){
            tuples.push_back(n-4);
          }
          else{
            //cout << "first 3 ";
            tuples.clear();
            tuples.push_back(3);
            gold_bach_even(n-3);
          }
        }
      }
      else{
        gold_bach_even(n);
      }
      cout << "Case #" << t << ": ";
      for(int i=0; i<tuples.size(); ++i)
        cout << tuples[i] << " ";
      cout << "\n";
   }
   return 0;
}
