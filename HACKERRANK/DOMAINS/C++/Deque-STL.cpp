#include <iostream>
#include <deque>
#include <utility>
#include <algorithm>
using namespace std;

void insert_into_deque(int arr[], deque<int> &dq, int pos){
    while(!dq.empty() && arr[dq.back()] <= arr[pos]){
        dq.pop_back();
    }
    dq.push_back(pos);
}

void printKMax(int arr[], int n, int k){
    if(k > n)
        return;
    deque<int> dq;
    for(int i=0; i<k; ++i){
        insert_into_deque(arr, dq, i);
    }
    cout << arr[dq.front()] << " ";
    for(int i=k; i<n; ++i){
        if(!dq.empty() && i-k+1 > dq.front())
            dq.pop_front();
        insert_into_deque(arr, dq, i);
        cout << arr[dq.front()] << " ";
    }
    cout << endl;
}

int main(){

   int t;
   cin >> t;
   while(t>0) {
      int n,k;
       cin >> n >> k;
       int i;
       int arr[n];
       for(i=0;i<n;i++)
            cin >> arr[i];
       printKMax(arr, n, k);
       t--;
     }
     return 0;
}
