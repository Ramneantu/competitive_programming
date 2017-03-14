#include <iostream>

using namespace std;

#define REP(i,a,b) for(int i=int(a); i <= int(b); ++i)

template<typename T>
T nCk(T n, T k){
  T res = 1;

  if(k > n)
    return -1;
  if(k == 0)
    return 1;
  REP(i, 1, k){
    res *= n+1-i;
    res /= i;
  }
  return res;
}

int main(){

  cout << nCk(long(40),long(20)) << endl;

  return 0;
}
