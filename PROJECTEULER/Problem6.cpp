#include <iostream>

using namespace std;

typedef long long ll;

int main(){

  ll sum_of_squares = 0;
  for(ll i = 1; i<=100; ++i)
    sum_of_squares += i*i;
  cout << ll(50*50*101*101) - sum_of_squares << endl;

  return 0;
}
