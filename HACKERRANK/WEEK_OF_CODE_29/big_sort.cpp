#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

bool cmp(string a, string b){
    if(a.size() == b.size()){
        return a < b;
    }
    else
        return a.size() < b.size();
}

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<string> unsorted(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       cin >> unsorted[unsorted_i];
    }
    sort(unsorted.begin(), unsorted.end(), cmp);
    for(int i=0; i<unsorted.size(); ++i)
        cout << unsorted[i] << "\n";
    return 0;
}
