//====================================
// Name: A
// Date: 8/4/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description:
//====================================

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <utility>
using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define all(V) V.begin(), V.end()

void flip(int from, int to, vector<bool>& strip){
  rep(i,from,to){
    strip[i] = ~strip[i];
  }
}

inline bool isGoal(vector<bool>& strip){
  rep(i,0,strip.size()-1)
    if(!strip[i])
      return false;
  return true;
}

int k, minSteps;
void solveHelper(vector<bool>& strip, int steps, int pos){
  #if 0
  cout << pos << " " << steps << endl;
  for(auto c : strip)
    cout << c << " ";
  cout << endl;
  #endif
  if(isGoal(strip))
    minSteps = min(minSteps, steps);
  if(pos > strip.size()-k)
    return;

  // flip
  flip(pos, pos+k-1, strip);
  solveHelper(strip, steps+1, pos+1);
  flip(pos,pos+k-1,strip); // undo flip

  // don't flip at this step
  solveHelper(strip, steps, pos+1);
}

int solve(vector<bool>& strip){
  minSteps = INT_MAX;
  solveHelper(strip, 0, 0);
  return minSteps;
}

int main(){
  ios_base::sync_with_stdio(0);

  int T;
  cin >> T;
  rep(t,1,T){
    string s;
    cin >> s >> k;
    vector<bool> strip(s.size());
    rep(i,0,int(s.size())-1)
      strip[i] = (s[i] == '+' ? true : false);
    int res = solve(strip);
    cout << "Case #" << t << ": ";
    if(res >= INT_MAX)
      cout << "IMPOSSIBLE";
    else
      cout <<   res;
    cout << endl;
  }
}
