#include <map>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

int main(){

  int T, n, k, vertex;
  cin >> T;
  for(int t=1; t<=T; ++t){
    cin >> n;
    vector<vector<int> > G(n,vector<int>());
    for(int i=0; i<n; ++i){
      cin >> k;
      for(int j=0; j<k; ++j){
        cin >> vertex;
        G[i].push_back(vertex-1);
      }
    }

    map<int,bool> A;
    map<int,bool> B;
    for(int i=0; i<n; ++i)
      A[i] = true;
    int cross_edges = 0;
    while(true){
      bool found = false;
      for(map<int,bool>::iterator it=A.begin(); it!=A.end(); ++it){
    	if(it->second){
    		int inB = 0;
    		int inA = 0;
    		int node = it->first;
    		for(int i=0; i<G[node].size(); ++i){
    			int u = G[node][i];
    			if(B.find(u) != B.end()){
    				inB++;
    			}
    			else if(A.find(u) != A.end()){
    				inA++;
    			}
    		}
    		if(cross_edges - inB + inA > cross_edges){
    			found = true;
    			cross_edges = cross_edges - inA + inB;
    			A[node] = false;
    			B[node] = true;
    		}
    	}
    }
    if(!found)
    	break;
    }
    printf("Case #%d:\n", t);
    for(map<int,bool>::iterator it=A.begin(); it!=A.end(); ++it)
      if(it->second)
        cout << it->first+1 << " ";
    cout << "\n";
  }

  return 0;
}
