#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
typedef long long ll;

int main(){

  vector<int> arr;
  string s;
  while(cin>>s){
    cout << s << endl;
    rep(i,0,s.size()-1)
      arr.push_back(s[i]-'0');
  }

  // if you encounter 0 you have to restart the sequence of 13 numbers.
  ll prod = 1;
  ll max_prod = prod;
  ll i = 0;
  int ct = 0;
  while(i < arr.size()){
    if(arr[i] != 0){
      if(ct < 13){
        prod *= arr[i];
        ct++;
      }else{
        prod = prod * arr[i] / arr[i-13];
        if(max_prod < prod)
          max_prod = prod;
      }
    }else{
      ct = 0;
      prod = 1;
    }
    i++;
  }
  cout << max_prod << endl;


  return 0;
}
