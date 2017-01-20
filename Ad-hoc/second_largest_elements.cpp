#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

int main(){

  /*
    PROBLEM: Given n numbers. for each number, find the first largest number to the right of it.
    SOLUTION:
      - use a stack
      - start from the end of the array.
      - any element you eliminate from the stack, cannot be a largest element
      for any of the elements to its left.
  */

  int t;cin>>t;
  for(int _t=1; _t<=t; _t++){
    int n;cin>>n;
    vector<int> ns(n,0);
    vector<int> res;
    for(int i=0; i<n; ++i)
      cin>>ns[i];
    stack<int> S;
    for(int i=ns.size()-1; i>=0; --i){
      if(S.empty()){
        res.push_back(-1);
        S.push(i);
      }
      else{
        while(!S.empty()){
          int pos = S.top();
          if(ns[i] > ns[pos])
            S.pop();
          else{
            S.push(i);
            res.push_back(pos);
            break;
          }
        }
      }
    }

    cout<<"Case #"<<_t<<": ";
    for(int i=res.size()-1; i>=0; --i)
      cout<<res[i]<<" ";
    cout << "\n";
  }

  return 0;
}
