#include <bits/stdc++.h>
using namespace std;

int main(){

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

  return 0;
}