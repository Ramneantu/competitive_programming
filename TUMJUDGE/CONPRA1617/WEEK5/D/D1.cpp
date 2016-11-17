#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

int main(){

  int t;
  cin >> t;
  for(int var=1; var<=t; ++var){
    string N;
    cin >> N;
    long long res = 0;
    long long base = 1;
    for(long long i=N.size()-1; i>=0; --i){
      res += ((N[i]-'0') * base) % 13;
      base = base*8 % 13;
    }
    res = (res + 2) % 13 + 1;

    printf("Case #%d: %lld\n", var, res);
  }

   return 0;
}
