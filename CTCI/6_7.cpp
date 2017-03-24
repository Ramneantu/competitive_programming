//====================================
// Name: 6.7 CTCI Vol 6
// Date: 24/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: simulate the one girl per family rule.
//====================================

#include<bits/stdc++.h>
using namespace std;

pair<int,int> simulateFamily(){
  pair<int,int> cnt;
  while(!cnt.second){
    int c = rand() % 2;
    if(c)
      cnt.first++;
    else{
      cnt.second++;
      break;
    }
  }
  return cnt;
}

pair<int,int> simulatePopulation(int families){
  pair<int,int> cnt; // first = boys, second = girls
  for(int i=0; i<families; ++i){
    auto res = simulateFamily();
    cnt.first += res.first;
    cnt.second += res.second;
  }
  return cnt;
}

int main(){

  srand(time(NULL));
  int families = rand() % int(1e7);
  auto cnt = simulatePopulation(families);
  cout << "#boys: " << cnt.first << " #girls: " << cnt.second << " ratio: " << float(cnt.first) / cnt.second << endl;
}
