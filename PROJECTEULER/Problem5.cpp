#include <iostream>

using namespace std;

template<typename T>
T ggt(T a, T b) {
    T t;
    while (b) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long kgv(long a, long b){
  return a*b / ggt(a,b);
}

int main(){

  long lcm = 1;
  for(int i=2; i<=20; ++i)
    lcm = kgv(lcm, i);
  cout << lcm << endl;

  return 0;
}
