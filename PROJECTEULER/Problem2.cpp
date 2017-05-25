#include<bits/stdc++.h>

using namespace std;

#define NMAX 4000001

typedef long long ll;

int main(){

  // sum even terms of fibonacci
  ll n;
  cin >> n;
  ll a = 1;
  ll b = 1;
  int i = 1;
  ll sum = 0;
  while(b <= n){
    ll c = a + b;
    a = b;
    b = c;
    if(c%2 == 0)
      sum += c;
  }
  cout << sum << endl;

  return 0;
}
