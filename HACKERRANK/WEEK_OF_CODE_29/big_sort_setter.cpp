#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
using namespace std;


int main(){

  srand(time(0));
  int max_strs = 200000;
  int max_digits = 1000000;
  int n = max_strs;
  int dig_per_str = max_digits / n;
  string s;
  cout << n << endl;
  for(int i=0; i<n; ++i){
    for(int j=0; j<dig_per_str; ++j)
      s += char((rand() % 10) + '0');
    cout << s << endl;
    s.clear();
  }

	return 0;
}
