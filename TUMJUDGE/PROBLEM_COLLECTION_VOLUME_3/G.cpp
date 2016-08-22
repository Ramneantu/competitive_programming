
#include <iostream>

using namespace std;

typedef long long ll;

bool is_prime(ll n){
  if(n < 2)
    return false;
  if(n == 2)
    return true;
  for(ll d=2; d*d<=n; d+=1){
    if(n % d == 0)
      return false;
  }
  return true;
}

ll turn_upside(ll n){
  ll new_n = 0;
  while(n > 0){
    int c = n%10;
    if(c == 6)
      c = 9;
    else if(c == 9)
      c = 6;
    if(c == 3 || c == 4 || c == 7)
      return 0;

    new_n = new_n * 10 + c;
    n /= 10;
  }
  return new_n;
}

int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    ll n;
    cin >> n;
    ll upside_n = turn_upside(n);

    if(is_prime(n) && is_prime(upside_n))
      printf("Case #%d: yes\n", t);
    else
      printf("Case #%d: no\n", t);
  }

  return 0;
}
