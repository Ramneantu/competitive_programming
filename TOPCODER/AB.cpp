//====================================
// Name: AB
// Date: 29/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description:
//====================================

#include<bits/stdc++.h>
using namespace std;

class AB{

public:
    string createString(int N, int K){
      int maxPairs = (N % 2 ? 2*(N/2 + 1) : N);
      if(K > maxPairs)
        return "";
      string res(N, 'A');
      int i=1;
      int placed = 0;
      while(K && i < N){
        if(K-i+placed >= 0){
          res[i] = 'B';
          K = K - i+placed;
          placed++;
        }
        i++;
      }
      return res;
    }
};

int main(){
  int T;
  cin >> T;
  for(int t=1; t<=T; ++t){
    int N, K;
    cin >> N >> K;
    AB s;
    printf("Case #%d: %s\n", t, s.createString(N,K).c_str());
  }
}
