#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include <cstring>

using namespace std;
typedef long long ll;
#define MOD 13

int main(){

  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    string X;
    cin >> X;
    ll day = 0;
    ll b = 1;
    ll len = X.size();
    for(ll i=len-1; i>=0; i--){
      day += ((X[i]-'0') * b) % MOD;
      b = (b*8) % MOD;
    }
    day = (day + 2) % MOD + 1;

    cout << "Case #" << t << ": " << day << "\n";
  }
   return 0;
}
