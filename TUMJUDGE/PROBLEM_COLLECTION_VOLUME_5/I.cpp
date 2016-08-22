#include <iostream>

using namespace std;
#define REP(i, a, b) for(int i=int(a); i <= int(b); ++i)

int main(){

  int T;
  cin >> T;
  REP(t, 1, T){
    int e, f, c;
    cin >> e >> f >> c;
    int empty = e + f;
    int bottles = 0;
    while(empty >= c){
      bottles += empty / c;
      empty = empty/c + empty%c;
    }
    printf("Case #%d: %d\n", t, bottles);
  }

  return 0;
}
