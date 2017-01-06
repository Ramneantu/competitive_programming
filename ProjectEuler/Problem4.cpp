#include <iostream>

using namespace std;

bool is_palindrome(int n){
  int pal_n = 0;
  int _n = n;
  while(_n>0){
    pal_n = 10*pal_n + _n%10;
    _n/=10;
  }
  return pal_n == n;
}

#define repr(i,b,a) for(int i=int(b); i>=int(a); --i)

int main(){

  int max_pal = -1;
  repr(i, 999, 100)
    repr(j, 999, 100){
      int n = i*j;
      if(n > max_pal && is_palindrome(n))
        max_pal = n;
    }
    cout << max_pal << endl;

  return 0;
}
