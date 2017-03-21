//====================================
// Name: 12_1 CTCI Volume 6
// Date: 21/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: Read last k lines of a file.
//====================================

#include<bits/stdc++.h>
using namespace std;

int main(){
  #if 0
  //====================================
  // Two-pointer solution.
  // Complexity: O(lines)
  // Space: O(lines)
  //====================================
  // read last k lines of a file
  ifstream f("file.in");
  ifstream g("file.in");

  // move f stream k lines down.
  int k;
  cin >> k;
  string line;
  for(int i=0; i<k; ++i) getline(f,line);

  // move f and g stream at the same pace.
  for(; getline(f,line); ){
    getline(g, line);
  }

  // g now has to go the last k lines.
  for(; getline(g,line); )
    cout << line << endl;
  #else
    //====================================
    // K-sized Queue solution.
    // Complexity: O(lines)
    // Space: O(K)
    //====================================

    ifstream fin("file.in");
    int k;
    cin >> k;
    queue<string> Q;
    string line;
    for(; getline(fin, line); ){
      if(Q.size() == k){
        Q.pop();
      }
      Q.push(line);
    }
    while(!Q.empty()){
      cout << Q.front() << endl;
      Q.pop();
    }
    #endif
}
