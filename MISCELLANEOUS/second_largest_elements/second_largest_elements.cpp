#include<bits/stdc++.h>
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
    vector<int> res(n,-1);
    for(int i=0; i<n; ++i)
      cin>>ns[i];
    stack<int> S;
    for(int i=ns.size()-1; i>=0; --i){
      if(!S.empty()){
        while(!S.empty()){
          if(ns[i] > ns[S.top()])
            S.pop();
          else{
            res[i] = S.top();
            break;
          }
        }
      }
      S.push(i);
    }

    cout<<"Case #"<<_t<<": ";
    for(int i=0; i<res.size(); ++i)
      if(i < res.size()-1)
        cout<<res[i]<<" ";
      else
        cout<<res[i];
    cout << "\n";
  }

  return 0;
}
