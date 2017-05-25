#include<bits/stdc++.h>

using namespace std;

#define PRIMES_UP_TO 100000002
typedef long ll;

template<typename T>
T gcd(T a, T b) {
    T t;
    while (b) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    ll n;
    cin >> n;
    ll ggt;
    ll a,b;
    cin >> a >> b;
    ggt = gcd(a,b);
    for(int i=0; i<n-2; ++i){
      cin >> a;
      ggt = gcd(a,ggt);
    }
    cout << "Case #" << t << ": " << ggt << "\n";
  }


   return 0;
}
