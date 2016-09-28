#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

typedef long long ll;

using namespace std;

vector<int> arr;
ll merge_count_inv(int l, int r){
    if(l >= r)
        return 0;
    int m = l + (r-l)/2;
    ll cnt = merge_count_inv(l,m);
    cnt += merge_count_inv(m+1,r);
    vector<int> c;
    int i=l;
    int j=m+1;
    while(i <= m && j <= r){
        if(arr[i] > arr[j]){
            cnt += m-i+1;
            c.push_back(arr[j]);
            j++;
        }
        else{
            c.push_back(arr[i]);
            i++;
        }
    }
    while(i <= m){
        c.push_back(arr[i]);
        i++;
    }
    while(j <= r){
        c.push_back(arr[j]);
        j++;
    }
    for(int i=0; i<c.size(); ++i)
        arr[l+i] = c[i];
    c.erase(c.begin(), c.end());

    return cnt;
}


void merge_sort(int l, int r){
    if(l >= r)
      return;

    int m = l + (r-l)/2;
    merge_count_inv(l,m);
    merge_count_inv(m+1,r);
    int i=l;
    int j=m+1;
    while(i <= m && j <= r){
        if(arr[i] > arr[j]){
            swap(arr[i], arr[j]);
            i++;
        }
        else
            j++;
    }
}





ll count_inversions(vector<int> a) {
  return merge_count_inv(0, a.size()-1);
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        arr.resize(n,0);
        for(int arr_i = 0;arr_i < n;arr_i++){
           cin >> arr[arr_i];
        }
        merge_sort(0, arr.size()-1);
        for(int i=0; i<arr.size(); ++i)
          cout << arr[i] << " ";
        cout << endl;
        //cout << count_inversions(arr) << endl;
    }
    return 0;
}
