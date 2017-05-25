#include<bits/stdc++.h>

using namespace std;


int main(){
    int n;
    cin >> n;
    vector<int> c(101, 0);
    for(int c_i = 0;c_i < n;c_i++){
       int val;
       cin >> val;
        c[val]++;
    }
    int sum = 0;
    for(int i=1; i<=100; ++i)
        sum += c[i]/2;
    cout << sum << endl;
    return 0;
}
