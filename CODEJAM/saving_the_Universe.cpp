#include<bits/stdc++.h>
//====================================
// Name: Saving the Universe CodeJam Qualification 2008
// Date: 27/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: https://code.google.com/codejam/contest/32013/dashboard
//====================================

using namespace std;

int minimumSearchEngineSwitches(vector<string>& engines, vector<string>& queries){
  int res = 0;
  map<string, bool> H;
  for(auto q : queries){
    if(H.find(q) == H.end()){
      if(H.size() == engines.size()-1){
        res++;
        H.clear();
      }
    }
    H[q] = true;
  }
  return res;
}

int main(){
  int t;
  cin >> t;
  for(int i=1; i<=t; ++i){
    int n;
    cin >> n;
    vector<string> engines(n);
    string dummy;
    getline(cin,dummy);
    for(int j=0; j<n; ++j)
      getline(cin, engines[j]);
    int q;
    cin >> q;
    getline(cin, dummy);
    vector<string> queries(q);
    for(int j=0; j<q; ++j)
      getline(cin, queries[j]);

    printf("Case #%d: %d\n", i, minimumSearchEngineSwitches(engines, queries));
  }
}
