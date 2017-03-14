#include <iostream>
#include <vector>

using namespace std;

int main(){

  int n;
  cin >> n;
  vector<int> arr(n+1,0);
  arr[3] = arr[5] = 1;

  // mark all multiples of 3
  for(int i=6; i<n; i+=3)
    arr[i] = 1;

  // mark all multiples of 5
  for(int i=10; i<n; i+=5)
  arr[i] = 1;

  int sum = 0;
  // add all multiples of 3 or 5
  for(int i=0; i<n; ++i)
    sum += arr[i]*i;

  cout << sum << endl;

  return 0;
}
