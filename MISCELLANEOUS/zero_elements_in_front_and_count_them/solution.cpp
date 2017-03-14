#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

int main(){

  /*
  PROBLEM: Given an array of n numbers. Move all zeros to the front of the
           array and return their count at the end.
	*/

  int t;cin>>t;
  for(int _t=1; _t<=t; _t++){
    int n;cin>>n;
    vector<int> ns(n,0);
    for(int i=0; i<n; ++i)
      cin>>ns[i];
    
	int p = 0;
	int pp = p;
	while(pp < ns.size()){
		if(ns[p] == 0){
			p++;
			pp = max(p,pp);
		}
		else if(ns[pp] == 0){
			swap(ns[p], ns[pp]);
			p++;
			pp++;
		}
		else if(ns[pp] != 0){
			pp++;	
		}
	}
    cout<<"Case #"<<_t<<":\n" << p << endl;
	for(int i=0; i<ns.size(); ++i)
		cout << ns[i] << " ";
	cout << endl;
  }

  return 0;
}
